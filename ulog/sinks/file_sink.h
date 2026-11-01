// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_SINKS_FILE_SINK_H_
#define ULOG_SINKS_FILE_SINK_H_

#include <cassert>
#include <cstdio>
#include <string>

#include "ulog/sinks/sink.h"

namespace ulog {
namespace sinks {

class FileSink : public Sink {
 public:
  explicit FileSink(const std::string& filename);
  virtual ~FileSink() {
    if (file_) {
      fclose(file_);
    }
  }

  FileSink(const FileSink&) = delete;
  FileSink& operator=(const FileSink&) = delete;

  void SinkIt(const LogMsg& msg) override;

 private:
  std::string filename_;
  FILE* file_ = nullptr;
};

inline FileSink::FileSink(const std::string& filename) : filename_(filename) {
  file_ = fopen(filename.c_str(), "a");
  if (!file_) {
    throw std::runtime_error("Failed to open log file");
  }
}

inline void FileSink::SinkIt(const LogMsg& msg) {
  assert(file_);
  std::fwrite(msg.formatted.data(), sizeof(char), msg.formatted.size(), file_);
}

}  // namespace sinks
}  // namespace ulog

#endif  // ULOG_SINKS_FILE_SINK_H_