// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <gtest/gtest.h>
#include <ulog/logger.h>

TEST(LoggerTest, basic) {
  ulog::Logger logger("test_logger", ulog::level_enum::info);

  logger.Trace("This is a trace message.\n");
  logger.Info("This is an info message.\n");
  logger.Error("This is an error message.\n");
}