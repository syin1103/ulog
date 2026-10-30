// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <fmt/format.h>

#include <iostream>

int main() {
  std::string message = fmt::format("Hello {}, number = {}", "ulog", 42);
  std::cout << message << '\n';
  return 0;
}