// Copyright 2022 wm8

#ifndef LAB12_STATSENDER_H
#define LAB12_STATSENDER_H
#include <vector>
#include <fstream>
#include "Item.h"
#include "Log.h"
class StatSender {
 public:
  explicit StatSender(const Log& log);
  void OnLoaded(const std::vector<Item>& new_items);

  virtual void Skip(const Item& item);
  const Log* getLog();
 protected:
  virtual ~StatSender() = default;
  virtual void AsyncSend(const std::vector<Item>& items, std::string_view path);

  const Log* log_;
  std::ofstream fstr;
};

#endif  // LAB12_STATSENDER_H
