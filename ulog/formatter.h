// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_FORMATTER_H_
#define ULOG_FORMATTER_H_

#include "ulog/log_msg.h"

namespace ulog {

class Formatter {
 public:
  Formatter() = default;
  virtual ~Formatter() = default;

  Formatter(const Formatter&) = delete;
  Formatter& operator=(const Formatter&) = delete;

  virtual void Format(LogMsg& msg);
};

inline void Formatter::Format(LogMsg& msg) {
  // TODO(syin1103): Implement formatting logic
  fmt::format_to(std::back_inserter(msg.formatted), "[TODO]: {}",
                 fmt::string_view(msg.raw.data(), msg.raw.size()));
}

}  // namespace ulog

#endif  // ULOG_FORMATTER_H_