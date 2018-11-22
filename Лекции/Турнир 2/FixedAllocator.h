#pragma once
#include <vector>

class FixedAllocator {
 private:
  const size_t Sizeof;
  const size_t PageSize;
  std::vector<char *> HeapBuffer;

  void AddPage() {
    for (size_t i = 0; i < PageSize; ++i) {
      HeapBuffer.emplace_back(new char[Sizeof]);
    }
  }

 public:
  FixedAllocator(const size_t &chunkSize, const size_t &pageSize)
      : Sizeof(chunkSize), PageSize(pageSize) {}

  void *Allocate() {
    if (empty(HeapBuffer)) {
      AddPage();
    }
    const auto res = HeapBuffer.back();
    HeapBuffer.pop_back();
    return res;
  }

  void Deallocate(void *const ptr) {
    HeapBuffer.emplace_back(static_cast<char *>(ptr));
  }

  ~FixedAllocator() {
    for (const auto &p : HeapBuffer) {
      delete[] p;
    }
  }
};
