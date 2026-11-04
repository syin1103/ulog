// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "ulog/flag_formatter.h"

#include <gtest/gtest.h>

#include "ulog/log_msg.h"

using ulog::LogMsg;
using ulog::details::LevelFormatter;
using ulog::details::NameFormatter;

/*
 * TODO(syin1103): refact flag formatter unit tests
 */

TEST(NameFormatterTest, basic) {
  const std::string name = "test_logger";

  LogMsg msg(&name, ulog::level_enum::info);

  NameFormatter name_formatter;
  name_formatter.Format(msg);

  EXPECT_EQ(fmt::to_string(msg.formatted), "test_logger");
}

TEST(LevelFormatterTest, basic) {
  const std::string name = "test_logger";
  LogMsg msg(&name, ulog::level_enum::info);

  LevelFormatter lvl_formatter;
  lvl_formatter.Format(msg);
  EXPECT_EQ(fmt::to_string(msg.formatted),
            std::to_string(static_cast<int>(ulog::level_enum::info)));
}

TEST(MessageFormatterTest, basic) {
  const std::string name = "test_logger";
  LogMsg msg(&name, ulog::level_enum::info);

  fmt::format_to(std::back_inserter(msg.raw), "{}", "This is a test message.");

  ulog::details::MessageFormatter msg_formatter;
  msg_formatter.Format(msg);
  EXPECT_EQ(fmt::to_string(msg.formatted), "This is a test message.");
}

TEST(ThreadIdFormatterTest, basic) {
  const std::string name = "test_logger";
  LogMsg msg(&name, ulog::level_enum::info);

  ulog::details::ThreadIdFormatter thread_id_formatter;
  thread_id_formatter.Format(msg);
  EXPECT_EQ(fmt::to_string(msg.formatted), std::to_string(msg.thread_id));
}
TEST(LiteralFormatterTest, basic) {
  const std::string name = "test_logger";

  LogMsg msg(&name, ulog::level_enum::info);

  ulog::details::LiteralFormatter literal_formatter;
  std::string str = "prefix";
  for (const auto& ch : str) {
    literal_formatter.AddChar(ch);
  }

  literal_formatter.Format(msg);
  EXPECT_EQ(fmt::to_string(msg.formatted), "prefix");
}

class DateFormatterTest : public ::testing::Test {
 protected:
  std::string name_ = "test_logger";
  LogMsg msg{&name_, ulog::level_enum::info};

  void SetUp() override {
    std::tm tm{};
    tm.tm_year = 2026 - 1900;
    tm.tm_mon = 10;
    tm.tm_mday = 3;
    tm.tm_isdst = -1;

    auto timestamp = std::mktime(&tm);
    msg.time = std::chrono::system_clock::from_time_t(timestamp);
  }
};

TEST_F(DateFormatterTest, FormatYear) {
  ulog::details::YearFormatter formatter;
  formatter.Format(msg);
  EXPECT_EQ(fmt::to_string(msg.formatted), "2026");
}

TEST_F(DateFormatterTest, FormatMonth) {
  ulog::details::MonthFormatter formatter;
  formatter.Format(msg);
  EXPECT_EQ(fmt::to_string(msg.formatted), "11");
}

TEST_F(DateFormatterTest, FormatDay) {
  ulog::details::DayFormatter formatter;
  formatter.Format(msg);
  EXPECT_EQ(fmt::to_string(msg.formatted), "03");
}