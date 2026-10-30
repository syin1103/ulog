// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "ulog/logger.h"

#include "ulog/log_msg.h"

namespace ulog {

Logger::Logger(const std::string& name, level_enum lvl)
    : name_(name), level_(lvl) {}

const std::string& Logger::name() const { return name_; }

level_enum Logger::level() const { return level_; };
void Logger::set_level(level_enum lvl) { level_ = lvl; }

template <typename... Args>
void Logger::Trace(const char* fmt, const Args&... args) {}

template <typename... Args>
void Logger::Debug(const char* fmt, const Args&... args) {}

template <typename... Args>
void Logger::Info(const char* fmt, const Args&... args) {}

template <typename... Args>
void Logger::Warn(const char* fmt, const Args&... args) {}

template <typename... Args>
void Logger::Error(const char* fmt, const Args&... args) {}

template <typename... Args>
void Logger::Critical(const char* fmt, const Args&... args) {}

bool Logger::ShouldLog(level_enum lvl) const { return true; }

template <typename... Args>
void Log(level_enum lvl, const char* fmt, const Args&... args) {}

}  // namespace ulog
