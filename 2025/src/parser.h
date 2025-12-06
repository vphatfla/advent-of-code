#pragma once

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

inline auto parseStringFromFile(const std::string& file_path) -> std::string {
    std::string res;
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Can not open file");
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        res += line;
    }
    return res;
};

inline auto parseArrayOfLineFromFile(const std::string& file_path) -> std::vector<std::string> {
    std::vector<std::string> res;

    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Can not open file");
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        res.emplace_back(line);
    }
    return res;
};
