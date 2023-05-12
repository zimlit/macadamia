// Copyright (C) 2023 Devin Rockwell
// 
// This file is part of macademia.
// 
// macademia is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// macademia is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with macademia.  If not, see <http://www.gnu.org/licenses/>.

#ifndef MA_WINDOW_H
#define MA_WINDOW_H

#include <stdbool.h>


/* The unknown key */
#define MA_KEY_UNKNOWN            -1

/* Printable keys */
#define MA_KEY_SPACE              32
#define MA_KEY_APOSTROPHE         39  /* ' */
#define MA_KEY_COMMA              44  /* , */
#define MA_KEY_MINUS              45  /* - */
#define MA_KEY_PERIOD             46  /* . */
#define MA_KEY_SLASH              47  /* / */
#define MA_KEY_0                  48
#define MA_KEY_1                  49
#define MA_KEY_2                  50
#define MA_KEY_3                  51
#define MA_KEY_4                  52
#define MA_KEY_5                  53
#define MA_KEY_6                  54
#define MA_KEY_7                  55
#define MA_KEY_8                  56
#define MA_KEY_9                  57
#define MA_KEY_SEMICOLON          59  /* ; */
#define MA_KEY_EQUAL              61  /* = */
#define MA_KEY_A                  65
#define MA_KEY_B                  66
#define MA_KEY_C                  67
#define MA_KEY_D                  68
#define MA_KEY_E                  69
#define MA_KEY_F                  70
#define MA_KEY_G                  71
#define MA_KEY_H                  72
#define MA_KEY_I                  73
#define MA_KEY_J                  74
#define MA_KEY_K                  75
#define MA_KEY_L                  76
#define MA_KEY_M                  77
#define MA_KEY_N                  78
#define MA_KEY_O                  79
#define MA_KEY_P                  80
#define MA_KEY_Q                  81
#define MA_KEY_R                  82
#define MA_KEY_S                  83
#define MA_KEY_T                  84
#define MA_KEY_U                  85
#define MA_KEY_V                  86
#define MA_KEY_W                  87
#define MA_KEY_X                  88
#define MA_KEY_Y                  89
#define MA_KEY_Z                  90
#define MA_KEY_LEFT_BRACKET       91  /* [ */
#define MA_KEY_BACKSLASH          92  /* \ */
#define MA_KEY_RIGHT_BRACKET      93  /* ] */
#define MA_KEY_GRAVE_ACCENT       96  /* ` */
// #define MA_KEY_WORLD_1            161 /* non-US #1 */
// #define MA_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define MA_KEY_ESCAPE             256
#define MA_KEY_ENTER              257
#define MA_KEY_TAB                258
#define MA_KEY_BACKSPACE          259
#define MA_KEY_INSERT             260
#define MA_KEY_DELETE             261
#define MA_KEY_RIGHT              262
#define MA_KEY_LEFT               263
#define MA_KEY_DOWN               264
#define MA_KEY_UP                 265
#define MA_KEY_PAGE_UP            266
#define MA_KEY_PAGE_DOWN          267
#define MA_KEY_HOME               268
#define MA_KEY_END                269
#define MA_KEY_CAPS_LOCK          280
#define MA_KEY_SCROLL_LOCK        281
#define MA_KEY_NUM_LOCK           282
#define MA_KEY_PRINT_SCREEN       283
#define MA_KEY_PAUSE              284
#define MA_KEY_F1                 290
#define MA_KEY_F2                 291
#define MA_KEY_F3                 292
#define MA_KEY_F4                 293
#define MA_KEY_F5                 294
#define MA_KEY_F6                 295
#define MA_KEY_F7                 296
#define MA_KEY_F8                 297
#define MA_KEY_F9                 298
#define MA_KEY_F10                299
#define MA_KEY_F11                300
#define MA_KEY_F12                301
#define MA_KEY_F13                302
#define MA_KEY_F14                303
#define MA_KEY_F15                304
#define MA_KEY_F16                305
#define MA_KEY_F17                306
#define MA_KEY_F18                307
#define MA_KEY_F19                308
#define MA_KEY_F20                309
#define MA_KEY_F21                310
#define MA_KEY_F22                311
#define MA_KEY_F23                312
#define MA_KEY_F24                313
#define MA_KEY_F25                314
#define MA_KEY_KP_0               320
#define MA_KEY_KP_1               321
#define MA_KEY_KP_2               322
#define MA_KEY_KP_3               323
#define MA_KEY_KP_4               324
#define MA_KEY_KP_5               325
#define MA_KEY_KP_6               326
#define MA_KEY_KP_7               327
#define MA_KEY_KP_8               328
#define MA_KEY_KP_9               329
#define MA_KEY_KP_DECIMAL         330
#define MA_KEY_KP_DIVIDE          331
#define MA_KEY_KP_MULTIPLY        332
#define MA_KEY_KP_SUBTRACT        333
#define MA_KEY_KP_ADD             334
#define MA_KEY_KP_ENTER           335
#define MA_KEY_KP_EQUAL           336
#define MA_KEY_LEFT_SHIFT         340
#define MA_KEY_LEFT_CONTROL       341
#define MA_KEY_LEFT_ALT           342
#define MA_KEY_LEFT_SUPER         343
#define MA_KEY_RIGHT_SHIFT        344
#define MA_KEY_RIGHT_CONTROL      345
#define MA_KEY_RIGHT_ALT          346
#define MA_KEY_RIGHT_SUPER        347
#define MA_KEY_MENU               348

