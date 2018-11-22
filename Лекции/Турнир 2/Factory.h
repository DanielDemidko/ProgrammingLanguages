#include <string>
#include <functional>
#include <map>

struct Object {
  virtual std::string ToString() const = 0;
};

class Factory {
 private:
  struct DefaultObject : public Object {
    const std::string Value;
    virtual std::string ToString() const { return Value; }
    explicit DefaultObject(const std::string &s) : Value(s) {}
  };

  std::map<std::string, std::function<Object *()>> Lib;

 public:
  Object *Create(const std::string &class_id) const {
    if (const auto res = Lib.find(class_id); res != cend(Lib)) {
      return res->second();
    }
    return nullptr;
  }

  void Register(const std::string &class_id,
                const std::function<Object *()> &creator) {
    Lib.insert({class_id, creator});
  }

  Factory() {
    for (const auto &i : {"apple!", "list", "yet another identifier"}) {
      Lib.insert({i, [i]() -> Object * { return new DefaultObject(i); }});
    }
  }
};
