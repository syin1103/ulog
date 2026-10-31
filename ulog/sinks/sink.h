// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_SINKS_SINK_H_
#define ULOG_SINKS_SINK_H_

#include <fmt/format.h>

#include <string>

#include "ulog/log_msg.h"

namespace ulog {
namespace sinks {

class Sink {
 public:
  Sink() = default;
  virtual ~Sink() = default;

  Sink(const Sink&) = delete;
  Sink& operator=(const Sink&) = delete;

  virtual void SinkIt(const LogMsg& msg);
};

inline void Sink::SinkIt(const LogMsg& msg) {
  // TODO(syin1103): Implement sink logic
  fmt::print("{}",
             fmt::string_view(msg.formatted.data(), msg.formatted.size()));
}

}  // namespace sinks
}  // namespace ulog

#endif  // ULOG_SINKS_SINK_H_