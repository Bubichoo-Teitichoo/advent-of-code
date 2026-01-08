#if !defined(__AOC_HPP__)
#define __AOC_HPP__

#include <cassert>
#include <charconv>
#include <chrono>
#include <cmath>
#include <format>
#include <iostream>
#include <ranges>
#include <string_view>
#include <vector>

#define BENCH(fn_call, cycles)                                                              \
    do {                                                                                    \
        const auto start{std::chrono::high_resolution_clock::now()};                        \
        for (const auto _ : std::views::iota(0, cycles)) {                                  \
            fn_call;                                                                        \
        }                                                                                   \
        const auto end{std::chrono::high_resolution_clock::now()};                          \
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); \
        std::cout << std::format("'{}' executed {} time in {} ({} per cycle)\n",            \
                                 #fn_call,                                                  \
                                 cycles,                                                    \
                                 duration,                                                  \
                                 duration / cycles);                                        \
    } while (0)

#define BENCH2(fn_call, timeout)                                                               \
    do {                                                                                       \
        using clock = std::chrono::high_resolution_clock;                                      \
        const auto start{clock::now()};                                                        \
        std::chrono::duration<double> duration;                                                \
        size_t cycles{0};                                                                      \
        for (;; cycles++) {                                                                    \
            fn_call;                                                                           \
            duration = std::chrono::duration_cast<std::chrono::seconds>(clock::now() - start); \
            if (duration >= std::chrono::seconds(timeout)) {                                   \
                break;                                                                         \
            }                                                                                  \
        }                                                                                      \
        std::cout << std::format("'{}' executed {} times in {} ({}/cycle)\n",                  \
                                 #fn_call,                                                     \
                                 cycles,                                                       \
                                 duration,                                                     \
                                 duration / cycles);                                           \
    } while (0)
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
