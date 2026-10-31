// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_LOGGER_H_
#define ULOG_LOGGER_H_

#include <fmt/format.h>

#include <iterator>
#include <string>
#include <vector>

#include "ulog/common.h"
#include "ulog/formatter.h"
#include "ulog/log_msg.h"
#include "ulog/sinks/sink.h"

namespace ulog {

class Logger {
 public:
  Logger(const std::string& name, level_enum lvl);
  ~Logger() = default;

  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

  const std::string& name() const;
  level_enum level() const;
  void set_level(level_enum lvl);

  template <typename... Args>
  void Trace(const char* fmt, const Args&... args);

  template <typename... Args>
  void Debug(const char* fmt, const Args&... args);

  template <typename... Args>
  void Info(const char* fmt, const Args&... args);

  template <typename... Args>
  void Warn(const char* fmt, const Args&... args);

  template <typename... Args>
  void Error(const char* fmt, const Args&... args);

  template <typename... Args>
  void Critical(const char* fmt, const Args&... args);

 private:
  bool ShouldLog(level_enum lvl) const;

  template <typename... Args>
  void Log(level_enum lvl, const char* fmt, const Args&... args);

  void Sink(LogMsg& msg);

  std::string name_;
  level_enum level_;

  FormatterPtr formatter_ = nullptr;
  std::vector<SinkPtr> sinks_;
};

template <typename... Args>
inline void Logger::Trace(const char* fmt, const Args&... args) {
  Log(level_enum::trace, fmt, args...);
}

template <typename... Args>
inline void Logger::Debug(const char* fmt, const Args&... args) {
  Log(level_enum::debug, fmt, args...);
}

template <typename... Args>
inline void Logger::Info(const char* fmt, const Args&... args) {
  Log(level_enum::info, fmt, args...);
}

template <typename... Args>
inline void Logger::Warn(const char* fmt, const Args&... args) {
  Log(level_enum::warn, fmt, args...);
}

template <typename... Args>
inline void Logger::Error(const char* fmt, const Args&... args) {
  Log(level_enum::err, fmt, args...);
}

template <typename... Args>
inline void Logger::Critical(const char* fmt, const Args&... args) {
  Log(level_enum::critical, fmt, args...);
}

template <typename... Args>
void Logger::Log(level_enum lvl, const char* fmt, const Args&... args) {
  if (!ShouldLog(lvl)) {
    return;
  }

  LogMsg log_msg(&name(), lvl);
  fmt::format_to(std::back_inserter(log_msg.raw), fmt, args...);

  Sink(log_msg);
}

}  // namespace ulog

#endif  // ULOG_LOGGER_H_