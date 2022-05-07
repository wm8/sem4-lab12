// Copyright 2022 wm8

#include "Histogram.h"
void Histogram::AddItemScore(float score) {
  count++;
  sum += score;
  mean = score / (float)count;
}
void Histogram::Clear() {
  /*sum = 0;
  count = 0;
  mean = 0;*/
  skipped = 0;
}
void Histogram::AddSkipped() { skipped++; }
