#pragma once

template<typename T, typename It> It Find(const T& value, const It &first,
    const It &last, const std::random_access_iterator_tag) {
    const auto r = std::lower_bound(first, last, value);
    return *r == value ? r : last;
}

template<typename T, typename It> It Find(const T& value, const It &first,
    const It &last, const std::bidirectional_iterator_tag) {
    return std::find(first, last, value);
}

template<typename T, typename It> It Find(
    const T& value, const It &first, const It &last) {
    return Find(value, first, last,
        typename std::iterator_traits<It>::iterator_category());
}
