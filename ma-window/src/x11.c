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
#include <GL/glx.h>
#include <GL/gl.h>
#include <stdio.h>
#include <string.h>

typedef GLXContext (*glXCreateContextAttribsARBProc)
    (Display*, GLXFBConfig, GLXContext, Bool, const int*);

typedef struct {
    MaWindow parent;
    Display *display;
    Window xwindow;
    Atom wmDeleteMessage;
    GLXFBConfig fbc;
    Colormap cmap;
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
    window->parent.width = width;
    window->parent.height = height;
    window->parent.title = title;

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
    if (!fbc)
        return NULL;

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
    swa.event_mask        = StructureNotifyMask;
    window->xwindow = XCreateWindow( window->display, RootWindow( window->display, vi->screen ), 
                                     0, 0, width, height, 0, vi->depth, InputOutput, 
                                     vi->visual, 
                                     CWBorderPixel|CWColormap|CWEventMask, &swa );
    if (!window->xwindow) {
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
    XDestroyWindow(x11window->display, x11window->xwindow);
    XFreeColormap(x11window->display, x11window->cmap);
    XCloseDisplay(x11window->display);
    free(window);
}

bool maWindowMakeGlContext(MaWindow *w) {
    X11Window *window = (X11Window *)w;
    const char *glxExts = glXQueryExtensionsString( window->display,
                                                    DefaultScreen( window->display ) );

    // NOTE: It is not necessary to create or make current to a context before
    // calling glXGetProcAddressARB
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
            glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );

    GLXContext ctx = 0;
    if ( !isExtensionSupported( glxExts, "GLX_ARB_create_context" ) ||
       !glXCreateContextAttribsARB ) {
        printf("cant find ext");
        return false;
    }

    int context_attribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
        GLX_CONTEXT_MINOR_VERSION_ARB, 0,
        //GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        None
    };

    ctx = glXCreateContextAttribsARB( window->display, window->fbc, 0,
                                      True, context_attribs );

    XSync( window->display, False );

    if ( !ctx ) {
        printf("Failed to create GL context");
        return false;
    }

    glXMakeCurrent( window->display, window->xwindow, ctx );
    XSync( window->display, False );

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
        }
    }

    return true;
}

void maWindowSwapBuffers(MaWindow *window) {
    X11Window *x11window = (X11Window *)window;
    glXSwapBuffers(x11window->display, x11window->xwindow);
}