#include <macademia/window.h>
#include <windows.h>
#include <stdlib.h>
#include <glad/wgl.h>
#include <glad/gl.h>
#include <stdint.h>
#include <macademia/log.h>

#ifndef UNICODE
#define UNICODE
#endif

static uint32_t keymap[] = {
    [VK_SPACE] = MA_KEY_SPACE,
    [VK_OEM_7] = MA_KEY_APOSTROPHE,
    [VK_OEM_COMMA] = MA_KEY_COMMA,
    [VK_OEM_MINUS] = MA_KEY_MINUS,
    [VK_OEM_PERIOD] = MA_KEY_PERIOD,
    [VK_OEM_2] = MA_KEY_SLASH,
    ['0'] = MA_KEY_0,
    ['1'] = MA_KEY_1,
    ['2'] = MA_KEY_2,
    ['3'] = MA_KEY_3,
    ['4'] = MA_KEY_4,
    ['5'] = MA_KEY_5,
    ['6'] = MA_KEY_6,
    ['7'] = MA_KEY_7,
    ['8'] = MA_KEY_8,
    ['9'] = MA_KEY_9,
    [VK_OEM_1] = MA_KEY_SEMICOLON,
    [VK_OEM_PLUS] = MA_KEY_EQUAL,
    ['A'] = MA_KEY_A,
    ['B'] = MA_KEY_B,
    ['C'] = MA_KEY_C,
    ['D'] = MA_KEY_D,
    ['E'] = MA_KEY_E,
    ['F'] = MA_KEY_F,
    ['G'] = MA_KEY_G,
    ['H'] = MA_KEY_H,
    ['I'] = MA_KEY_I,
    ['J'] = MA_KEY_J,
    ['K'] = MA_KEY_K,
    ['L'] = MA_KEY_L,
    ['M'] = MA_KEY_M,
    ['N'] = MA_KEY_N,
    ['O'] = MA_KEY_O,
    ['P'] = MA_KEY_P,
    ['Q'] = MA_KEY_Q,
    ['R'] = MA_KEY_R,
    ['S'] = MA_KEY_S,
    ['T'] = MA_KEY_T,
    ['U'] = MA_KEY_U,
    ['V'] = MA_KEY_V,
    ['W'] = MA_KEY_W,
    ['X'] = MA_KEY_X,
    ['Y'] = MA_KEY_Y,
    ['Z'] = MA_KEY_Z,
    [VK_OEM_4] = MA_KEY_LEFT_BRACKET,
    [VK_OEM_5] = MA_KEY_BACKSLASH,
    [VK_OEM_6] = MA_KEY_RIGHT_BRACKET,
    [VK_OEM_3] = MA_KEY_GRAVE_ACCENT,
    [VK_ESCAPE] = MA_KEY_ESCAPE,
    [VK_RETURN] = MA_KEY_ENTER,
    [VK_TAB] = MA_KEY_TAB,
    [VK_BACK] = MA_KEY_BACKSPACE,
    [VK_INSERT] = MA_KEY_INSERT,
    [VK_DELETE] = MA_KEY_DELETE,
    [VK_RIGHT] = MA_KEY_RIGHT,
    [VK_LEFT] = MA_KEY_LEFT,
    [VK_DOWN] = MA_KEY_DOWN,
    [VK_UP] = MA_KEY_UP,
    [VK_PRIOR] = MA_KEY_PAGE_UP,
    [VK_NEXT] = MA_KEY_PAGE_DOWN,
    [VK_HOME] = MA_KEY_HOME,
    [VK_END] = MA_KEY_END,
    [VK_CAPITAL] = MA_KEY_CAPS_LOCK,
    [VK_SCROLL] = MA_KEY_SCROLL_LOCK,
    [VK_NUMLOCK] = MA_KEY_NUM_LOCK,
    [VK_PRINT] = MA_KEY_PRINT_SCREEN,
    [VK_MEDIA_PLAY_PAUSE] = MA_KEY_PAUSE,
    [VK_F1] = MA_KEY_F1,
    [VK_F2] = MA_KEY_F2,
    [VK_F3] = MA_KEY_F3,
    [VK_F4] = MA_KEY_F4,
    [VK_F5] = MA_KEY_F5,
    [VK_F6] = MA_KEY_F6,
    [VK_F7] = MA_KEY_F7,
    [VK_F8] = MA_KEY_F8,
    [VK_F9] = MA_KEY_F9,
    [VK_F10] = MA_KEY_F10,
    [VK_F11] = MA_KEY_F11,
    [VK_F12] = MA_KEY_F12,
    [VK_F13] = MA_KEY_F13,
    [VK_F14] = MA_KEY_F14,
    [VK_F15] = MA_KEY_F15,
    [VK_F16] = MA_KEY_F16,
    [VK_F17] = MA_KEY_F17,
    [VK_F18] = MA_KEY_F18,
    [VK_F19] = MA_KEY_F19,
    [VK_F20] = MA_KEY_F20,
    [VK_F21] = MA_KEY_F21,
    [VK_F22] = MA_KEY_F22,
    [VK_F23] = MA_KEY_F23,
    [VK_F24] = MA_KEY_F24,
    [0] = MA_KEY_F25,
    [VK_NUMPAD0] = MA_KEY_KP_0,
    [VK_NUMPAD1] = MA_KEY_KP_1,
    [VK_NUMPAD2] = MA_KEY_KP_2,
    [VK_NUMPAD3] = MA_KEY_KP_3,
    [VK_NUMPAD4] = MA_KEY_KP_4,
    [VK_NUMPAD5] = MA_KEY_KP_5,
    [VK_NUMPAD6] = MA_KEY_KP_6,
    [VK_NUMPAD7] = MA_KEY_KP_7,
    [VK_NUMPAD8] = MA_KEY_KP_8,
    [VK_NUMPAD9] = MA_KEY_KP_9,
    [VK_DECIMAL] = MA_KEY_KP_DECIMAL,
    [VK_DIVIDE] = MA_KEY_KP_DIVIDE,
    [VK_MULTIPLY] = MA_KEY_KP_MULTIPLY,
    [VK_SUBTRACT] = MA_KEY_KP_SUBTRACT,
    [VK_ADD] = MA_KEY_KP_ADD,
    [VK_RETURN] = MA_KEY_KP_ENTER,
    [VK_OEM_PLUS] = MA_KEY_KP_EQUAL,
    [VK_SHIFT] = MA_KEY_LEFT_SHIFT,
    [VK_CONTROL] = MA_KEY_LEFT_CONTROL,
    [VK_LMENU] = MA_KEY_LEFT_ALT,
    [VK_LWIN] = MA_KEY_LEFT_SUPER,
    [VK_SHIFT] = MA_KEY_RIGHT_SHIFT,
    [VK_CONTROL] = MA_KEY_RIGHT_CONTROL,
    [VK_RMENU] = MA_KEY_RIGHT_ALT,
    [VK_RWIN] = MA_KEY_RIGHT_SUPER,
    [VK_MENU] = MA_KEY_MENU,
    [VK_OEM_102] = MA_KEY_UNKNOWN,
};

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
        case WM_SIZE:
            w->parent.width = LOWORD(lParam);
            w->parent.height = HIWORD(lParam);
            if (w->parent.hasGlContext)
                glViewport(0, 0, w->parent.width, w->parent.height);
            if (w->parent.resizeCallback) {
                w->parent.resizeCallback(LOWORD(lParam), HIWORD(lParam));
            }
            return 0;
        case WM_KEYDOWN:
            if (w->parent.keyPressedCallback) {
                w->parent.keyPressedCallback(keymap[wParam]);
                // printf("key down %d\n", wParam);
            }
            return 0;
        case WM_KEYUP:
            if (w->parent.keyReleasedCallback) {
                w->parent.keyReleasedCallback(keymap[wParam]);
            }
            return 0;
        case WM_LBUTTONDOWN:
            if (w->parent.mouseButtonPressedCallback) {
                w->parent.mouseButtonPressedCallback(MA_MOUSE_BUTTON_LEFT);
            }
            return 0;
        case WM_LBUTTONUP:
            if (w->parent.mouseButtonReleasedCallback) {
                w->parent.mouseButtonReleasedCallback(MA_MOUSE_BUTTON_LEFT);
            }
            return 0;
        case WM_RBUTTONDOWN:
            if (w->parent.mouseButtonPressedCallback) {
                w->parent.mouseButtonPressedCallback(MA_MOUSE_BUTTON_RIGHT);
            }
            return 0;
        case WM_RBUTTONUP:
            if (w->parent.mouseButtonReleasedCallback) {
                w->parent.mouseButtonReleasedCallback(MA_MOUSE_BUTTON_RIGHT);
            }
            return 0;
        case WM_MBUTTONDOWN:
            if (w->parent.mouseButtonPressedCallback) {
                w->parent.mouseButtonPressedCallback(MA_MOUSE_BUTTON_MIDDLE);
            }
            return 0;
        case WM_MBUTTONUP:
            if (w->parent.mouseButtonReleasedCallback) {
                w->parent.mouseButtonReleasedCallback(MA_MOUSE_BUTTON_MIDDLE);
            }
            return 0;
        case WM_XBUTTONDOWN:
            if (w->parent.mouseButtonPressedCallback) {
                w->parent.mouseButtonPressedCallback(MA_MOUSE_BUTTON_9 + HIWORD(wParam) - 1);
            }
            return 0;
        case WM_XBUTTONUP:
            if (w->parent.mouseButtonReleasedCallback) {
                w->parent.mouseButtonReleasedCallback(MA_MOUSE_BUTTON_9 + HIWORD(wParam) - 1);
            }
            return 0;
        case WM_MOUSEWHEEL:
            if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) {
                if (w->parent.mouseButtonPressedCallback) {
                    w->parent.mouseButtonPressedCallback(MA_MOUSE_BUTTON_4);
                }
                if (w->parent.mouseButtonReleasedCallback) {
                    w->parent.mouseButtonReleasedCallback(MA_MOUSE_BUTTON_4);
                }
            } else {
                if (w->parent.mouseButtonPressedCallback) {
                    w->parent.mouseButtonPressedCallback(MA_MOUSE_BUTTON_5);
                }
                if (w->parent.mouseButtonReleasedCallback) {
                    w->parent.mouseButtonReleasedCallback(MA_MOUSE_BUTTON_5);
                }
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
        MA_LOG_FIELDS(MaFatal, "failed to create HWND", "window", title);
        free(window);
        return NULL;
    }

    window->hdc = GetDC(window->hwnd);

    ShowWindow(window->hwnd, SW_SHOWDEFAULT);

    MA_LOG_FIELDS(MaInfo, "opened window", "window", title);
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
        MA_LOG(MaError, "failed to create fake window");
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
        MA_LOG(MaError, "failed to choose fake pixel format");
        DestroyWindow(fakeWND);
        free(window);
        return false;
    }

    if (!SetPixelFormat(fakeDC, fakePFDID, &fakePFD)) {
        MA_LOG(MaError, "failed to set fake pixel format");
        DestroyWindow(fakeWND);
        free(window);
        return false;
    }

    HGLRC fakeRC = wglCreateContext(fakeDC);
    if (!fakeRC) {
        MA_LOG(MaError, "failed to create fake GL context");
        DestroyWindow(fakeWND);
        free(window);
        return false;
    }
    if (!wglMakeCurrent(fakeDC, fakeRC)) {
        MA_LOG(MaError, "failed to make fake GL context current");
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
        MA_LOG(MaError, "failed to choose pixel format");
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
        MA_LOG(MaError, "failed to create GL context");
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
        MA_LOG(MaError, "failed to load GL");
        return false;
    }

    MA_LOG_FIELDS(MaInfo, "created GL context", "window", pwindow->title);
    return true;
}

void maWindowSwapBuffers(MaWindow *window) {
    if (window == NULL)
        return;
    wglSwapLayerBuffers(((Win32Window *)window)->hdc, WGL_SWAP_MAIN_PLANE);
}