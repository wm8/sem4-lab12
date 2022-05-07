// Copyright 2022 wm8

#ifndef LAB12_USEDMEMORY_H
#define LAB12_USEDMEMORY_H
#include <vector>
#include "Log.h"
#include "Item.h"
class UsedMemory {
 public:
  explicit UsedMemory(const Log& log);

  void OnDataLoad(const std::vector<Item>& old_items,
                  const std::vector<Item>& new_items);

  void OnRawDataLoad(const std::vector<std::string>& old_items,
                     const std::vector<std::string>& new_items);

  size_t used() const;

 private:
  const Log* log_;
  size_t used_ = 0;
};


#endif  // LAB12_USEDMEMORY_H
