// Copyright (C) 2023 devinr

// This file is part of Macademia.

// Macademia is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Macademia is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Macademia.  If not, see <http://www.gnu.org/licenses/>.

#include <macademia/log.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void __maLog(const char* file, int line, const char *func, FILE *stream, MaLogLevel level, const char *message, int argc, ...) {
    if (argc % 2 != 0) return;
    va_list argv;
    va_start(argv, argc);

    if (stream == NULL) {
        stream = stdout;
    }

    char levelstr[5];
    switch (level ){
        case MaInfo:
            strncpy(levelstr, "info", 4);
            break;
        case MaWarn:
            strncpy(levelstr, "warn", 4);
            break;
        case MaError:
            strncpy(levelstr, "error", 5);
            break;
        case MaFatal:
            strncpy(levelstr, "fatal", 5);
            break;
    }

    time_t t = time(0);

    fprintf(
        stream,
        "{\n\t\"time\": %ld,\n"
        "\t\"level\": \"%s\",\n"
        "\t\"file\": \"%s\",\n"
        "\t\"line\": %d,\n"
        "\t\"function\": \"%s\",\n"
        "\t\"message\": \"%s\"",
        t, levelstr, file, line, func, message
    );

    if (argc > 0) {
        fprintf(stream, ",\n");
    } else {
        fprintf(stream, "\n");
    }

    for (int i = 0; i < argc; i++) {
        fprintf(stream, "\t\"%s\": ", va_arg(argv, const char *));
        fprintf(stream, "\"%s\"", va_arg(argv, const char *));
        i++;
        if (i + 1 < argc) {
            fprintf(stream, ",\n");
        } else {
            fprintf(stream, "\n");
        }
    }

    fprintf(stream, "}\n");

    va_end(argv);
}