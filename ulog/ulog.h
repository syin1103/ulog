// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_H_
#define ULOG_H_

#include <memory>
#include <string>

#include "ulog/common.h"
#include "ulog/logger.h"

namespace ulog {

std::shared_ptr<Logger> GetLogger(const std::string& name);

void SetPattern(const std::string& pattern);
void SetFormatter(FormatterPtr formatter);
void SetLevel(level_enum level);

std::shared_ptr<Logger> BasicLoggerMt(const std::string& logger_name,
                                      const std::string& filename);
std::shared_ptr<Logger> BasicLoggerSt(const std::string& logger_name,
                                      const std::string& filename);

std::shared_ptr<Logger> StdoutLoggerMt(const std::string& logger_name);
std::shared_ptr<Logger> StdoutLoggerSt(const std::string& logger_name);

std::shared_ptr<Logger> StderrLoggerMt(const std::string& logger_name);
std::shared_ptr<Logger> StderrLoggerSt(const std::string& logger_name);

void RegisterLogger(std::shared_ptr<Logger> logger);
void Drop(const std::string& name);
void DropAll();

}  // namespace ulog

#endif  // ULOG_H_