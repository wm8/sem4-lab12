// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_EXAMPLE_HPP_
#define INCLUDE_EXAMPLE_HPP_

#include <iostream>

class Log {
 public:
  void Write(std::string_view message) const;

  void WriteDebug(std::string_view message) const;

  explicit Log(size_t level);

 private:
  size_t level_ = 0;
  mutable std::ostream* out_;
};

#endif // INCLUDE_EXAMPLE_HPP_
