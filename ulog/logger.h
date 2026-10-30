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

 private:
  std::string name_;
  level_enum level_;
};

}  // namespace ulog

#endif  // ULOG_LOGGER_H_