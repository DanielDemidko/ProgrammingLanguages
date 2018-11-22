#include <utility>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>

bool Op(const GameObject &a, const GameObject &b) { return a.id > b.id; }

class GameDatabase {
 private:
  map<ObjectId, GameObject> ById;
  map<string, vector<GameObject>> ByName;

 public:
  void Insert(const ObjectId &id, const string &name, const size_t &x,
              const size_t &y) {
    const GameObject obj = {id, name, x, y};
    ById.insert_or_assign(id, obj);
    ByName[name].push_back(obj);
  }

  void Remove(const ObjectId &id) { ById.erase(id); }

  pair<GameObject, bool> DataById(const ObjectId &id) const {
    const auto it = ById.find(id);
    return {it->second, it != ById.end()};
  }

  vector<GameObject> DataByName(const string &name) const {
    const auto tmp = ByName.find(name)->second;
    vector<GameObject> res;
    for (size_t i = 0; i < size(tmp); i++) {
      if (ById.find(tmp[i].id) != ById.end() &&
          ById.find(tmp[i].id)->second.name == name) {
        res.push_back(tmp[i]);
      }
    }
    sort(res.begin(), res.end(), Op);
    return res;
  }

  vector<GameObject> DataByPosition(const size_t &x, const size_t &y) const {
    vector<GameObject> res;
    for (auto i = ById.begin(); i != ById.end(); ++i) {
      if (i->second.x == x && i->second.y == y) {
        res.push_back(i->second);
      }
    }
    sort(res.begin(), res.end(), Op);
    return res;
  }

  vector<GameObject> Data() const {
    vector<GameObject> res;
    transform(cbegin(ById), cend(ById), back_inserter(res),
              mem_fn(&map<ObjectId, GameObject>::value_type::second));
    sort(res.begin(), res.end(), Op);
    return (res);
  }
};
