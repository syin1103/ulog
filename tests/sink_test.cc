// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <gtest/gtest.h>

#include <mutex>
#include <thread>

#include "ulog/sinks/file_sink.h"
#include "ulog/sinks/test_sink.h"

using ulog::LogMsg;
using ulog::sinks::FileSink;
using ulog::sinks::TestSink;

TEST(SinkTest, SingleThreadLog) {
  TestSink sink;

  std::string logger_name = "test";
  LogMsg msg(&logger_name, ulog::level_enum::info);

  fmt::format_to(std::back_inserter(msg.raw), "Hello World");

  sink.Log(msg);

  ASSERT_EQ(sink.Messages().size(), 1);
  EXPECT_EQ(sink.Messages()[0], "Hello World");
}

TEST(SinkTest, MultiThreadLog) {
  TestSink sink;

  constexpr int thread_count = 8;
  constexpr int messages_per_thread = 1000;

  std::vector<std::thread> threads;

  for (int i = 0; i < thread_count; ++i) {
    threads.emplace_back([&sink, i]() {
      std::string logger_name = "test";

      for (int j = 0; j < messages_per_thread; ++j) {
        LogMsg msg(&logger_name, ulog::level_enum::info);
        fmt::format_to(std::back_inserter(msg.raw), "thread={} msg={}", i, j);
        sink.Log(msg);
      }
    });
  }

  for (auto& thread : threads) {
    thread.join();
  }

  EXPECT_EQ(sink.Messages().size(), thread_count * messages_per_thread);
}

TEST(SinkTest, MultiThreadFlush) {
  TestSink sink;

  constexpr int thread_count = 8;
  constexpr int flush_count = 100;

  std::vector<std::thread> threads;

  for (int i = 0; i < thread_count; ++i) {
    threads.emplace_back([&sink]() {
      for (int j = 0; j < flush_count; ++j) {
        sink.Flush();
      }
    });
  }

  for (auto& thread : threads) {
    thread.join();
  }

  EXPECT_EQ(sink.flush_count(), thread_count * flush_count);
}

TEST(FileSinkTest, MultiThreadLog) {
  const std::string filename = "test.log";
  FileSink<std::mutex> sink(filename);

  constexpr int thread_count = 8;
  constexpr int messages_per_thread = 1000;

  std::vector<std::thread> threads;

  for (int i = 0; i < thread_count; ++i) {
    threads.emplace_back([&sink, i]() {
      std::string logger_name = "test";
      for (int j = 0; j < messages_per_thread; ++j) {
        LogMsg msg(&logger_name, ulog::level_enum::info);
        fmt::format_to(std::back_inserter(msg.formatted), "id={},msg={}\n", i,
                       j);
        sink.Log(msg);
      }
    });
  }

  for (auto& thread : threads) {
    thread.join();
  }
  sink.Flush();

  // Read the file and verify the actual number of log entries written.
}