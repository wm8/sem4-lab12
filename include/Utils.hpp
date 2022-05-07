// Copyright 2022 wm8
#ifndef INCLUDE_UTILS_HPP_
#define INCLUDE_UTILS_HPP_
#include <boost/program_options.hpp>
#include "Item.h"
#include "PageContainer.h"
namespace po = boost::program_options;
bool ParseArgs(Data* data, int argc, char **argv);
#endif // INCLUDE_UTILS_HPP_
