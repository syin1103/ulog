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

}  // namespace ulog

#endif  // ULOG_FLAG_FORMATTER_H_