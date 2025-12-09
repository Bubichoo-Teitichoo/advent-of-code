#include <cassert>
#include <charconv>
#include <format>
#include <iostream>
#include <string>
#include <vector>

int str2int(std::string_view str) {
    int number{0};
    const auto [ptr, ec] = std::from_chars(std::begin(str), std::end(str), number);
    assert(ec == std::errc());
    return number;
}

int normalize_offset(const int offset, const int maximum) {
    if (offset >= 0) {
        return offset;
    }
    // a negative offset is already a pass-by so the +1 is needed
    // this only calculates the multiple of clicks per full turn as this is what matters.
    return ((std::abs(offset) / maximum) + 1) * maximum;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    if (args[0] == "--") {
        std::cout << "Reading inputs from stdin\n";
        args.clear();
        for (std::string line; std::getline(std::cin, line);) {
            args.push_back(std::move(line));
        }
    }

    const constexpr int dial_max{100};  // the dial goes from 0-99 so effectively 100 numbers.

    int position{50};
    int zero_turns{0};
    int zero_passes{0};

    for (const auto& arg : args) {
        assert(arg[0] == 'L' or arg[0] == 'R' && "First character of a rotation must be a either 'L' or 'R'");

        const int direction{arg[0] == 'L' ? -1 : 1};
        const int clicks{direction * str2int(arg.substr(1))};

        // a normalized number of clicks relative to 0
        const int offset{position + clicks};
        const int revolutions{normalize_offset(offset, dial_max) / dial_max};

        if (revolutions) {
            // if the dial lands directly on a zero it does not count as a pass-by
            // same goes for turning the dial left and it started at 0
            zero_passes +=
                revolutions - static_cast<int>(offset % dial_max == 0) - static_cast<int>(offset < 0 && position == 0);
        }
        // Usually the equation would look as follow: position = (position + clicks) % max.
        // To compensate for a negative wrap around we add an active 0 (max % max) to the equation:
        // (max + (position + clicks)) % max
        position = (dial_max + (offset % dial_max)) % dial_max;
        if (position == 0) {
            zero_turns++;
        }
    }

    std::cout << std::format("The password for stage 1 is '{}'\n", zero_turns);
    std::cout << std::format("The password for stage 2 is '{}'\n", zero_turns + zero_passes);
    return 0;
}
