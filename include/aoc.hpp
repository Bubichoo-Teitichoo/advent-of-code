#if !defined(__AOC_HPP__)
#define __AOC_HPP__

#include <cassert>
#include <charconv>
#include <string_view>

inline auto str2int(std::string_view string) -> int {
    int number{0};
    const auto [ptr, ec] = std::from_chars(std::begin(string), std::end(string), number);
    assert(ec == std::errc());
    return number;
}

#endif
