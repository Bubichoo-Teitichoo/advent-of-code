#include <cmath>
#include <cstdint>
#include <format>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

#include "aoc.hpp"
#include "aoc_main.hpp"

using u64 = uint64_t;

void solve(const std::vector<std::string>& input) {
    u64 sum1{0};
    u64 sum2{0};

    auto ranges = input | split_transformer(',') | std::views::join;

    for (const auto& range : ranges) {
        const auto bounds{split(range, '-')};

        const u64 lower{str2int<u64>(bounds[0])};
        const u64 upper{str2int<u64>(bounds[1])};

        for (u64 number{lower}; number <= upper; number++) {
            const unsigned num_digits{static_cast<unsigned>(1 + std::log10(number))};

            // part 1
            if (num_digits % 2 == 0) {
                const u64 multiplier{static_cast<u64>(std::pow(10, num_digits / 2))};
                const u64 digits{number / multiplier};
                const u64 pattern{repeat(digits, static_cast<u64>(2))};
                if (pattern == number) {
                    sum1 += number;
                }
            }

            // at most the a pattern can be half the number of digits
            for (u64 pd{1}; pd <= num_digits / 2; pd++) {
                // multiplier/divisor to get the upper n digit
                const u64 multiplier{static_cast<u64>(std::pow(10, num_digits - pd))};
                const u64 digits{number / multiplier};

                const u64 pattern{repeat(digits, num_digits / pd)};
                if (pattern == number) {
                    sum2 += number;
                    break;
                }
            }
        }
    }

    std::cout << std::format("Sum of invalid IDs of part 1 is {}\n", sum1);
    std::cout << std::format("Sum of invalid IDs of part 2 is {}\n", sum2);
}
