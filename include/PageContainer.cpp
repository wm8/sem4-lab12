// Copyright 2022 wm8
#include "PageContainer.h"
#include <vector>
#include <set>
#include <string>
#include <utility>
std::vector<Item> PageContainer::GetAll() { return data_; }

void PageContainer::Load(std::istream& io, float threshold) {
  std::vector<std::string> raw_data;

  while (!io.eof()) {
    std::string line;
    std::getline(io, line, '\n');
    raw_data.push_back(std::move(line));
  }

  if (raw_data.size() < kMinLines) {
    throw std::runtime_error("too small input stream");
  }

  memory_counter_->OnRawDataLoad(raw_data_, raw_data);
  raw_data_ = std::move(raw_data);

  std::vector<Item> data;
  std::set<std::string> ids;
  histogram_->Clear();
  for (const auto& line : raw_data_) {
    std::stringstream stream(line);

    Item item;
    stream >> item.id >> item.name >> item.score;

    if (auto&& [_, inserted] = ids.insert(item.id); !inserted) {
      throw std::runtime_error("already seen");
    }

    if (item.score > threshold) {
      histogram_->AddItemScore(item.score);
      data.push_back(std::move(item));
    } else {
      stat_sender_->Skip(item);
    }
  }

  if (data.size() < kMinLines) {
    throw std::runtime_error("oops");
  }

  memory_counter_->OnDataLoad(data_, data);
  stat_sender_->OnLoaded(data);
  data_ = std::move(data);
}

const Item& PageContainer::ByIndex(size_t i) const { return data_[i]; }

const Item& PageContainer::ById(const std::string& id) const {
  auto it = std::find_if(std::begin(data_), std::end(data_),
                         [&id](const auto& i) { return id == i.id; });
  return *it;
}

void PageContainer::Reload(float threshold) {
  std::vector<Item> data;
  std::set<std::string> ids;
  histogram_->Clear();
  for (const auto& line : raw_data_) {
    std::stringstream stream(line);

    Item item;
    stream >> item.id >> item.name >> item.score;
    if (auto&& [_, inserted] = ids.insert(item.id); !inserted) {
      throw std::runtime_error("already seen");
    }

    if (item.score > threshold) {
      histogram_->AddItemScore(item.score);
      data.push_back(std::move(item));
    } else {
      stat_sender_->Skip(item);
    }
  }

  if (data.size() < kMinLines) {
    throw std::runtime_error("oops");
  }

  memory_counter_->OnDataLoad(data_, data);
  stat_sender_->OnLoaded(data);
  data_ = std::move(data);
}

PageContainer::PageContainer(StatSender* stat, UsedMemory* memory_counter) {
  this->memory_counter_ = memory_counter;
  stat_sender_ = stat;
  log_ = stat->getLog();
  histogram_ = new Histogram();
}
PageContainer::PageContainer(const Log& log, UsedMemory* memory_counter,
                             Histogram* h)
    : log_(&log), histogram_(h), memory_counter_(memory_counter),
      stat_sender_( new StatSender(*log_)) {}

PageContainer::~PageContainer() {
  delete memory_counter_;
  delete stat_sender_;
  delete histogram_;
}
