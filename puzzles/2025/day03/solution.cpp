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
        auto bank_view{line | std::views::transform(char2num)};
        const std::vector<u64> bank{std::begin(bank_view), std::end(bank_view)};

        std::vector<u64> permutations{};
        for (size_t idx0{0}; idx0 < bank.size() - 1; idx0++) {
            for (size_t idx1{idx0 + 1}; idx1 < bank.size(); idx1++) {
                permutations.push_back(bank[idx0] * 10 + bank[idx1]);
            }
        }
        joltages += *std::max_element(permutations.begin(), permutations.end());
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
