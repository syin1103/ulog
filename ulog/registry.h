// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_REGISTRY_H_
#define ULOG_REGISTRY_H_

#include <memory>
#include <string>
#include <unordered_map>

#include "ulog/common.h"
#include "ulog/logger.h"

namespace ulog {

template <typename Mutex>
class RegistryT {
 public:
  ~RegistryT<Mutex>(){};

  static RegistryT<Mutex>& Instance() {
    static RegistryT<Mutex> instance;
    return instance;
  }

  void Register(std::shared_ptr<Logger> logger) {
    std::lock_guard<Mutex> lock_(mutex_);
    ThrowIfExists(logger->name());
    loggers_[logger->name()] = logger;
  }

  std::shared_ptr<Logger> Get(const std::string& name) {
    std::lock_guard<Mutex> lock_(mutex_);
    auto it = loggers_.find(name);
    return it != loggers_.end() ? it->second : nullptr;
  }

  void Drop(const std::string& name) {
    std::lock_guard<Mutex> lock_(mutex_);
    loggers_.erase(name);
  }
  void DropAll() {
    std::lock_guard<Mutex> lock_(mutex_);
    loggers_.clear();
  }

  void set_formatter(FormatterPtr formatter) {
    std::lock_guard<Mutex> lock_(mutex_);
    formatter_ = formatter;
    for (auto& item : loggers_) {
      item.second->set_formatter(formatter_);
    }
  }

  void set_pattern(const std::string& pattern) {
    std::lock_guard<Mutex> lock_(mutex_);
    formatter_ = std::make_shared<PatternFormatter>(pattern);
    for (auto& item : loggers_) {
      item.second->set_formatter(formatter_);
    }
  }

  void set_level(level_enum level) {
    std::lock_guard<Mutex> lock_(mutex_);
    level_ = level;
    for (auto& item : loggers_) {
      item.second->set_level(level_);
    }
  }

 private:
  RegistryT<Mutex>(){};
  RegistryT<Mutex>(const RegistryT<Mutex>&) = delete;
  RegistryT<Mutex>& operator=(const RegistryT<Mutex>&) = delete;

  void ThrowIfExists(const std::string& name) {
    auto it = loggers_.find(name);
    if (it != loggers_.end()) {
      throw std::runtime_error("Logger already exists");
    }
  }

  Mutex mutex_;
  level_enum level_;
  FormatterPtr formatter_;
  std::unordered_map<std::string, std::shared_ptr<Logger>> loggers_;
};

#ifdef ULOG_NO_REGISTRY_MUTEX
using Registry = RegistryT<details::null_mutex>;
#else
using Registry = RegistryT<std::mutex>;
#endif

}  // namespace ulog

#endif  // ULOG_REGISTRY_H_