#include <atomic>
#include <cstdarg>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <vector>

#include "util/log.h"

std::atomic<LogLevel> log_level(LogLevel::ERROR);
std::mutex log_mutex;
std::ofstream log_stream;
std::ostream *log_ostream = &std::cerr;
std::string log_filename;

void util::set_log_filename(const char *filename) {
    if (log_stream.is_open()) {
        log_stream.close();
        log_ostream = &std::cerr;
    }

    if (filename) {
        log_filename = filename;
        log_stream.open(std::string(log_filename).c_str());
        log_ostream = &log_stream;
    } else {
        log_filename = std::string();
    }
}

void util::set_log_level(const LogLevel level) { log_level = level; }

LogLevel util::get_log_level() { return log_level; }

static void LOGva(const char *format, va_list ap) {
    va_list apTmp;
    va_copy(apTmp, ap);
    const int size = std::vsnprintf(nullptr, 0, format, apTmp);
    va_end(apTmp);
    if (size < 1)
        return; // Nothing to log

    std::vector<char> buf(size + 1);
    std::vsnprintf(buf.data(), buf.size(), format, ap);

    {
        const std::lock_guard lock(log_mutex);
        log_ostream->write(buf.data(), size);
        log_ostream->flush();
    }

#ifdef _DEBUG
    fputs(buf.data(), stderr);
    fflush(stderr);
#endif
}

void LOG(const char *format, ...) {
    if (!format || log_level < INFO)
        return;

    va_list ap;
    va_start(ap, format);
    LOGva(format, ap);
    va_end(ap);
}

void LOG(const LogLevel level, const char *format, ...) {
    if (!format || log_level < level)
        return;

    va_list ap;
    va_start(ap, format);
    LOGva(format, ap);
    va_end(ap);
}
