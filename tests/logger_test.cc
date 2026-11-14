// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <gtest/gtest.h>
#include <ulog/logger.h>
#include <ulog/sinks/file_sink.h>
#include <ulog/sinks/stdout_sink.h>

#include <memory>
#include <mutex>

using ulog::SinkPtr;
using ulog::sinks::FileSink;
using ulog::sinks::StderrSink;
using ulog::sinks::StdoutSink;

TEST(LoggerTest, basic) {
  SinkPtr out_sink = StdoutSink<std::mutex>::Instance();
  SinkPtr err_sink = StderrSink<std::mutex>::Instance();
  SinkPtr file_sink = std::make_shared<FileSink<std::mutex>>("logger_test.log");

  ulog::Logger logger("TestLogger", {out_sink, err_sink, file_sink});

  logger.Trace("This is a trace message.");
  logger.Info("This is an info message.");
  logger.Error("This is an error message.");
}