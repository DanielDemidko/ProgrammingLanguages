#include <string>
#include <thread>

unsigned short Index(const char chr) { return chr - 'a'; }

char Char(const unsigned short index) { return index + 'a'; }

char EncodeChr(const char chr) { return Char((Index(chr) + 3) % 26); }

void EncodeStr(std::string::iterator i, const std::string::iterator &last) {
  for (; i < last; ++i) {
    *i = EncodeChr(*i);
  }
}

void CaesarEncrypt(std::string *s) {
  auto &str = *s;
  std::vector<std::thread> pool;
  auto it = begin(str);
  for (unsigned i = 0, count = std::thread::hardware_concurrency(),
                shift = (size(str) / count);
       i < (count - 1); ++i) {
    const auto last = it + shift;
    pool.emplace_back(EncodeStr, it, last);
    it = last;
  }
  if (it < end(str)) {
    EncodeStr(it, end(str));
  }
  for (auto &i : pool) {
    i.join();
  }
}
