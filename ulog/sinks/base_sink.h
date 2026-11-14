// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_SINKS_BASE_SINK_H_
#define ULOG_SINKS_BASE_SINK_H_

#include <mutex>

namespace ulog {
namespace sinks {

template <typename Mutex>
class BaseSink : public Sink {
 public:
  BaseSink() : mutex_() {}
  virtual ~BaseSink() = default;

  virtual void Log(const LogMsg& msg) override {
    std::lock_guard<Mutex> lock(mutex_);
    SinkIt(msg);
  }

  //  protected:
 private:
  virtual void SinkIt(const LogMsg& msg) = 0;
  Mutex mutex_;
};

}  // namespace sinks
}  // namespace ulog

#endif  // ULOG_SINKS_BASE_SINK_H_