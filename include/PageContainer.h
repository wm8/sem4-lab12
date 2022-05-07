// Copyright 2022 wm8
#ifndef LAB12_PAGECONTAINER_H
#define LAB12_PAGECONTAINER_H
#include "StatSender.h"
#include "Histogram.h"
#include "UsedMemory.h"

constexpr size_t kMinLines = 10;

class PageContainer
{
 public:
  void Load(std::istream& io, float threshold);
  const Item& ByIndex(size_t i) const;

  const Item& ById(const std::string& id) const;

  std::vector<Item> GetAll();

  void Reload(float threshold);

  PageContainer(StatSender* stat, UsedMemory* memory_counter);
  PageContainer(const Log& log, UsedMemory* memory_counter, Histogram* h = new Histogram());
  ~PageContainer();
 private:
  const Log* log_;
  Histogram* histogram_;
  UsedMemory* memory_counter_;
  StatSender* stat_sender_;
  std::vector<Item> data_;
  std::vector<std::string> raw_data_;
};
#endif  // LAB12_PAGECONTAINER_H
