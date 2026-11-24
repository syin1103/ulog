// Copyright(c) 2026 syin1103.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "ulog/registry.h"

#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "ulog/common.h"
#include "ulog/pattern_formatter.h"

using namespace ulog;

// TEST(RegistryTest, InstanceSingleton) {
//   auto& registry1 = ulog::Registry::Instance();
//   auto& registry2 = ulog::Registry::Instance();
//   EXPECT_EQ(&registry1, &registry2);
// }

class RegistryTest : public ::testing::Test {
 protected:
  Registry& registry = Registry::Instance();

  void SetUp() override { registry.DropAll(); }

  void TearDown() override { registry.DropAll(); }

  std::shared_ptr<Logger> CreateLogger(const std::string& name) {
    return std::make_shared<Logger>(name);
  }
};

TEST_F(RegistryTest, RegisterAndGet) {
  auto logger = CreateLogger("test_logger");
  registry.Register(logger);
  auto result = registry.Get("test_logger");

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, logger);
  EXPECT_EQ(result->name(), "test_logger");
}

TEST_F(RegistryTest, GetNonexistentLogger) {
  EXPECT_EQ(registry.Get("not_exist"), nullptr);
}

TEST_F(RegistryTest, RegisterDuplicateLogger) {
  auto logger1 = CreateLogger("test_logger");
  auto logger2 = CreateLogger("test_logger");
  registry.Register(logger1);

  EXPECT_THROW(registry.Register(logger2), std::runtime_error);
  EXPECT_EQ(registry.Get("test_logger"), logger1);
}

TEST_F(RegistryTest, DropLogger) {
  auto logger = CreateLogger("test_logger");
  registry.Register(logger);
  registry.Drop("test_logger");

  EXPECT_EQ(registry.Get("test_logger"), nullptr);
}

TEST_F(RegistryTest, DropAllLoggers) {
  auto logger1 = CreateLogger("logger1");
  auto logger2 = CreateLogger("logger2");
  registry.Register(logger1);
  registry.Register(logger2);
  registry.DropAll();

  EXPECT_EQ(registry.Get("logger1"), nullptr);
  EXPECT_EQ(registry.Get("logger2"), nullptr);
}

TEST_F(RegistryTest, SetLevel) {
  auto logger1 = CreateLogger("logger1");
  auto logger2 = CreateLogger("logger2");
  registry.Register(logger1);
  registry.Register(logger2);
  registry.set_level(level_enum::debug);

  EXPECT_EQ(logger1->level(), level_enum::debug);
  EXPECT_EQ(logger2->level(), level_enum::debug);
}

TEST_F(RegistryTest, SetFormatter) {
  auto logger1 = CreateLogger("logger1");
  auto logger2 = CreateLogger("logger2");
  registry.Register(logger1);
  registry.Register(logger2);

  FormatterPtr formatter = std::make_shared<PatternFormatter>("[%l] %v");
  registry.set_formatter(formatter);

  EXPECT_EQ(logger1->formatter(), formatter);
  EXPECT_EQ(logger2->formatter(), formatter);
}