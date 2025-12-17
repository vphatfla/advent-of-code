#pragma once

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
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

inline auto parseMultipleBlocksInputFromFile(const std::string& file_path) -> std::vector<std::vector<std::string>> {
    std::vector<std::vector<std::string>> res;

    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Can not open file");
    }

    std::vector<std::string> temp;
    std::string line;
    while (std::getline(file, line)) {
        if (line.size() != 0) {
            temp.emplace_back(line);
        } else {
            res.emplace_back(std::move(temp));
            temp.clear();
        }
    }
    res.emplace_back(std::move(temp));
    return res;
}
