// Copyright 2022 wm8

#include "Log.h"
void Log::Write(std::string_view message) const {
  *out_ << message << std::endl;
}

void Log::WriteDebug(std::string_view message) const {
  if (level_ > 0) *out_ << message << std::endl;
}

Log::Log(size_t level) : level_(level) { out_ = &std::cout; }
