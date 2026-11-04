// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_PATTERN_FORMATTER_H_
#define ULOG_PATTERN_FORMATTER_H_

#include <memory>
#include <string>
#include <vector>

#include "ulog/formatter.h"

namespace ulog {

class FlagFormatter;

class PatternFormatter : public Formatter {
 public:
  explicit PatternFormatter(const std::string& pattern);
  ~PatternFormatter() override;

  virtual void Format(LogMsg& msg) override;

 private:
  void Compile(const std::string& pattern);
  void HandleFlag(char ch);

  std::string pattern_;
  std::vector<std::unique_ptr<FlagFormatter>> flag_formatters_;
};

}  // namespace ulog

#endif  // ULOG_PATTERN_FORMATTER_H_