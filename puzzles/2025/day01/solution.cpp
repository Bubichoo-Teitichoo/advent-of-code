#include <cassert>
#include <cmath>
#include <format>
#include <iostream>
#include <string>
#include <vector>

#include "aoc.hpp"

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    if (args[0] == "--") {
        std::cout << "Reading inputs from stdin\n";
        args.clear();
        for (std::string line; std::getline(std::cin, line);) {
            args.push_back(std::move(line));
        }
    }

    int position{50};
    int zero_hits{0};
    int zero_pass_by{0};
    for (const auto& arg : args) {
        assert(arg[0] == 'L' or arg[0] == 'R' && "First character of a rotation must be a either 'L' or 'R'");

        const int direction{arg[0] == 'L' ? -1 : 1};
        const int clicks{direction * str2int(arg.substr(1))};

        // std::cout << std::format("Dial {:>5} - Clicks {:>4} - Zeros hits {:>3} - Zero pass-bys {:>4}\n", position,
        //                          clicks, zero_hits, zero_pass_by);

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

    std::cout << std::format("The password for stage 1 is '{}'\n", zero_hits);
    std::cout << std::format("The password for stage 2 is '{}'\n", zero_hits + zero_pass_by);

    assert(zero_hits == 962);
    assert(zero_hits + zero_pass_by == 5782);
    return 0;
}
