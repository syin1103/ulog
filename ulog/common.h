// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_COMMON_H_
#define ULOG_COMMON_H_

#include <initializer_list>
#include <memory>
#include <string>

namespace ulog {

class Formatter;

namespace sinks {
class Sink;
}

using FormatterPtr = std::shared_ptr<Formatter>;
using SinkPtr = std::shared_ptr<sinks::Sink>;
using SinksInitList = std::initializer_list<SinkPtr>;

enum class level_enum {
  trace = 0,
  debug = 1,
  info = 2,
  warn = 3,
  err = 4,
  critical = 5,
  off = 6
};

}  // namespace ulog

#endif  // ULOG_COMMON_H_