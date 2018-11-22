#pragma once
#include <cstdint>

bool IsSimple(const uint64_t n) {
  for (auto i = 2ull; i < n - 1; ++i) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

class PrimeNumberGenerator {
 private:
  uint64_t Start;

 public:
  explicit PrimeNumberGenerator(const uint64_t start)
      : Start(start == 1 ? 2 : start) {}

  uint64_t GetNextPrime() {
    for (auto i = Start;; ++i) {
      if (IsSimple(i)) {
        Start = i + 1;
        return i;
      }
    }
  }
};