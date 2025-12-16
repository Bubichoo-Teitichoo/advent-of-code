#if !defined(__AOC_HPP__)
#define __AOC_HPP__

#include <cassert>
#include <charconv>
#include <cmath>
#include <string_view>

template <typename T>
auto str2int(std::string_view string) -> T {
    T number{0};
    const auto [ptr, ec] = std::from_chars(std::begin(string), std::end(string), number);
    assert(ec == std::errc());
    return number;
}

template <typename T>
T repeat(T number, T count) {
    const T digits{static_cast<T>(1 + std::log10(number))};
    const T multiplier{static_cast<T>(std::pow(10, digits))};
    T result{0};
    for (T i{0}; i < count; i++) {
        result = (result * multiplier) + number;
    }
    return result;
}

#endif
