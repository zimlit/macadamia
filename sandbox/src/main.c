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
#ifdef WIN32
    #include <windows.h>
#endif
#include <GL/gl.h>
#include <stdio.h>

void onMouse(int btn) {
    printf("Mouse %d\n", btn);
}
int main() {
    MaWindow *window = maWindowNew(640, 480, "Hello, World!");
    if (!window)
        return 1;
    if (!maWindowMakeGlContext(window, 4, 0))
        return 1;
    int child = maWindowAddChild(window, 320, 240, "Child");
    maWindowMakeGlContext(maWindowGetChild(window, child), 4, 0);
    maWindowMouseButtonPressedCallback(window, onMouse);
    maWindowMouseButtonReleasedCallback(window, onMouse);
    while (maWindowPollEvents(window)) {
        maWindowMakeGlContextCurrent(window);
        glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        maWindowSwapBuffers(window);
        maWindowMakeGlContextCurrent(maWindowGetChild(window, child));
        glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        maWindowSwapBuffers(maWindowGetChild(window, child));
    }
    maWindowFree(window);
    return 0;
}