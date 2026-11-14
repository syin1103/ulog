// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_SINKS_STDOUT_SINK_H_
#define ULOG_SINKS_STDOUT_SINK_H_

#include <cstdio>
#include <memory>

#include "ulog/sinks/base_sink.h"

namespace ulog {
namespace sinks {

template <typename Mutex>
class StdoutSink : public BaseSink<Mutex> {
  using SelfPtr = std::shared_ptr<StdoutSink<Mutex>>;

 public:
  StdoutSink() = default;
  virtual ~StdoutSink() = default;

  static std::shared_ptr<StdoutSink> Instance() {
    static SelfPtr instance = std::make_shared<StdoutSink<Mutex>>();
    return instance;
  }

  void Flush() override { std::fflush(stdout); }

 private:
  virtual void SinkIt(const LogMsg& msg) override {
    std::fwrite(msg.formatted.data(), sizeof(char), msg.formatted.size(),
                stdout);
    std::fflush(stdout);
  }
};

template <typename Mutex>
class StderrSink : public BaseSink<Mutex> {
  using SelfPtr = std::shared_ptr<StderrSink<Mutex>>;

 public:
  StderrSink() = default;
  virtual ~StderrSink() = default;

  static std::shared_ptr<StderrSink> Instance() {
    static SelfPtr instance = std::make_shared<StderrSink<Mutex>>();
    return instance;
  }

  void Flush() override { std::fflush(stderr); }

 private:
  virtual void SinkIt(const LogMsg& msg) override {
    std::fwrite(msg.formatted.data(), sizeof(char), msg.formatted.size(),
                stderr);
    std::fflush(stderr);
  }
};

}  // namespace sinks
}  // namespace ulog

#endif  // ULOG_SINKS_STDOUT_SINK_H_