// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <gtest/gtest.h>
#include <ulog/logger.h>
#include <ulog/sinks/stdout_sink.h>

TEST(LoggerTest, basic) {
  ulog::SinkPtr out_sink = ulog::sinks::StdoutSink::Instance();
  ulog::SinkPtr err_sink = ulog::sinks::StderrSink::Instance();

  ulog::Logger logger("TestLogger", {out_sink, err_sink});

  logger.Trace("This is a trace message.\n");
  logger.Info("This is an info message.\n");
  logger.Error("This is an error message.\n");
}