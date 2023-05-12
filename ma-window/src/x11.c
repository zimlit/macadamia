/**
 * Copyright (C) 2023 Devin Rockwell
 * 
 * This file is part of macademia.
 * 
 * macademia is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * macademia is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with macademia.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <ma-window/ma-window.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <glad/gl.h>
#include <GL/glx.h>
#include <stdio.h>
#include <string.h>

static uint32_t keymap[] = {
    [XK_space] = MA_KEY_SPACE,
    [XK_apostrophe] = MA_KEY_APOSTROPHE,
    [XK_comma] = MA_KEY_COMMA,
    [XK_minus] = MA_KEY_MINUS,
    [XK_period] = MA_KEY_PERIOD,
    [XK_slash] = MA_KEY_SLASH,
    [XK_0] = MA_KEY_0,
    [XK_1] = MA_KEY_1,
    [XK_2] = MA_KEY_2,
    [XK_3] = MA_KEY_3,
    [XK_4] = MA_KEY_4,
    [XK_5] = MA_KEY_5,
    [XK_6] = MA_KEY_6,
    [XK_7] = MA_KEY_7,
    [XK_8] = MA_KEY_8,
    [XK_9] = MA_KEY_9,
    [XK_semicolon] = MA_KEY_SEMICOLON,
    [XK_equal] = MA_KEY_EQUAL,
    [XK_a] = MA_KEY_A,
    [XK_b] = MA_KEY_B,
    [XK_c] = MA_KEY_C,
    [XK_d] = MA_KEY_D,
    [XK_e] = MA_KEY_E,
    [XK_f] = MA_KEY_F,
    [XK_g] = MA_KEY_G,
    [XK_h] = MA_KEY_H,
    [XK_i] = MA_KEY_I,
    [XK_j] = MA_KEY_J,
    [XK_k] = MA_KEY_K,
    [XK_l] = MA_KEY_L,
    [XK_m] = MA_KEY_M,
    [XK_n] = MA_KEY_N,
    [XK_o] = MA_KEY_O,
    [XK_p] = MA_KEY_P,
    [XK_q] = MA_KEY_Q,
    [XK_r] = MA_KEY_R,
    [XK_s] = MA_KEY_S,
    [XK_t] = MA_KEY_T,
    [XK_u] = MA_KEY_U,
    [XK_v] = MA_KEY_V,
    [XK_w] = MA_KEY_W,
    [XK_x] = MA_KEY_X,
    [XK_y] = MA_KEY_Y,
    [XK_z] = MA_KEY_Z,
    [XK_bracketleft] = MA_KEY_LEFT_BRACKET,
    [XK_backslash] = MA_KEY_BACKSLASH,
    [XK_bracketright] = MA_KEY_RIGHT_BRACKET,
    [XK_grave] = MA_KEY_GRAVE_ACCENT,
    [XK_Escape] = MA_KEY_ESCAPE,
    [XK_Return] = MA_KEY_ENTER,
    [XK_Tab] = MA_KEY_TAB,
    [XK_BackSpace] = MA_KEY_BACKSPACE,
    [XK_Insert] = MA_KEY_INSERT,
    [XK_Delete] = MA_KEY_DELETE,
    [XK_Right] = MA_KEY_RIGHT,
    [XK_Left] = MA_KEY_LEFT,
    [XK_Down] = MA_KEY_DOWN,
    [XK_Up] = MA_KEY_UP,
    [XK_Page_Up] = MA_KEY_PAGE_UP,
    [XK_Page_Down] = MA_KEY_PAGE_DOWN,
    [XK_Home] = MA_KEY_HOME,
    [XK_End] = MA_KEY_END,
    [XK_Caps_Lock] = MA_KEY_CAPS_LOCK,
    [XK_Scroll_Lock] = MA_KEY_SCROLL_LOCK,
    [XK_Num_Lock] = MA_KEY_NUM_LOCK,
    [XK_Print] = MA_KEY_PRINT_SCREEN,
    [XK_Pause] = MA_KEY_PAUSE,
    [XK_F1] = MA_KEY_F1,
    [XK_F2] = MA_KEY_F2,
    [XK_F3] = MA_KEY_F3,
    [XK_F4] = MA_KEY_F4,
    [XK_F5] = MA_KEY_F5,
    [XK_F6] = MA_KEY_F6,
    [XK_F7] = MA_KEY_F7,
    [XK_F8] = MA_KEY_F8,
    [XK_F9] = MA_KEY_F9,
    [XK_F10] = MA_KEY_F10,
    [XK_F11] = MA_KEY_F11,
    [XK_F12] = MA_KEY_F12,
    [XK_F13] = MA_KEY_F13,
    [XK_F14] = MA_KEY_F14,
    [XK_F15] = MA_KEY_F15,
    [XK_F16] = MA_KEY_F16,
    [XK_F17] = MA_KEY_F17,
    [XK_F18] = MA_KEY_F18,
    [XK_F19] = MA_KEY_F19,
    [XK_F20] = MA_KEY_F20,
    [XK_F21] = MA_KEY_F21,
    [XK_F22] = MA_KEY_F22,
    [XK_F23] = MA_KEY_F23,
    [XK_F24] = MA_KEY_F24,
    [XK_F25] = MA_KEY_F25,
    [XK_KP_0] = MA_KEY_KP_0,
    [XK_KP_1] = MA_KEY_KP_1,
    [XK_KP_2] = MA_KEY_KP_2,
    [XK_KP_3] = MA_KEY_KP_3,
    [XK_KP_4] = MA_KEY_KP_4,
    [XK_KP_5] = MA_KEY_KP_5,
    [XK_KP_6] = MA_KEY_KP_6,
    [XK_KP_7] = MA_KEY_KP_7,
    [XK_KP_8] = MA_KEY_KP_8,
    [XK_KP_9] = MA_KEY_KP_9,
    [XK_KP_Decimal] = MA_KEY_KP_DECIMAL,
    [XK_KP_Divide] = MA_KEY_KP_DIVIDE,
    [XK_KP_Multiply] = MA_KEY_KP_MULTIPLY,
    [XK_KP_Subtract] = MA_KEY_KP_SUBTRACT,
    [XK_KP_Add] = MA_KEY_KP_ADD,
    [XK_KP_Enter] = MA_KEY_KP_ENTER,
    [XK_KP_Equal] = MA_KEY_KP_EQUAL,
    [XK_Shift_L] = MA_KEY_LEFT_SHIFT,
    [XK_Control_L] = MA_KEY_LEFT_CONTROL,
    [XK_Alt_L] = MA_KEY_LEFT_ALT,
    [XK_Super_L] = MA_KEY_LEFT_SUPER,
    [XK_Shift_R] = MA_KEY_RIGHT_SHIFT,
    [XK_Control_R] = MA_KEY_RIGHT_CONTROL,
    [XK_Alt_R] = MA_KEY_RIGHT_ALT,
    [XK_Super_R] = MA_KEY_RIGHT_SUPER,
    [XK_Menu] = MA_KEY_MENU,
};

static int mousemap[] = {
    [1] = MA_MOUSE_BUTTON_LEFT,
    [2] = MA_MOUSE_BUTTON_MIDDLE,
    [3] = MA_MOUSE_BUTTON_RIGHT,
    [4] = MA_MOUSE_BUTTON_4,
    [5] = MA_MOUSE_BUTTON_5,
    [6] = MA_MOUSE_BUTTON_6,
    [7] = MA_MOUSE_BUTTON_7,
    [8] = MA_MOUSE_BUTTON_8,
    [9] = MA_MOUSE_BUTTON_9,
};

typedef GLXContext (*glXCreateContextAttribsARBProc)
    (Display*, GLXFBConfig, GLXContext, Bool, const int*);
typedef struct {
    MaWindow parent;
    Display *display;
    Window xwindow;
    Atom wmDeleteMessage;
    GLXFBConfig fbc;
    Colormap cmap;
    GLXContext glxContext;
    int mousex, mousey;
} X11Window;

#define GLX_CONTEXT_MAJOR_VERSION_ARB       0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB       0x2092
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

bool isExtensionSupported(const char *extList, const char *extension) {
  const char *start;
  const char *where, *terminator;
  
  where = strchr(extension, ' ');
  if (where || *extension == '\0')
    return false;

  for (start=extList;;) {
    where = strstr(start, extension);

    if (!where)
      break;

    terminator = where + strlen(extension);

    if ( where == start || *(where - 1) == ' ' )
      if ( *terminator == ' ' || *terminator == '\0' )
        return true;

    start = terminator;
  }

  return false;
}

MaWindow *maWindowNew(int width, int height, const char *title) {
    X11Window *window = malloc(sizeof(X11Window));
    window->parent.hasGlContext = false;
    window->parent.width = width;
    window->parent.height = height;
    window->parent.title = title;
    window->parent.mouseMovedCallback = NULL;
    window->parent.resizeCallback = NULL;
    window->parent.keyPressedCallback = NULL;
    window->parent.keyReleasedCallback = NULL;
    window->parent.mouseButtonPressedCallback = NULL;
    window->parent.mouseButtonReleasedCallback = NULL;
    maWindowsInit(&window->parent.children);

    window->display = XOpenDisplay(NULL);
    if (window->display == NULL) {
        free(window);
        return NULL;
    }

    static int visual_attribs[] = {
      GLX_X_RENDERABLE    , True,
      GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
      GLX_RENDER_TYPE     , GLX_RGBA_BIT,
      GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
      GLX_RED_SIZE        , 8,
      GLX_GREEN_SIZE      , 8,
      GLX_BLUE_SIZE       , 8,
      GLX_ALPHA_SIZE      , 8,
      GLX_DEPTH_SIZE      , 24,
      GLX_STENCIL_SIZE    , 8,
      GLX_DOUBLEBUFFER    , True,
      //GLX_SAMPLE_BUFFERS  , 1,
      //GLX_SAMPLES         , 4,
      None
    };

    int glx_major, glx_minor;

    if ( !glXQueryVersion(window->display, &glx_major, &glx_minor ) || 
       ( ( glx_major == 1 ) && ( glx_minor < 3 ) ) || ( glx_major < 1 ) ){
        return NULL;
    }

    int fbcount = 0;
    GLXFBConfig *fbc = glXChooseFBConfig(window->display, DefaultScreen(window->display), visual_attribs, &fbcount);
    if (!fbc) {
        free(window);
        return NULL;
    }

    int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;

    for (int i=0; i<fbcount; ++i) {
        XVisualInfo *vi = glXGetVisualFromFBConfig( window->display, fbc[i] );
        if ( vi ) {
            int samp_buf, samples;
            glXGetFBConfigAttrib( window->display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf );
            glXGetFBConfigAttrib( window->display, fbc[i], GLX_SAMPLES       , &samples  );
            
            if ( best_fbc < 0 || samp_buf && samples > best_num_samp )
            best_fbc = i, best_num_samp = samples;
            if ( worst_fbc < 0 || !samp_buf || samples < worst_num_samp )
            worst_fbc = i, worst_num_samp = samples;
        }
        XFree( vi );
    }

    window->fbc = fbc[ best_fbc ];
    XFree(fbc);
    XVisualInfo *vi = glXGetVisualFromFBConfig( window->display, window->fbc );
    XSetWindowAttributes swa;
    swa.colormap = window->cmap = XCreateColormap( window->display,
                                           RootWindow( window->display, vi->screen ), 
                                           vi->visual, AllocNone );

    swa.background_pixmap = None ;
    swa.border_pixel      = 0;
    swa.event_mask        = StructureNotifyMask | PointerMotionMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask;
    window->xwindow = XCreateWindow( window->display, RootWindow( window->display, vi->screen ), 
                                     0, 0, width, height, 0, vi->depth, InputOutput, 
                                     vi->visual, 
                                     CWBorderPixel|CWColormap|CWEventMask, &swa );
    if (!window->xwindow) {
        free(window);
        return NULL;
    }

    XFree(vi);
    XStoreName(window->display, window->xwindow, title);

    window->wmDeleteMessage = XInternAtom(window->display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(window->display, window->xwindow, &window->wmDeleteMessage, 1);

    XMapWindow(window->display, window->xwindow);
    XFlush(window->display);
    return (MaWindow *)window;
}

void maWindowFree(MaWindow *window) {
    X11Window *x11window = (X11Window *)window;
    if (window->hasGlContext) {
        glXMakeCurrent(x11window->display, None, NULL);
        glXDestroyContext(x11window->display, x11window->glxContext);
    }
    XDestroyWindow(x11window->display, x11window->xwindow);
    XFreeColormap(x11window->display, x11window->cmap);
    XCloseDisplay(x11window->display);
    maWindowsFree(&window->children);
    free(window);
    window = NULL;
}

bool maWindowMakeGlContext(MaWindow *w, int major, int minor) {
    X11Window *window = (X11Window *)w;
    const char *glxExts = glXQueryExtensionsString( window->display,
                                                    DefaultScreen( window->display ) );

    // NOTE: It is not necessary to create or make current to a context before
    // calling glXGetProcAddressARB
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
            glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );

    window->glxContext = 0;
    if ( !isExtensionSupported( glxExts, "GLX_ARB_create_context" ) ||
       !glXCreateContextAttribsARB ) {
        printf("cant find ext");
        return false;
    }

    int context_attribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 0,
        //GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        None
    };

    window->glxContext = glXCreateContextAttribsARB( window->display, window->fbc, 0,
                                      True, context_attribs );

    XSync( window->display, False );

    if ( !window->glxContext ) {
        return false;
    }

    glXMakeCurrent( window->display, window->xwindow, window->glxContext );
    XSync( window->display, False );

    window->parent.hasGlContext = true;


    int gl_version = gladLoaderLoadGL();
    if (!gl_version) {
        return false;
    }

    return true;
}

bool maWindowPollEvents(MaWindow *window) {
    X11Window *x11window = (X11Window *)window;
    XEvent event;
    if (XPending(x11window->display) > 0) {
        XNextEvent(x11window->display, &event);
        switch (event.type) {
            case ClientMessage:
                if (event.xclient.data.l[0] == x11window->wmDeleteMessage) {
                    return false;
                }
                break;
            case MotionNotify:
                if (event.xmotion.x != x11window->mousex || event.xmotion.y != x11window->mousey) {
                    x11window->mousex = event.xmotion.x;
                    x11window->mousey = event.xmotion.y;
                    if (window->mouseMovedCallback)
                        window->mouseMovedCallback(event.xmotion.x, event.xmotion.y);
                }
                break;
            case ConfigureNotify:
                if (event.xconfigure.width != window->width || event.xconfigure.height != window->height) {
                    window->width = event.xconfigure.width;
                    window->height = event.xconfigure.height;
                    if (window->resizeCallback)
                        window->resizeCallback(event.xconfigure.width, event.xconfigure.height);
                }
                break;
            case KeyPress:
                if (window->keyPressedCallback)
                    window->keyPressedCallback(keymap[XLookupKeysym(&event.xkey, 0)]);
                break;
            case KeyRelease:
                if (window->keyReleasedCallback)
                    window->keyReleasedCallback(keymap[XLookupKeysym(&event.xkey, 0)]);
                break;
            case ButtonPress:
                if (window->mouseButtonPressedCallback)
                    window->mouseButtonPressedCallback(event.xbutton.button);
                break;
            case ButtonRelease:
                if (window->mouseButtonReleasedCallback)
                    window->mouseButtonReleasedCallback(event.xbutton.button);
                break;
        }
    }

    for (int i = 0; i < window->children.len; i++) {
        if (window->children.data[i] == NULL)
            continue;
        if (!maWindowPollEvents(window->children.data[i])) {
            maWindowsRemove(&window->children, i);
        }
    }

    return true;
}

void maWindowSwapBuffers(MaWindow *window) {
    if (window == NULL)
        return;
    X11Window *x11window = (X11Window *)window;
    glXSwapBuffers(x11window->display, x11window->xwindow);
}


int maWindowAddChild(MaWindow *window, int width, int height, const char *title) {
    maWindowsPush(&window->children, maWindowNew(width, height, title));
    return window->children.len - 1;
}

MaWindow *maWindowGetChild(MaWindow *window, int child_id) {
    if (child_id >= window->children.len)
        return NULL;
    return window->children.data[child_id];
}

void maWindowMakeGlContextCurrent(MaWindow *window) {
    if (window == NULL || !window->hasGlContext)
        return;
    X11Window *x11window = (X11Window *)window;
    glXMakeCurrent(x11window->display, x11window->xwindow, x11window->glxContext);
}
