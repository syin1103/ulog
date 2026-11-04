// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "ulog/pattern_formatter.h"

#include <fmt/format.h>
#include <gtest/gtest.h>

#include <string>

#include "ulog/common.h"
#include "ulog/log_msg.h"

using ulog::PatternFormatter;

class PatternFormatterTest : public ::testing::Test,
                             public ::testing::WithParamInterface<
                                 std::pair<std::string, std::string>> {
 protected:
  std::string logger_name_ = "test_logger";
  ulog::LogMsg msg{&logger_name_, ulog::level_enum::info};

  void SetUp() override {
    std::tm tm{};
    tm.tm_year = 2026 - 1900;
    tm.tm_mon = 10;
    tm.tm_mday = 3;
    tm.tm_isdst = -1;

    auto timestamp = std::mktime(&tm);
    msg.time = std::chrono::system_clock::from_time_t(timestamp);

    fmt::format_to(std::back_inserter(msg.raw), "{}", "Hello World");
  }
};

TEST_F(PatternFormatterTest, CompileLiteral) {
  PatternFormatter formatter("%v");
  formatter.Format(msg);
  EXPECT_EQ(fmt::to_string(msg.formatted), "Hello World\n");
}

TEST_F(PatternFormatterTest, CompileSingleFlag) {
  PatternFormatter formatter("%n");
  formatter.Format(msg);
  EXPECT_EQ(fmt::to_string(msg.formatted), "test_logger\n");
}

TEST_F(PatternFormatterTest, CompileThreadId) {
  PatternFormatter formatter("[%t]");
  formatter.Format(msg);
  EXPECT_EQ(fmt::to_string(msg.formatted),
            fmt::format("[{}]\n", msg.thread_id));
}

TEST_F(PatternFormatterTest, CompileEscapedPercent) {
  PatternFormatter formatter("Progress: 100%%");
  formatter.Format(msg);
  EXPECT_EQ(fmt::to_string(msg.formatted), "Progress: 100%\n");
}

TEST_F(PatternFormatterTest, CompileEscapedPercentWithFlag) {
  PatternFormatter formatter("100%% [%n]");
  formatter.Format(msg);
  EXPECT_EQ(fmt::to_string(msg.formatted), "100% [test_logger]\n");
}

TEST_F(PatternFormatterTest, CompileMultipleFlags) {
  PatternFormatter formatter("%Y-%m-%d");
  formatter.Format(msg);
  EXPECT_EQ(fmt::to_string(msg.formatted), "2026-11-03\n");
}

TEST_F(PatternFormatterTest, CompileMixedPattern) {
  PatternFormatter formatter("[%l] %n: %v");
  formatter.Format(msg);
  EXPECT_EQ(fmt::to_string(msg.formatted), "[info] test_logger: Hello World\n");
}

TEST_F(PatternFormatterTest, ThrowOnMissingFlag) {
  EXPECT_THROW(PatternFormatter("%"), std::runtime_error);
}

TEST_F(PatternFormatterTest, ThrowOnUnknownFlag) {
  EXPECT_THROW(PatternFormatter("%q"), std::runtime_error);
}

TEST_P(PatternFormatterTest, Compile) {
  const auto& [pattern, expected] = GetParam();
  PatternFormatter formatter(pattern);
  formatter.Format(msg);
  EXPECT_EQ(fmt::to_string(msg.formatted), expected);
}

INSTANTIATE_TEST_SUITE_P(
    PatternCases, PatternFormatterTest,
    ::testing::Values(
        std::make_pair("", "\n"), std::make_pair("hello", "hello\n"),
        std::make_pair("%n", "test_logger\n"), std::make_pair("%l", "info\n"),
        std::make_pair("%Y-%m-%d", "2026-11-03\n"),
        std::make_pair("abc %n", "abc test_logger\n"),
        std::make_pair("%n abc", "test_logger abc\n"),
        std::make_pair("%n-%l", "test_logger-info\n"),
        std::make_pair("%n%l", "test_loggerinfo\n"),
        std::make_pair("%%%%", "%%\n"), std::make_pair("abc%%def", "abc%def\n"),
        std::make_pair("%n%% %l", "test_logger% info\n"),
        std::make_pair("a%n-b%l-c%v", "atest_logger-binfo-cHello World\n"),
        std::make_pair("%+", "[2026-11-03][test_logger][info] Hello World\n")));