// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "ulog/ulog.h"

#include "ulog/registry.h"

namespace ulog {

std::shared_ptr<Logger> GetLogger(const std::string& name) {
  return Registry::Instance().Get(name);
}

void SetPattern(const std::string& pattern) {
  Registry::Instance().set_pattern(pattern);
}

void SetFormatter(FormatterPtr formatter) {
  Registry::Instance().set_formatter(formatter);
}

void SetLevel(level_enum level) { Registry::Instance().set_level(level); }

void RegisterLogger(std::shared_ptr<Logger> logger) {
  Registry::Instance().Register(logger);
}

std::shared_ptr<Logger> Create(const std::string& name, SinkPtr sink) {
  return nullptr;
}

std::shared_ptr<Logger> Create(const std::string& name, SinksInitList sinks) {
  return nullptr;
}

template <typename It>
std::shared_ptr<Logger> Create(const std::string& name, const It& begin,
                               const It& end) {
  return nullptr;
}

template <typename Sink, typename... Args>
std::shared_ptr<Logger> Create(const std::string& name, Args&&... args) {
  return nullptr;
}

std::shared_ptr<Logger> BasicLoggerMt(const std::string& logger_name,
                                      const std::string& filename) {
  return nullptr;
}

std::shared_ptr<Logger> BasicLoggerSt(const std::string& logger_name,
                                      const std::string& filename) {
  return nullptr;
}

std::shared_ptr<Logger> StdoutLoggerMt(const std::string& logger_name) {
  return nullptr;
}

std::shared_ptr<Logger> StdoutLoggerSt(const std::string& logger_name) {
  return nullptr;
}

std::shared_ptr<Logger> StderrLoggerMt(const std::string& logger_name) {
  return nullptr;
}
std::shared_ptr<Logger> StderrLoggerSt(const std::string& logger_name) {
  return nullptr;
}

void Drop(const std::string& name) { Registry::Instance().Drop(name); }

void DropAll() { Registry::Instance().DropAll(); }

}  // namespace ulog