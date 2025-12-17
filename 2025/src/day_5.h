#include "parser.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "helper.h"
#include <algorithm>

const auto FILE_PATH = "data/day_5.txt";

inline auto numbersOfFreshIngredient() -> long {
    long res = 0;

    auto input = parseMultipleBlocksInputFromFile(FILE_PATH);
    auto raw_ranges = input[0], raw_ingredients = input[1];

    std::vector<std::pair<long, long>> ranges;
    std::vector<long> ingredients;

    for (const auto& r: raw_ranges) {
        auto temp = splitString(r, '-');
        ranges.emplace_back(std::move(std::pair<long, long> {std::stol(temp[0]), std::stol(temp[1])}));
    }

    std::ranges::sort(ranges, {}, &std::pair<long, long>::first);

    std::vector<std::pair<long, long>> merged_ranges;
    merged_ranges.emplace_back(std::move(ranges[0]));

    for (auto i=1; i<ranges.size(); i+=1) {
        auto& last_merged = merged_ranges[merged_ranges.size() - 1];
        if (ranges[i].first <= last_merged.second) {
            last_merged.second = std::max(last_merged.second, ranges[i].second);
        } else {
            merged_ranges.emplace_back(std::move(ranges[i]));
        }
    }

    for (const auto& i: raw_ingredients) {
        ingredients.emplace_back(std::stol(i));
    }

    for (const auto& i: ingredients) {
        // std::cout << "ingredient = " << i << std::endl;
        // can perform binrary search here
        for (const auto& r: merged_ranges) {
            // std::cout << r.first << " ; " << r.second << std::endl;
            if (r.first >= i && i <= r.second) {
                res +=1;
                break;
            }
        }
    }
    return res;
}
