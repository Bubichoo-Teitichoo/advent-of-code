#include <cassert>
#include <cmath>
#include <format>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "aoc.hpp"
#include "aoc_main.hpp"

std::tuple<int, int> reference(const std::vector<std::string>& input);
std::tuple<int, int> optimized(const std::vector<std::string>& input);

void solve(const std::vector<std::string>& input) {
    const auto reference_solution{reference(input)};
    const auto optimized_solution{optimized(input)};

    assert(reference_solution == optimized_solution && "Results of reference and optimized solutions do not match.");

    std::cout << std::format("The password for stage 1 is '{}'\n", std::get<0>(optimized_solution));
    std::cout << std::format("The password for stage 2 is '{}'\n", std::get<1>(optimized_solution));

    BENCH(reference(input), 5000);
    BENCH(optimized(input), 5000);
}

std::tuple<int, int> reference(const std::vector<std::string>& input) {
    int position{50};
    int zero_hits{0};
    int zero_pass_by{0};
    for (const auto& rotation : input) {
        assert(rotation[0] == 'L' or rotation[0] == 'R' && "First character of a rotation must be a either 'L' or 'R'");

        const int direction{rotation[0] == 'L' ? -1 : 1};
        const int clicks{(direction * str2int<int>(rotation.substr(1)))};

        for (int i{0}; i < std::abs(clicks); i++) {
            if (i and position == 0) {
                zero_pass_by++;
            }
            position = (100 + (position + static_cast<int>(std::copysign(1, clicks)))) % 100;
        }
        if (position == 0) {
            zero_hits += 1;
        }
    }
    return {zero_hits, zero_hits + zero_pass_by};
}

std::tuple<int, int> optimized(const std::vector<std::string>& input) {
    int position{50};
    int zero_hits{0};
    int zero_pass_by{0};
    for (const auto& rotation : input) {
        assert(rotation[0] == 'L' or rotation[0] == 'R' && "First character of a rotation must be a either 'L' or 'R'");

        const int direction{rotation[0] == 'L' ? -1 : 1};
        const int clicks{direction * str2int<int>(rotation.substr(1))};

        const int position_next{clicks + position};
        const bool start_on_zero{position % 100 == 0};
        const bool end_on_zero{position_next % 100 == 0};

        // part 1: Only increment when the position is a multiple of 100
        zero_hits += static_cast<int>(end_on_zero);

        // part 2: Only increment when 0 was passed "during" incrementing
        // 1. If clicks is larger than 100, the multiples of 100 are guaranteed pass-bys
        // 2. If the current or new position is not a 0...
        //   - check if the sign changed, which is an indicator of 0 pass-by
        //   - calculate the relative changes of the hudreth digit (170 -> 280 ^= 1).
        //     As this also takes clicks into account, they have to subtracted.
        const int clicks_wraparound{std::abs(clicks / 100)};
        zero_pass_by += clicks_wraparound;
        if (!(start_on_zero || end_on_zero)) {
            if (std::copysign(1, position) != std::copysign(1, position_next)) {
                zero_pass_by += 1;
            }
            const int max{std::max(position, position_next)};
            const int min{std::min(position, position_next)};
            zero_pass_by += std::abs(max / 100 - min / 100) - clicks_wraparound;
        }
        position = position_next;
    }

    return {zero_hits, zero_hits + zero_pass_by};
}
