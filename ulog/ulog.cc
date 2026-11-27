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

void Drop(const std::string& name) { Registry::Instance().Drop(name); }

void DropAll() { Registry::Instance().DropAll(); }

}  // namespace ulog