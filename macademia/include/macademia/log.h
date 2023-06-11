// Copyright (C) 2023 devinr
// 
// This file is part of Macademia.
// 
// Macademia is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Macademia is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Macademia.  If not, see <http://www.gnu.org/licenses/>.

#ifndef MACADEMIA_LOG_H
#define MACADEMIA_LOG_H

#define MA_LOG_FILE stdout
#define MA_LOG_LEVEL MaInfo

#include <stdio.h>

typedef enum {
    MaInfo,
    MaWarn,
    MaError,
    MaFatal,
} MaLogLevel;

void __maLog(const char* file, int line, const char *func, FILE *stream, MaLogLevel level, const char *message, int args, ...);

#define NUMARGS(...)  (sizeof((const char *[]){__VA_ARGS__})/sizeof(const char *))

#define MA_LOG(level, message) __maLog(__FILE__, __LINE__, __func__, MA_LOG_FILE, level, message, 0)
#define MA_LOG_FIELDS(level, message, ...) __maLog(__FILE__, __LINE__, __func__, MA_LOG_FILE, level, message, NUMARGS(__VA_ARGS__), __VA_ARGS__)

#endif