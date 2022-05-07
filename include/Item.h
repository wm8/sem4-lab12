// Copyright 2022 wm8

#ifndef LAB12_ITEM_H
#define LAB12_ITEM_H
#include <string>

struct Data
{
  std::string inp_path;
  float threshold;
};
struct Item {
  std::string id;
  std::string name;
  float score = 0;
};
#endif  // LAB12_ITEM_H
