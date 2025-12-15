#include <cmath>
#include <cstdint>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "aoc.hpp"

template <typename T>
inline T repeat(T number, T count) {
    const T digits{static_cast<T>(1 + std::log10(number))};
    const T multiplier{static_cast<T>(std::pow(10, digits))};
    T result{0};
    for (T i{0}; i < count; i++) {
        result = (result * multiplier) + number;
    }
    return result;
}

using u64 = uint64_t;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << std::format("Invalid arguments\nUsage: {} [<file>|--]\n\n", argv[0])
                  << "Pass a filename to read the input data from.\nWhen passing the data via stdin use '--' instead.";
    }

    std::vector<std::string> arguments{argv + 1, argv + argc};
    std::filesystem::path file{arguments[0]};
    if (not std::filesystem::exists(file)) {
        std::cerr << std::format("'{}' does not exist\n", file.string());
        return 1;
    }
    if (not std::filesystem::is_regular_file(file)) {
        std::cerr << std::format("'{}' it not a regular file\n", file.string());
        return 1;
    }
    std::cout << std::format("Reading inputs from {}\n", file.string());

    std::ifstream reader{file};
    if (not reader.is_open()) {
        std::cerr << std::format("opening '{}' failed\n", file.string());
        return 1;
    }

    u64 sum1{0};
    u64 sum2{0};
    for (std::string line{}; std::getline(reader, line);) {
        std::istringstream line_stream{std::move(line)};
        for (std::string range{}; std::getline(line_stream, range, ',');) {
            const size_t dash_pos{range.find('-')};

            const std::string lhs{range.substr(0, dash_pos)};
            const std::string rhs{range.substr(dash_pos + 1)};

            const u64 lower{str2int<u64>(lhs)};
            const u64 upper{str2int<u64>(rhs)};

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
    }

    std::cout << std::format("Sum of invalid IDs of part 1 is {}\n", sum1);
    std::cout << std::format("Sum of invalid IDs of part 2 is {}\n", sum2);

    return 0;
}
