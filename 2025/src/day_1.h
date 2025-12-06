#include "parser.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <stdexcept>

const auto FILE_PATH="data/day_1.txt";

inline auto decodePasswordFromDial() -> int {
    auto res = 0;
    auto position = 50;
    auto max_right = 99;
    auto max_left = 0;

    auto dial_instructions = parseArrayOfLineFromFile(FILE_PATH);

    for (auto& str: dial_instructions) {
        auto dir = str[0];
        auto turn = 0;
        for (size_t i = 1; i < str.size(); i+=1) {
             turn = turn * 10 + (str[i] - '0');
        }

        if (dir == 'L') {
            position -= turn;
            position %= 100;
            if (position < 0) {
                position += 100;
            }
        } else if (dir == 'R') {
            position += turn;
            position = abs(position) % 100;
        } else {
            throw std::runtime_error("invalid direction");
        }

        std::cout << dir << " turn " << turn << " to " << position << std::endl;
        res += (position == 0) ? 1 : 0;
    }

    return res;
}
