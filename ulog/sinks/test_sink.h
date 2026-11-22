// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_SINKS_TEST_SINK_H_
#define ULOG_SINKS_TEST_SINK_H_

#include <fmt/format.h>

#include <mutex>
#include <vector>

#include "ulog/sinks/base_sink.h"

namespace ulog {
namespace sinks {

class TestSink : public BaseSink<std::mutex> {
 public:
  const std::vector<std::string>& Messages() const { return messages_; }

  void Flush() override { ++flush_count_; }
  int flush_count() const { return flush_count_; }

 private:
  void SinkIt(const LogMsg& msg) override {
    messages_.push_back(fmt::to_string(msg.raw));
  }

  std::vector<std::string> messages_;
  int flush_count_ = 0;
};

}  // namespace sinks
}  // namespace ulog

#endif  // ULOG_SINKS_TEST_SINK_H_