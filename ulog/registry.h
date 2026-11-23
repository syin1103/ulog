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

  void Register(std::shared_ptr<Logger> logger) {}
  std::shared_ptr<Logger> Get(const std::string& name) { return nullptr; }

  void Drop(const std::string& name) {}
  void DropAll() {}

  void set_formatter(FormatterPtr formatter) {}
  void set_pattern(const std::string& pattern) {}
  void set_level(level_enum level) {}

 private:
  RegistryT<Mutex>(){};
  RegistryT<Mutex>(const RegistryT<Mutex>&) = delete;
  RegistryT<Mutex>& operator=(const RegistryT<Mutex>&) = delete;

  void ThrowIfExists(const std::string& name) {}

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