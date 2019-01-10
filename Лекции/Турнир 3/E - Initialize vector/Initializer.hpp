#pragma once
#include <vector>

template<typename R, typename T>
auto Create(R oldVec, const T &arg) {
    std::vector<R> res;
    res.push_back(oldVec);
    return res;
}

template<typename R, typename T, typename... Types>
auto Create(R oldVec, const T &arg, const Types... args) {
    return Create(std::vector<R> {oldVec}, args...);
}

template<typename V, typename T> void Resize(V &vec, const T &arg) {
    vec.resize(arg, vec.front());
}

template<typename V, typename T, typename... Ts>
void Resize(V &vec, const T &arg, const Ts... args) {
    vec.resize(arg, vec.front());
    for (auto &i : vec) {
        Resize(i, args...);
    }
}

template<typename T, typename... Types>
auto initialize_vector(T arg, const Types... args) {
    auto res = Create(arg, args...);
    Resize(res, args...);
    return res;
}
