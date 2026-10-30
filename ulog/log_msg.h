// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_LOG_MSG_H_
#define ULOG_LOG_MSG_H_

#include <fmt/format.h>

#include <string>

#include "ulog/common.h"

namespace ulog {

struct LogMsg {
  LogMsg(const std::string* name, level_enum lvl)
      : logger_name(name), level(lvl) {}

  LogMsg(const LogMsg&) = delete;
  LogMsg& operator=(const LogMsg&) = delete;

  const std::string* logger_name;
  level_enum level;
  fmt::memory_buffer raw;
  fmt::memory_buffer formatted;
};

}  // namespace ulog

#endif  // ULOG_LOG_MSG_H_