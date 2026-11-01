// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_SINKS_STDOUT_SINK_H_
#define ULOG_SINKS_STDOUT_SINK_H_

#include <cstdio>
#include <memory>

#include "ulog/sinks/sink.h"

namespace ulog {
namespace sinks {

class StdoutSink : public Sink {
  using SelfPtr = std::shared_ptr<StdoutSink>;

 public:
  StdoutSink() = default;
  virtual ~StdoutSink() = default;

  static std::shared_ptr<StdoutSink> Instance() {
    static SelfPtr instance = std::make_shared<StdoutSink>();
    return instance;
  }

 private:
  virtual void SinkIt(const LogMsg& msg) override {
    std::fwrite(msg.formatted.data(), sizeof(char), msg.formatted.size(),
                stdout);
    std::fflush(stdout);
  }
};

class StderrSink : public Sink {
  using SelfPtr = std::shared_ptr<StderrSink>;

 public:
  StderrSink() = default;
  virtual ~StderrSink() = default;

  static std::shared_ptr<StderrSink> Instance() {
    static SelfPtr instance = std::make_shared<StderrSink>();
    return instance;
  }

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