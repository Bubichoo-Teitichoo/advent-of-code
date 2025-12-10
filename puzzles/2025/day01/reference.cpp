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
    int zero_turns{0};
    int zero_passes{0};

    for (const auto& arg : args) {
        assert(arg[0] == 'L' or arg[0] == 'R' && "First character of a rotation must be a either 'L' or 'R'");

        const int direction{arg[0] == 'L' ? -1 : 1};
        const int clicks{(direction * str2int(arg.substr(1)))};

        // std::cout << std::format("Dial {:>5} - Clicks {:>4} - Zeros hits {:>3} - Zero pass-bys {:>4}\n", position,
        //                          clicks, zero_turns, zero_passes - zero_turns);

        // Solution 5782
        for (int i{0}; i < std::abs(clicks); i++) {
            position += std::copysign(1, clicks);
            if (position < 0) {
                position = 99;
            } else if (position > 99) {
                position = 0;
            }

            if (position == 0) {
                zero_passes++;
            }
        }
        if (position == 0) {
            zero_turns += 1;
        }
    }

    std::cout << std::format("The password for stage 1 is '{}'\n", zero_turns);
    std::cout << std::format("The password for stage 2 is '{}'\n", zero_passes);

    assert(zero_turns == 962);
    assert(zero_passes == 5782);
    return 0;
}
