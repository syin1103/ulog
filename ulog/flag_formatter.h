// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_FLAG_FORMATTER_H_
#define ULOG_FLAG_FORMATTER_H_

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
  void Format(LogMsg& msg) override {}
};

// log level: %l
class LevelFormatter : public FlagFormatter {
 public:
  void Format(LogMsg& msg) override {}
};

// thread id formatter : %t
class ThreadIdFormatter : public FlagFormatter {
 public:
  void Format(LogMsg& msg) override {}
};

// year formatter: %Y
class YearFormatter : public FlagFormatter {
 public:
  void Format(LogMsg& msg) override {}
};

// month formatter: %m
class MonthFormatter : public FlagFormatter {
 public:
  void Format(LogMsg& msg) override {}
};

// day formatter: %d
class DayFormatter : public FlagFormatter {
 public:
  void Format(LogMsg& msg) override {}
};

// message formatter: %v
class MessageFormatter : public FlagFormatter {
 public:
  void Format(LogMsg& msg) override {}
};

// aggregate user char to display
class AggregateFormatter : public FlagFormatter {
 public:
  void Format(LogMsg& msg) override {}
};

}  // namespace details

}  // namespace ulog

#endif  // ULOG_FLAG_FORMATTER_H_