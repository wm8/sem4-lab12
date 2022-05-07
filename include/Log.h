// Copyright 2022 wm8

#ifndef LAB12_LOG_H
#define LAB12_LOG_H
#include <string>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
class Log {
 public:
  void Write(std::string_view message) const;

  void WriteDebug(std::string_view message) const;

  explicit Log(size_t level);

 private:
  size_t level_ = 0;
  mutable std::ostream* out_;
};



#endif  // LAB12_LOG_H
