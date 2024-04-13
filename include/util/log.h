#ifndef LOG_H
#define LOG_H
#pragma once

enum LogLevel {
        NONE = 0,    // Default log level: do not log
        FATAL = 1,   // Something failed and we CANNOT continue the execution
        ERROR = 2,   // Something failed, the UI should show this, and we can continue
        WARNING = 3, // Something failed, the UI don't need to show this, and we can continue
        INFO = 4,    // Information about some important event
        VERBOSE = 5, // Information step by step
};

namespace util {

void set_log_filename(const char* filename);
void set_log_level(LogLevel level);
LogLevel get_log_level();

} // namespace util

void LOG(const char* format, ...);
void LOG(LogLevel level, const char* format, ...);

#endif // LOG_H
