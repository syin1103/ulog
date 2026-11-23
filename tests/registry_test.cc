// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "ulog/registry.h"

#include <gtest/gtest.h>

TEST(RegistryTest, InstanceSingleton) {
  auto& registry1 = ulog::Registry::Instance();
  auto& registry2 = ulog::Registry::Instance();
  EXPECT_EQ(&registry1, &registry2);
}