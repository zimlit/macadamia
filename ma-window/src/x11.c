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

typedef struct {
    MaWindow parent;
    Display *display;
    Window xwindow;
    Atom wmDeleteMessage;
} X11Window;

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

    int blackColor = BlackPixel(window->display, DefaultScreen(window->display));
    window->xwindow = XCreateSimpleWindow(window->display, DefaultRootWindow(window->display), 0, 0, width, height, 0, blackColor, blackColor);
    XSelectInput(window->display, window->xwindow, StructureNotifyMask);

    window->wmDeleteMessage = XInternAtom(window->display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(window->display, window->xwindow, &window->wmDeleteMessage, 1);

    XMapWindow(window->display, window->xwindow);
    XFlush(window->display);
    return (MaWindow *)window;
}

void maWindowFree(MaWindow *window) {
    X11Window *x11window = (X11Window *)window;
    XDestroyWindow(x11window->display, x11window->xwindow);
    XCloseDisplay(x11window->display);
    free(window);
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