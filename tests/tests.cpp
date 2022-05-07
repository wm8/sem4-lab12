// Copyright 2022 wm8

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "MockStatSender.cpp"
#include <Utils.hpp>
#include <stdexcept>
#include <thread>

TEST(PageContainerTests, dataTest) {
  std::stringstream data1;
  for (int i = 0; i != 20; i++) data1 << i << " test 2\n";
  Log the_log(0);
  auto* used_memory = new UsedMemory{the_log};
  PageContainer page(the_log, used_memory);
  page.Load(data1, 0.1);
  auto raw_data_copy = page.GetAll();
  data1.clear();
  for (int i = 0; i != 8; i++) data1 << i << " test 2\n";
  ASSERT_ANY_THROW(page.Load(data1, 0.1));
  EXPECT_EQ(raw_data_copy.size(), page.GetAll().size());
}
TEST(PageContainerTests, asyncTest1) {
  using ::testing::_;
  using ::testing::AtLeast;
  Log the_log(0);
  auto* used_memory = new UsedMemory{the_log};
  auto* sender = new MockStatSender(the_log);
  PageContainer page(sender, used_memory);
  // An<const std::vector<Item>&>(), An<std::string_view>()
  EXPECT_CALL(*sender, AsyncSend(_, _)).Times(AtLeast(1));
  std::stringstream data1;
  for (int i = 0; i != 20; i++) data1 << i << " test 2\n";
  page.Load(data1, 0.1);
}
TEST(PageContainerTests, asyncTest2) {
  using ::testing::_;
  using ::testing::AtLeast;
  using ::testing::An;
  Log the_log(0);
  auto* used_memory = new UsedMemory{the_log};
  auto* sender = new MockStatSender(the_log);
  PageContainer page(sender, used_memory);
  EXPECT_CALL(*sender, Skip(_)).Times(AtLeast(1));
  std::stringstream data1;
  data1 << 222 << " test 0\n";
  for (int i = 0; i != 10; i++) data1 << i << " test 1\n";
  page.Load(data1, 0.1);
}
TEST(PageContainerTests, istreamTest) {
  std::stringstream data1;
  data1 << 44 << " sdasdsd sckasksd\n";
  for (int i = 0; i != 20; i++) data1 << i << " sodksdl 2\n";
  Log the_log(0);
  auto* used_memory = new UsedMemory{the_log};
  PageContainer page(the_log, used_memory);
  EXPECT_NO_THROW(page.Load(data1, 0.1));
}
TEST(UsedMemoryTests, usedMemoryTest) {
  std::stringstream data1;
  for (int i = 0; i != 20; i++) data1 << i << " test 2\n";
  Log the_log(0);
  auto* used_memory = new UsedMemory{the_log};
  PageContainer page(the_log, used_memory);
  page.Load(data1, 0.1);
  EXPECT_EQ(used_memory->used(), 995);
}
