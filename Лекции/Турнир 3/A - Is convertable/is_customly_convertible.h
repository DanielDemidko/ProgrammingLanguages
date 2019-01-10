#pragma once

struct NoTriviallyConstructible {
    NoTriviallyConstructible() = delete;
};

struct NoCopyConstructible {
    NoCopyConstructible(const NoCopyConstructible&) = delete;
    NoCopyConstructible(NoCopyConstructible&&) = delete;
};

template<typename A, typename B> struct Convert {
    static constexpr bool NotSpecializated = true;
};

template <> struct Convert<NoCopyConstructible, NoTriviallyConstructible> {
    NoTriviallyConstructible operator()(const NoCopyConstructible&) {}
};

template<typename A, typename B> class is_customly_convertible {
 private:
    static void Detect(...);
    template<typename T> static decltype(T::NotSpecializated) Detect(const T&);

 public:
    constexpr static bool value =
        std::is_same<void, decltype(Detect(std::declval<Convert<A, B>>()))>();
};
