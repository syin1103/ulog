// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_LOGGER_H_
#define ULOG_LOGGER_H_

#include <fmt/format.h>

#include <string>

#include "ulog/common.h"

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

  std::string name_;
  level_enum level_;
};

}  // namespace ulog

#endif  // ULOG_LOGGER_H_