#define MA_KEY_LAST               MA_KEY_MENU

#define MA_MOUSE_BUTTON_1         0
#define MA_MOUSE_BUTTON_2         1
#define MA_MOUSE_BUTTON_3         2
#define MA_MOUSE_BUTTON_4         3
#define MA_MOUSE_BUTTON_5         4
#define MA_MOUSE_BUTTON_6         5
#define MA_MOUSE_BUTTON_7         6
#define MA_MOUSE_BUTTON_8         7
#define MA_MOUSE_BUTTON_9         8
#define MA_MOUSE_BUTTON_10        9
#define MA_MOUSE_BUTTON_LAST      MA_MOUSE_BUTTON_8
#define MA_MOUSE_BUTTON_LEFT      MA_MOUSE_BUTTON_1
#define MA_MOUSE_BUTTON_RIGHT     MA_MOUSE_BUTTON_2
#define MA_MOUSE_BUTTON_MIDDLE    MA_MOUSE_BUTTON_3


typedef struct MaWindow MaWindow;
typedef struct MaWindows {
    int len;
    int cap;
    MaWindow **data;
} MaWindows;

void maWindowsInit(MaWindows *windows);
void maWindowsFree(MaWindows *windows);
void maWindowsPush(MaWindows *windows, MaWindow *window);
void maWindowsRemove(MaWindows *windows, int idx);
typedef struct MaWindow {
    int width;
    int height;
    const char *title;
    bool hasGlContext;
    MaWindows children;
    void (*mouseMovedCallback)(int x, int y);
    void (*resizeCallback)(int width, int height);
    void (*keyPressedCallback)(int key);
    void (*keyReleasedCallback)(int key);
    void (*mouseButtonPressedCallback)(int button);
    void (*mouseButtonReleasedCallback)(int button);
} MaWindow;

MaWindow *maWindowNew(int width, int height, const char *title);
void maWindowFree(MaWindow *window);
bool maWindowPollEvents(MaWindow *window);
void maWindowSwapBuffers(MaWindow *window);
int maWindowAddChild(MaWindow *window, int width, int height, const char *title);
MaWindow *maWindowGetChild(MaWindow *window, int child_id);

void maWindowMouseMovedCallback(MaWindow *window, void (*callback)(int x, int y));
void maWindowResizeCallback(MaWindow *window, void (*callback)(int width, int height));
void maWindowKeyPressedCallback(MaWindow *window, void (*callback)(int key));
void maWindowKeyReleasedCallback(MaWindow *window, void (*callback)(int key));
void maWindowMouseButtonPressedCallback(MaWindow *window, void (*callback)(int button));
void maWindowMouseButtonReleasedCallback(MaWindow *window, void (*callback)(int button));

bool maWindowMakeGlContext(MaWindow *window, int glVersionMajor, int glVersionMinor);
void maWindowMakeGlContextCurrent(MaWindow *window);

#endif