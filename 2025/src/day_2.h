#include "parser.h"
#include "helper.h"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

const auto FILE_PATH = "data/day_2.txt";

auto inline isStringRepeatedSubstr(const std::string& str) -> bool {
    auto concatted_str = str + str;
    auto cropped_str = concatted_str.substr(1, concatted_str.size() - 2);

    return cropped_str.find(str) != std::string::npos;
}

auto inline calculateInvalidIds() -> unsigned long long {
    unsigned long long res = 0;
    auto input = parseStringFromFile(FILE_PATH);
    auto array = splitString(input, ',');

    for (auto& str: array) {
        std::cout << str << std::endl;
        auto temp = splitString(str, '-' );
        auto begin = std::stoull(temp[0]), end = std::stoull(temp[1]);
        for (auto i = begin; i <= end; i+=1) {
            auto str_temp = std::to_string(i);
            if (isStringRepeatedSubstr(str_temp)) {
                std::cout << i << " checked valid" << std::endl;
                res += i;
            }
        }
    }
    return res;
}


