// Copyright 2022 wm8
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "Utils.hpp"
class MockStatSender: public StatSender
{
 public:
  MOCK_METHOD(void, AsyncSend, (const std::vector<Item>& items, std::string_view path), (override));
  MOCK_METHOD(void, Skip, (const Item& item), (override));
  explicit MockStatSender(const Log& log): StatSender(log) {}
};