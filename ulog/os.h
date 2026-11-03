// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ULOG_OS_H_
#define ULOG_OS_H_

#include <cstddef>
#include <functional>
#include <thread>

#if defined(_WIN32)
#include <windows.h>

#elif defined(__APPLE__)
#include <pthread.h>

#include <cstdint>

#elif defined(__linux__)
#include <sys/syscall.h>
#include <unistd.h>

#else
#error "Unsupported platform"
#endif

namespace ulog {
namespace os {

uint64_t GetThreadId() {
#if defined(_WIN32)
  return static_cast<uint64_t>(::GetCurrentThreadId());
#elif defined(__APPLE__)
  uint64_t tid = 0;
  if (pthread_threadid_np(nullptr, &tid) != 0) {
    return 0;
  }
  return tid;
#elif defined(__linux__)
  long tid = ::syscall(SYS_gettid);
  return tid == -1 ? 0 : static_cast<uint64_t>(tid);
#else
  return static_cast<uint64_t>(
      std::hash<std::thread::id>()(std::this_thread::get_id()));
#endif
}

}  // namespace os
}  // namespace ulog

#endif  // ULOG_OS_H_