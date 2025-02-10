/*
 * Copyright (c) 2025 notchum
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "logger.hpp"

fmt::v7::color level_colors[] = {
  fmt::color::cyan,       // "\x1b[36m",
  fmt::color::lime_green, // "\x1b[32m",
  fmt::color::yellow,     // "\x1b[33m",
  fmt::color::red,        // "\x1b[31m",
  fmt::color::magenta     // "\x1b[35m"
};

static const char *level_names[] = {
  "DEBUG",
  "INFO ",
  "WARN ",
  "ERROR",
  "FATAL"
};

std::FILE *log_file = NULL;
bool is_file_set = false;

void set_log_file(const char *file_name) {
  if (!is_file_set) {
    log_file = std::fopen(file_name, "w");
    if (!log_file) {
      throw fmt::system_error(errno, "cannot open file '{}'", file_name);
    }
    is_file_set = true;
    fmt::print(
      "┌{0:─^{2}}┐\n"
      "│{1: ^{2}}│\n"
      "└{0:─^{2}}┘\n", "", file_name, 6 + strlen(file_name));
  }
}

void vlog(int log_level, const char* file, int line, fmt::string_view str, fmt::format_args args) {
  static bool otf = false;
  if (!is_file_set && !otf) {
    fmt::print("hey uh you never set a file to log broh\n");
    otf = true;
    return;
  }
  else if (is_file_set) {
    /* get time */
    time_t t = time(NULL);
    struct tm *info = localtime(&t);
    char buf[16];
    buf[strftime(buf, sizeof(buf), "%H:%M:%S", info)] = '\0';

    /* print time -> log level -> message */
    fmt::print("{} ", buf);
#ifdef USE_LINE_NO
    fmt::print("{}:{}: ", file, line);
#endif
    fmt::print(fmt::fg(level_colors[log_level]) | fmt::emphasis::bold, "{} ", level_names[log_level]);
    fmt::vprint(str, args);

    /* write the same stuff to file */
    fmt::print(log_file, "{} ", buf);
    fmt::print(log_file, "{} ", level_names[log_level]);
    fmt::vprint(log_file, str, args);
  }
}
