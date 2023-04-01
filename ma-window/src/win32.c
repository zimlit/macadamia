#include <ma-window/ma-window.h>
#include <windows.h>
#include <stdlib.h>

#ifndef UNICODE
#define UNICODE
#endif

typedef struct {
    MaWindow parent;
    HWND hwnd;
    wchar_t *title_w;
    bool shoud_close;
} Win32Window;

LRESULT CALLBACK maWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    Win32Window *w = (Win32Window *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    switch (uMsg) {
        case WM_DESTROY:
            w->shoud_close = true;
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
        WS_OVERLAPPEDWINDOW,            // Window style

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

    ShowWindow(window->hwnd, SW_SHOWDEFAULT);

    return (MaWindow *)window;
}

void maWindowFree(MaWindow *window) {
    Win32Window *win32_window = (Win32Window *)window;\
    free(win32_window->title_w);
    maWindowsFree(&win32_window->parent.children);
    free(win32_window);
}

bool maWindowPollEvents(MaWindow *window) {
    MSG msg;
    Win32Window *win32_window = (Win32Window *)window;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if (win32_window->shoud_close)
            return false;
        for (int i = 0; i < window->children.len; i++) {
            if (window->children.data[i] == NULL)
                continue;
            if (((Win32Window *)window->children.data[i])->shoud_close)
                maWindowsRemove(&window->children, i);
        }
    }
    return true;
}

void maWindowMakeGlContextCurrent(MaWindow *window) {
}

bool maWindowMakeGlContext(MaWindow *window, int major, int minor) {
    return true;
}

void maWindowSwapBuffers(MaWindow *window) {
}