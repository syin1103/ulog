// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "ulog/flag_formatter.h"

#include <gtest/gtest.h>

#include "ulog/log_msg.h"

using ulog::LogMsg;
using ulog::details::LevelFormatter;
using ulog::details::NameFormatter;

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