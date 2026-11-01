// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "ulog/logger.h"

#include "ulog/log_msg.h"

namespace ulog {

Logger::Logger(const std::string& name) : name_(name) {}

Logger::Logger(const std::string& name, SinkPtr sink) : Logger(name, {sink}) {}

Logger::Logger(const std::string& name, SinksInitList sinks)
    : Logger(name, sinks.begin(), sinks.end()) {}

const std::string& Logger::name() const { return name_; }

level_enum Logger::level() const { return level_; };
void Logger::set_level(level_enum lvl) { level_ = lvl; }

bool Logger::ShouldLog(level_enum lvl) const { return lvl >= level_; }

void Logger::Sink(LogMsg& msg) {
  formatter_->Format(msg);
  for (const auto& sink : sinks_) {
    sink->SinkIt(msg);
  }
}

}  // namespace ulog
