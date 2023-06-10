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

#include <stdio.h>

typedef enum {
    MaInfo,
    MaWarn,
    MaError,
    MaFatal,
} MaLogLevel;

void __maLog(const char* file, int line, const char *func, FILE *stream, MaLogLevel level, const char *message, const char *fields[]);

#define MA_LOG(stream, level, fmt, fields) __maLog(__FILE__, __LINE__, __func__, stream, level, fmt, fields)
#define MA_LOGF(stream, level, fmt, fields, ...) __maLog(__FILE__, __LINE__, __func__, stream, level, fmt, fields, __VA_ARGS__)

#endif