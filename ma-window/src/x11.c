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

typedef struct {
    MaWindow parent;
} X11Window;

MaWindow *maWindowNew(int width, int height, const char *title) {
    X11Window *window = malloc(sizeof(X11Window));
    window->parent.width = width;
    window->parent.height = height;
    window->parent.title = title;
    return (MaWindow *)window;
}