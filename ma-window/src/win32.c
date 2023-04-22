#include <ma-window/ma-window.h>
#include <windows.h>
#include <stdlib.h>
#include <glad/wgl.h>
#include <glad/gl.h>

#ifndef UNICODE
#define UNICODE
#endif

typedef struct {
    MaWindow parent;
    HWND hwnd;
    wchar_t *title_w;
    bool shoud_close;
    HINSTANCE hInstance;
    HDC hdc;
    HGLRC rc;
} Win32Window;

LRESULT CALLBACK maWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    Win32Window *w = (Win32Window *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    switch (uMsg) {
        case WM_DESTROY:
            w->shoud_close = true;
            return 0;
        case WM_MOUSEMOVE:
            if (w->parent.mouseMovedCallback) {
                w->parent.mouseMovedCallback(LOWORD(lParam), HIWORD(lParam));
            }
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

MaWindow *maWindowNew(int width, int height, const char *title) {
    Win32Window *window = malloc(sizeof(Win32Window));
    if (!window)
        return NULL;
    window->parent.width = width;
    window->parent.height = height;
    window->parent.title = title;
    window->parent.hasGlContext = false;
    maWindowsInit(&window->parent.children);
    window->parent.mouseMovedCallback = NULL;
    window->parent.resizeCallback = NULL;
    window->parent.keyPressedCallback = NULL;
    window->parent.keyReleasedCallback = NULL;
    window->parent.mouseButtonPressedCallback = NULL;
    window->parent.mouseButtonReleasedCallback = NULL;
    window->shoud_close = false;

    HINSTANCE hInstance = GetModuleHandle(NULL);
    window->hInstance = hInstance;

    const wchar_t CLASS_NAME[] = L"ma-window";
    WNDCLASSW wc = {0};
    wc.lpfnWndProc = maWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.cbWndExtra = sizeof(Win32Window *);

    RegisterClassW(&wc);

    size_t title_len = strlen(title) + 1;
    window->title_w = malloc(title_len * sizeof(wchar_t));
    mbstowcs(window->title_w, title, title_len);

    window->hwnd = CreateWindowExW(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        window->title_w,    // Window text
        WS_OVERLAPPEDWINDOW | CS_OWNDC,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );
    SetWindowLongPtr(window->hwnd, GWLP_USERDATA, (LONG_PTR)window);

    if (window->hwnd == NULL) {
        free(window);
        return NULL;
    }

    window->hdc = GetDC(window->hwnd);

    ShowWindow(window->hwnd, SW_SHOWDEFAULT);

    return (MaWindow *)window;
}

void maWindowFree(MaWindow *window) {
    Win32Window *win32_window = (Win32Window *)window;
    DestroyWindow(win32_window->hwnd);
    free(win32_window->title_w);
    ReleaseDC(win32_window->hwnd, win32_window->hdc);
    wglDeleteContext(win32_window->rc);
    maWindowsFree(&win32_window->parent.children);
    free(win32_window);
}

bool maWindowPollEvents(MaWindow *window) {
    MSG msg;
    Win32Window *win32_window = (Win32Window *)window;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
        if (win32_window->shoud_close)
            return false;
        for (int i = 0; i < window->children.len; i++) {
            if (window->children.data[i] == NULL)
                continue;
            if (!maWindowPollEvents(window->children.data[i])) {
                maWindowsRemove(&window->children, i);
            }
        }
    }
    return true;
}

void maWindowMakeGlContextCurrent(MaWindow *window) {
    if (window == NULL || !window->hasGlContext)
        return;
    wglMakeCurrent(((Win32Window *)window)->hdc, ((Win32Window *)window)->rc);
}

bool maWindowMakeGlContext(MaWindow *pwindow, int major, int minor) {
    Win32Window *window = (Win32Window *)pwindow;
    
    const wchar_t CLASS_NAME[] = L"fake-ma-window";
    WNDCLASSW wc = {0};
    wc.lpfnWndProc = DefWindowProcW;
    wc.hInstance = window->hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.cbWndExtra = sizeof(Win32Window *);

    RegisterClassW(&wc);

    HWND fakeWND = CreateWindow(
        "fake-ma-window", "Fake Window",      // window class, title
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // style
        0, 0,                       // position x, y
        1, 1,                       // width, height
        NULL, NULL,                 // parent window, menu
        window->hInstance, NULL);           // instance, param
    if (!fakeWND) {
        free(window);
        char msg[256];
        MessageBoxA(NULL, itoa(GetLastError(), msg, 10), "fakewnd Error", MB_OK | MB_ICONEXCLAMATION);
        return false;
    }


    HDC fakeDC = GetDC(fakeWND);
    PIXELFORMATDESCRIPTOR fakePFD;
    ZeroMemory(&fakePFD, sizeof(fakePFD));
    fakePFD.nSize = sizeof(fakePFD);
    fakePFD.nVersion = 1;
    fakePFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    fakePFD.iPixelType = PFD_TYPE_RGBA;
    fakePFD.cColorBits = 32;
    fakePFD.cAlphaBits = 8;
    fakePFD.cDepthBits = 24;

    
    int fakePFDID = ChoosePixelFormat(fakeDC, &fakePFD);
    if (fakePFDID == 0) {
        DestroyWindow(fakeWND);
        free(window);
        return false;
    }

    if (!SetPixelFormat(fakeDC, fakePFDID, &fakePFD)) {
        DestroyWindow(fakeWND);
        free(window);
        return false;
    }

    HGLRC fakeRC = wglCreateContext(fakeDC);
    if (!fakeRC) {
        DestroyWindow(fakeWND);
        free(window);
        return false;
    }
    if (!wglMakeCurrent(fakeDC, fakeRC)) {
        wglDeleteContext(fakeRC);
        DestroyWindow(fakeWND);
        free(window);
        return false;
    }

    gladLoaderLoadWGL(fakeDC);

    const int pixelAttribs[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_ALPHA_BITS_ARB, 8,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
        WGL_SAMPLES_ARB, 4,
        0
    };
    
    int pixelFormatID; UINT numFormats;
    bool status = wglChoosePixelFormatARB(window->hdc, pixelAttribs, NULL, 1, &pixelFormatID, &numFormats);
    
    if (!status || numFormats == 0) {
        DestroyWindow(window->hwnd);
        free(window);
        return false;
    }

    PIXELFORMATDESCRIPTOR PFD;
    DescribePixelFormat(window->hdc, pixelFormatID, sizeof(PFD), &PFD);
    SetPixelFormat(window->hdc, pixelFormatID, &PFD);

    int  contextAttribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, major,
        WGL_CONTEXT_MINOR_VERSION_ARB, minor,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };
    
    HGLRC RC = wglCreateContextAttribsARB(window->hdc, 0, contextAttribs);
    if (RC == NULL) {
        DestroyWindow(window->hwnd);
        maWindowFree(pwindow);
        return false;
    }


    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(fakeRC);
    ReleaseDC(fakeWND, fakeDC);
    DestroyWindow(fakeWND);

    if (!wglMakeCurrent(window->hdc, RC)) {
        wglDeleteContext(RC);
        DestroyWindow(window->hwnd);
        maWindowFree(pwindow);
        return false;
    }

    window->rc = RC;
    pwindow->hasGlContext = true;

    int gl_version = gladLoaderLoadGL();
    if (!gl_version) {
        return false;
    }

    return true;
}

void maWindowSwapBuffers(MaWindow *window) {
    if (window == NULL)
        return;
    wglSwapLayerBuffers(((Win32Window *)window)->hdc, WGL_SWAP_MAIN_PLANE);
}