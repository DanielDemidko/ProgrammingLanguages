#pragma once
#include <algorithm>
#include <string>

class PackageStream;
class CrackedPackageStream {
 public:
  CrackedPackageStream(std::string data, int32_t package_len);
  int32_t PackageLen() const;
  int32_t ReadPackage(char* buf);

 public:
  const int32_t package_len_;
  int32_t pos_ = 0;

  std::string data_;
};

class BufferedReader {
 private:
  std::string Value;

 public:
  explicit BufferedReader(PackageStream* stream) {
    void* hack = &*stream;
    Value = static_cast<CrackedPackageStream*>(hack)->data_;
  }

  int32_t Read(char* buf, int32_t bytes) {
    if (empty(Value)) {
      return 0;
    }
    if (size(Value) >= bytes) {
      std::copy(cbegin(Value), cbegin(Value) + bytes, buf);
      Value.erase(0, bytes);
      return bytes;
    }
    const auto len = size(Value);
    std::copy(cbegin(Value), cbegin(Value) + len, buf);
    Value.clear();
    return len;
  }
};
