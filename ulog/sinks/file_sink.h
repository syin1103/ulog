// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_SINKS_FILE_SINK_H_
#define ULOG_SINKS_FILE_SINK_H_

#include <cassert>
#include <cstdio>
#include <string>

#include "ulog/sinks/base_sink.h"

namespace ulog {
namespace sinks {

template <typename Mutex>
class FileSink : public BaseSink<Mutex> {
 public:
  explicit FileSink(const std::string& filename);
  virtual ~FileSink() {
    if (file_) {
      fclose(file_);
    }
  }

  FileSink(const FileSink&) = delete;
  FileSink& operator=(const FileSink&) = delete;

  void Flush() override;

 private:
  void SinkIt(const LogMsg& msg) override;
  std::string filename_;
  FILE* file_ = nullptr;
};

template <typename Mutex>
inline FileSink<Mutex>::FileSink(const std::string& filename)
    : filename_(filename) {
  file_ = fopen(filename.c_str(), "a");
  if (!file_) {
    throw std::runtime_error("Failed to open log file");
  }
}

template <typename Mutex>
inline void FileSink<Mutex>::SinkIt(const LogMsg& msg) {
  assert(file_);
  std::fwrite(msg.formatted.data(), sizeof(char), msg.formatted.size(), file_);
}

template <typename Mutex>
inline void FileSink<Mutex>::Flush() {
  if (file_) {
    std::fflush(file_);
  }
}

}  // namespace sinks
}  // namespace ulog

#endif  // ULOG_SINKS_FILE_SINK_H_