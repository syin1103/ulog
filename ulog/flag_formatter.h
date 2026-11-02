// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_FLAG_FORMATTER_H_
#define ULOG_FLAG_FORMATTER_H_

#include "ulog/formatter.h"

namespace ulog {

class FlagFormatter : public Formatter {
 public:
  FlagFormatter() = default;
  virtual ~FlagFormatter() = default;

  void Format(LogMsg& msg) override {}

 private:
};

}  // namespace ulog

#endif  // ULOG_FLAG_FORMATTER_H_