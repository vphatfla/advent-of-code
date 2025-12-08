#include "parser.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>

const auto FILE_PATH = "data/day_3.txt";
const auto FILE_PATH_TEMP = "data/temp_data.txt";

inline auto largestJoltageTwoBank() -> unsigned long {
    unsigned long res = 0;
    auto array_str = parseArrayOfLineFromFile(FILE_PATH);

    for (const auto& str: array_str) {
        auto max_joltage = 0;
        auto max_digit_so_far = str[0] - '0';
        for (int i=1; i<str.size(); i+=1) {
            auto curr_num = str[i] - '0';
            max_joltage = std::max(max_joltage, max_digit_so_far*10 + curr_num);
            max_digit_so_far = std::max(max_digit_so_far, curr_num);
        }
        res += max_joltage;
    }

    return res;
}

inline auto max_digit_and_position_in_bound(const std::string& str, const int& left, const int& right) -> std::tuple<int, int>{
    auto max = str[right] - '0';
    auto pos = right;
    for (int i = right; i>= left; i -= 1) {
        auto curr_digit = str[i] - '0';
        if (curr_digit >= max) {
            max = curr_digit;
            pos = i;
        }
    }

    return {max, pos};
}

inline auto largestJoltageTwelveBank() -> unsigned long long {
    unsigned long res = 0;
    auto array_str = parseArrayOfLineFromFile(FILE_PATH);

    for (const auto& str: array_str) {
        unsigned long long max_joltage = 0;
        auto left_bound = 0;
        auto size = str.size();
        for (auto i = 12; i>=1; i-=1) {
            auto [max, pos] = max_digit_and_position_in_bound(str, left_bound, size - i);
            max_joltage = max_joltage*10 + max;
            // std::cout << "max =" << max << " post=" << pos << " max_joltage=" << max_joltage << std::endl;
            left_bound = pos + 1;
        }

        // std::cout << str << " with max = " << max_joltage << std::endl;
        res += max_joltage;
    }
    return res;
}
