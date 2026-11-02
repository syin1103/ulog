// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "ulog/pattern_formatter.h"

#include "ulog/flag_formatter.h"
#include "ulog/log_msg.h"

namespace ulog {

PatternFormatter::PatternFormatter(const std::string& pattern)
    : pattern_(pattern) {}

PatternFormatter::~PatternFormatter() = default;

void PatternFormatter::Format(LogMsg& msg) {
  for (const auto& formatter : flag_formatters_) {
    formatter->Format(msg);
  }
  // TODO(syin1103): just for test
  fmt::format_to(std::back_inserter(msg.formatted), "[TODO]: {}",
                 fmt::string_view(msg.raw.data(), msg.raw.size()));
}

}  // namespace ulog