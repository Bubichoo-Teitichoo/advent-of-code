#if !defined(__AOC_HPP__)
#define __AOC_HPP__

#include <cassert>
#include <charconv>
#include <cmath>
#include <ranges>
#include <string_view>
#include <vector>

constexpr auto view2string = [](auto&& view) {
    return std::string{std::begin(view), std::end(view)};
};

constexpr auto split_view(const std::string& string, char delim = '\n') {
    return string | std::views::split(delim) | std::views::transform(view2string);
}

constexpr auto split_transformer(char delim) {
    return std::views::transform([delim](const std::string& string) {
        return split_view(string, delim);
    });
}

template <typename T>
auto str2int(std::string_view string) -> T {
    T number{0};
    const auto [ptr, ec] = std::from_chars(std::begin(string), std::end(string), number);
    assert(ec == std::errc());
    return number;
}

inline std::vector<std::string> split(const std::string& string, char delim = '\n') {
    auto view{split_view(string, delim)};
    return std::vector<std::string>{std::begin(view), std::end(view)};
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
