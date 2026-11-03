// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_FLAG_FORMATTER_H_
#define ULOG_FLAG_FORMATTER_H_

#include <fmt/format.h>
#include <ulog/log_msg.h>

namespace ulog {

class FlagFormatter {
 public:
  FlagFormatter() = default;
  virtual ~FlagFormatter() = default;

  virtual void Format(LogMsg& msg) = 0;

 private:
};

namespace details {

// logger name: %n
class NameFormatter : public FlagFormatter {
 public:
  void Format(LogMsg& msg) override {
    fmt::format_to(std::back_inserter(msg.formatted), "{}", *msg.logger_name);
  }
};

// log level: %l
class LevelFormatter : public FlagFormatter {
 public:
  void Format(LogMsg& msg) override {
    fmt::format_to(std::back_inserter(msg.formatted), "{}",
                   static_cast<int>(msg.level));
  }
};

// thread id formatter : %t
class ThreadIdFormatter : public FlagFormatter {
 public:
  void Format(LogMsg& msg) override {
    fmt::format_to(std::back_inserter(msg.formatted), "{}", msg.thread_id);
  }
};

// year formatter: %Y
class YearFormatter : public FlagFormatter {
 public:
  void Format(LogMsg& msg) override {
    // TODO(syin1103): optimize, avoid redundant calls to ToLocalTime
    const auto tm = os::ToLocalTime(msg.time);
    fmt::format_to(std::back_inserter(msg.formatted), "{:04d}",
                   tm.tm_year + 1900);
  }
};

// month formatter: %m
class MonthFormatter : public FlagFormatter {
 public:
  void Format(LogMsg& msg) override {
    const auto tm = os::ToLocalTime(msg.time);
    fmt::format_to(std::back_inserter(msg.formatted), "{:02d}", tm.tm_mon + 1);
  }
};

// day formatter: %d
class DayFormatter : public FlagFormatter {
 public:
  void Format(LogMsg& msg) override {
    const auto tm = os::ToLocalTime(msg.time);
    fmt::format_to(std::back_inserter(msg.formatted), "{:02d}", tm.tm_mday);
  }
};

// message formatter: %v
class MessageFormatter : public FlagFormatter {
 public:
  void Format(LogMsg& msg) override {
    fmt::format_to(std::back_inserter(msg.formatted), "{}",
                   fmt::string_view(msg.raw.data(), msg.raw.size()));
  }
};

// aggregate user char to display
class AggregateFormatter : public FlagFormatter {
 public:
  void Format(LogMsg& msg) override {
    fmt::format_to(std::back_inserter(msg.formatted), "{}", str_);
  }

  void AddChar(char c) { str_ += c; }

 private:
  std::string str_ = "";
};

}  // namespace details

}  // namespace ulog

#endif  // ULOG_FLAG_FORMATTER_H_