// Copyright 2022 wm8
#ifndef LAB12_HISTOGRAM_H
#define LAB12_HISTOGRAM_H

class Histogram {
 public:
  void AddItemScore(float score);
  void AddSkipped();
 void Clear();

 private:
  int count = 0;
  float sum = 0;
  int skipped = 0;
  float mean = 0;
};

#endif  // LAB12_HISTOGRAM_H
