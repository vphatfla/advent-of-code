#pragma once

#include "parser.h"
#include "helper.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
const auto FILE_PATH = "data/day_6.txt";

inline void calculateResult(unsigned long long& result, int number, const std::string& op) {
   if (op == "+") {
       result += number;
   } else {
       result *= number;
   }
}

inline auto performMathCalculation() -> unsigned long long {
    unsigned long long res = 0;
    auto raw_input = parseArrayOfLineFromFile(FILE_PATH);
    std::vector<std::vector<int>> numbers;
    auto operators = splitStringMultipleWhiteSpace(raw_input[raw_input.size() - 1]);
    for (auto i = 0; i < raw_input.size()-1; i+=1) {
        std::vector<int> temp;
        auto raw_numbers = splitStringMultipleWhiteSpace(raw_input[i]);
        for (const auto& str: raw_numbers) {
            std::cout << str << " , ";
            temp.emplace_back(std::stoi(str));
        }
        std::cout << std::endl;
        numbers.emplace_back(std::move(temp));
    }
     
    for (auto col = 0; col < operators.size(); col+=1) {
        unsigned long long temp = numbers[0][col];
        for (auto row = 1; row < numbers.size(); row +=1) {
           calculateResult(temp, numbers[row][col], operators[col]);
        }
        res += temp;

        std::cout << "res = " << res << " & temp=" << temp << std::endl;
    }

    return res;
}
