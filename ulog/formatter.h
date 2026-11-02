// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_FORMATTER_H_
#define ULOG_FORMATTER_H_

namespace ulog {

class LogMsg;

class Formatter {
 public:
  Formatter() = default;
  virtual ~Formatter() = default;

  Formatter(const Formatter&) = delete;
  Formatter& operator=(const Formatter&) = delete;

  virtual void Format(LogMsg& msg) = 0;
};

}  // namespace ulog

#endif  // ULOG_FORMATTER_H_