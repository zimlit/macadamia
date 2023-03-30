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

void maWindowMouseMovedCallback(MaWindow *window, void (*callback)(int x, int y)) {
    window->mouseMovedCallback = callback;
}

void maWindowResizeCallback(MaWindow *window, void (*callback)(int width, int height)) {
    window->resizeCallback = callback;
}

void maWindowKeyPressedCallback(MaWindow *window, void (*callback)(int key)) {
    window->keyPressedCallback = callback;
}

void maWindowKeyReleasedCallback(MaWindow *window, void (*callback)(int key)) {
    window->keyReleasedCallback = callback;
}

void maWindowMouseButtonPressedCallback(MaWindow *window, void (*callback)(int button)) {
    window->mouseButtonPressedCallback = callback;
}

void maWindowMouseButtonReleasedCallback(MaWindow *window, void (*callback)(int button)) {
    window->mouseButtonReleasedCallback = callback;
}