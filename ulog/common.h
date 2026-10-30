// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_COMMON_H_
#define ULOG_COMMON_H_

#include <string>

namespace ulog {

enum class level_enum {
  trace = 0,
  debug = 1,
  info = 2,
  warn = 3,
  err = 4,
  critical = 5,
  off = 6
};

}

#endif  // ULOG_COMMON_H_