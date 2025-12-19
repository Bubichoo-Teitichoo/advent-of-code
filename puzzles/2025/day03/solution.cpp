#include <cassert>
#include <cstdint>
#include <ranges>
#include <tuple>

#include "aoc.hpp"
#include "aoc_main.hpp"

using u64 = uint64_t;

constexpr u64 char2num(char digit) {
    assert('0' <= digit and digit <= '9');
    return digit - 0x30;
}

std::tuple<u64, u64> reference(const std::vector<std::string>& input);
std::tuple<u64, u64> optimized(const std::vector<std::string>& input);

void solve(const std::vector<std::string>& input) {
    const auto reference_solution{reference(input)};
    const auto optimized_solution{optimized(input)};

    assert(reference_solution == optimized_solution && "Results of reference and optimized solutions do not match.");

    std::cout << std::format("The password for stage 1 is '{}'\n", std::get<0>(reference_solution));
    std::cout << std::format("The password for stage 2 is '{}'\n", std::get<1>(reference_solution));

    BENCH(reference(input), 100);
    BENCH(optimized(input), 1000);
}

std::tuple<u64, u64> reference(const std::vector<std::string>& input) {
    u64 joltages{0};
    for (const auto& line : input) {
        auto bank{line | std::views::transform(char2num)};

        u64 joltage{0};
        // a sliding window approach,
        // where each window starts at x+1 where x is the previous window.
        // The windows must not overlap or overrun each other.
        // For part 1 we have 2 windows, so a simple nested loop does the trick.
        // Hint: In debug mode, this is painfully slow,
        // but with compiler optimizations enabled this becomes blazingly fast.
        // Almost as fast as the "optimized" solution.
        for (auto idx0{bank.begin()}; idx0 < bank.begin() - 1; idx0++) {
            for (auto idx1{idx0 + 1}; idx1 < bank.end(); idx1++) {
                joltage = std::max(joltage, *idx0 * 10 + *idx1);
            }
        }
        joltages += joltage;
    }
    return {joltages, 0};
}

std::tuple<u64, u64> optimized(const std::vector<std::string>& input) {
    u64 joltages{0};
    for (const auto& line : input) {
        auto bank{line | std::views::transform(char2num)};

        const auto first = std::max_element(bank.begin(), bank.end() - 1);
        const auto second = std::max_element(first + 1, bank.end());

        joltages += (*first * 10 + *second);
    }

    return {joltages, 0};
}
