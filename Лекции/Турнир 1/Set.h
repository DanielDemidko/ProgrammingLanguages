#include <algorithm>
#include <iterator>
#include <set>
#include <vector>

class Set {
 private:
  std::vector<int64_t> Value;

 public:
  Set Union(const Set &other) const {
    std::vector<int64_t> res;
    std::set_union(cbegin(Value), cend(Value), cbegin(other.Value),
                   cend(other.Value), std::back_inserter(res));
    return Set(res);
  }

  Set Intersection(const Set &other) const {
    std::vector<int64_t> res;
    std::set_intersection(cbegin(Value), cend(Value), cbegin(other.Value),
                          cend(other.Value), std::back_inserter(res));
    return Set(res);
  }

  Set Difference(const Set &other) const {
    std::vector<int64_t> res;
    std::set_difference(cbegin(Value), cend(Value), cbegin(other.Value),
                        cend(other.Value), std::back_inserter(res));
    return Set(res);
  }

  Set SymmetricDifference(const Set &other) const {
    std::vector<int64_t> res;
    std::set_symmetric_difference(cbegin(Value), cend(Value),
                                  cbegin(other.Value), cend(other.Value),
                                  std::back_inserter(res));
    return Set(res);
  }

  explicit Set(const std::vector<int64_t> &v) {
    std::set<int64_t> s(cbegin(v), cend(v));
    Value = std::vector<int64_t>(cbegin(s), cend(s));
  }

  Set() = default;

  void Add(const int64_t &n) {
    const auto fix = std::find(cbegin(Value), cend(Value), n);
    if (fix == cend(Value)) {
      Value.push_back(n);
    }
  }

  void Remove(const int64_t &n) {
    const auto fix = std::find(begin(Value), end(Value), n);
    if (fix != end(Value)) {
      Value.erase(fix);
    }
  }

  bool Contains(const int64_t &n) const {
    return std::find(cbegin(Value), cend(Value), n) != cend(Value);
  }

  std::vector<int64_t> Data() { return Value; }
};