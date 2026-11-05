// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "ulog/pattern_formatter.h"

#include <stdexcept>

#include "ulog/flag_formatter.h"
#include "ulog/log_msg.h"

namespace ulog {

PatternFormatter::PatternFormatter(const std::string& pattern)
    : pattern_(pattern) {
  Compile(pattern);
}

PatternFormatter::~PatternFormatter() = default;

void PatternFormatter::Format(LogMsg& msg) {
  std::tm tm = os::ToLocalTime(msg.time);
  for (const auto& formatter : flag_formatters_) {
    formatter->Format(msg, tm);
  }
  fmt::format_to(std::back_inserter(msg.formatted), "{}", "\n");
}

void PatternFormatter::Compile(const std::string& pattern) {
  std::unique_ptr<details::LiteralFormatter> literal = nullptr;
  for (auto it = pattern.begin(); it != pattern.end(); it++) {
    if (*it == '%') {
      if (literal) {
        flag_formatters_.push_back(std::move(literal));
        literal = nullptr;
      }

      if (it + 1 == pattern.end()) {
        throw std::runtime_error("invalid pattern: missing flag after '%'");
      }

      if (*(++it) == '%') {
        if (!literal) {
          literal = std::make_unique<details::LiteralFormatter>();
        }
        literal->AddChar(*it);
      } else {
        HandleFlag(*it);
      }
    } else {
      if (!literal) {
        literal = std::make_unique<details::LiteralFormatter>();
      }
      literal->AddChar(*it);
    }
  }
  if (literal) {
    flag_formatters_.push_back(std::move(literal));
  }
}

void PatternFormatter::HandleFlag(char ch) {
  switch (ch) {
    case 'n':
      flag_formatters_.push_back(std::make_unique<details::NameFormatter>());
      break;
    case 'l':
      flag_formatters_.push_back(std::make_unique<details::LevelFormatter>());
      break;
    case 't':
      flag_formatters_.push_back(
          std::make_unique<details::ThreadIdFormatter>());
      break;
    case 'Y':
      flag_formatters_.push_back(std::make_unique<details::YearFormatter>());
      break;
    case 'm':
      flag_formatters_.push_back(std::make_unique<details::MonthFormatter>());
      break;
    case 'd':
      flag_formatters_.push_back(std::make_unique<details::DayFormatter>());
      break;
    case 'v':
      flag_formatters_.push_back(std::make_unique<details::MessageFormatter>());
      break;
    case '+':
      flag_formatters_.push_back(std::make_unique<details::FullFormatter>());
      break;
    default:
      throw std::runtime_error(fmt::format("invalid flag after'%{}'", ch));
      break;
  }
}

}  // namespace ulog