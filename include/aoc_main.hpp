#if !defined(__AOC_MAIN_HPP__)
#define __AOC_MAIN_HPP__

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <vector>

void solve(const std::vector<std::string>& input);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << std::format("Invalid arguments\nUsage: {} <file>\n\n", argv[0])
                  << "Pass a filename to read the input data from.\n";
        return 1;
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

    std::vector<std::string> input{};
    for (std::string line{}; std::getline(reader, line);) {
        input.push_back(std::move(line));
    }

    solve(input);

    return 0;
}

#endif  //__AOC_MAIN_HPP__
