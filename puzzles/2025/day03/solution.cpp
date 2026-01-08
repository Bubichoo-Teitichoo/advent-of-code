#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iterator>
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

    std::cout << "Reference Solution:\n";
    std::cout << std::format("  The password for stage 1 is '{}'\n", std::get<0>(reference_solution));
    std::cout << std::format("  The password for stage 2 is '{}'\n", std::get<1>(reference_solution));

    std::cout << "Optimized Solution:\n";
    std::cout << std::format("  The password for stage 1 is '{}'\n", std::get<0>(optimized_solution));
    std::cout << std::format("  The password for stage 2 is '{}'\n", std::get<1>(optimized_solution));

    assert(reference_solution == optimized_solution && "Results of reference and optimized solutions do not match.");

    BENCH(reference(input), 1000);
    BENCH(optimized(input), 1000);
}

template <size_t W>
u64 reference_calculate(std::ranges::input_range auto&& bank)
    requires std::same_as<std::ranges::range_value_t<decltype(bank)>, u64>
{
    using IteratorType = std::ranges::iterator_t<decltype(bank)>;

    u64 joltage{0};

    std::array<IteratorType, W> windows{};
    for (const size_t idx : std::views::iota(0U, W)) {
        windows[idx] = bank.begin() + idx;
    }

    bool window_moved{false};
    do {
        u64 value{0};
        for (const IteratorType& window : windows) {
            value = 10 * value + *window;
        }
        joltage = std::max(joltage, value);

        IteratorType end{bank.end()};
        window_moved = false;
        for (auto it{windows.rbegin()}; it != windows.rend(); it++) {
            IteratorType next{std::next(*it)};
            if (next < end) {
                *it = next;

                for (auto following{it.base()}; following != windows.end(); following++) {
                    *following = std::next(*std::prev(following));
                }
                window_moved = true;
                break;
            }
            end = *it;
        }
    } while (window_moved);

    return joltage;
}

std::tuple<u64, u64> reference(const std::vector<std::string>& input) {
    u64 joltages2{0};
    u64 joltages12{0};
    for (const auto& line : input) {
        auto bank{line | std::views::transform(char2num)};

        joltages2 += reference_calculate<2>(bank);
        // this is insanely slow a it has to calculate a lot of combinations
        joltages12 += reference_calculate<12>(bank);
        // a sliding window approach,
        // where each window starts at x+1 where x is the previous window.
        // The windows must not overlap or overrun each other.
        // For part 1 we have 2 windows, so a simple nested loop does the trick.
        // Hint: In debug mode, this is painfully slow,
        // but with compiler optimizations enabled this becomes blazingly fast.
        // Almost as fast as the "optimized" solution.
        // for (auto idx0{bank.begin()}; idx0 < bank.end() - 1; idx0++) {
        //     for (auto idx1{idx0 + 1}; idx1 < bank.end(); idx1++) {
        //         joltage = std::max(joltage, *idx0 * 10 + *idx1);
        //     }
        // }
        // joltages += joltage;
    }
    return {joltages2, joltages12};
}

u64 optimized_calculate(auto& bank, const size_t windows) {
    u64 joltage{0};

    auto pos{bank.begin()};
    for (const size_t offset : std::views::iota(0U, windows) | std::views::reverse) {
        pos = std::max_element(pos, bank.end() - offset);
        joltage = joltage * 10 + *pos;
        pos++;
    }

    return joltage;
}

std::tuple<u64, u64> optimized(const std::vector<std::string>& input) {
    u64 joltages2{0};
    u64 joltages12{0};
    for (const auto& line : input) {
        auto bank{line | std::views::transform(char2num)};

        joltages2 += optimized_calculate(bank, 2);
        joltages12 += optimized_calculate(bank, 12);
    }

    return {joltages2, joltages12};
}
