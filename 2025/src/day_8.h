#pragma once

#include "parser.h"
#include "helper.h"
#include <algorithm>
#include <cmath>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
#include <ranges>

const auto FILE_PATH = "data/temp_data.txt";

struct PairDistance {
    int i1;
    int i2;
    double distance;
};

auto inline calculateDistanceTwoPoints(const std::vector<int>& p1, const std::vector<int>& p2) -> double {
    double res = 0;
    for (auto i = 0; i < p1.size(); i+=1) {
        res +=  std::pow(p1[i] - p2[i], 2);
    }
    return res;
}

auto inline find(std::vector<int>& parents, const int& i) -> int {
    if (parents[i] == i) {
        return i;
    }
    parents[i] = find(parents, parents[i]);
    return parents[i];
}

auto inline unionPair(std::vector<int>& parents, const int& x, const int& y) -> bool {
    auto p_x = find(parents, x), p_y = find(parents, y);
    if (p_x == p_y) {
        return false; //  already merge
    }
    parents[x] = p_y;
    return true;
}

auto inline multipleCircuitSize() -> unsigned long long {
    unsigned long long res = 0;

    auto raw_input = parseArrayOfLineFromFile(FILE_PATH);
    auto n = raw_input.size();
    std::vector<std::vector<int>> points;
    std::vector<PairDistance> distances;
    for (const auto& str: raw_input) {
        auto temp_str = splitString(str, ',');
        auto temp = temp_str | std::views::transform([](std::string str){ return std::stoi(str);});
        auto temp_int = std::vector<int>(temp.begin(), temp.end());
        points.emplace_back(std::move(temp_int));
    }

    for (auto i = 0; i < n; i+=1) {
        for (auto j = i + 1; j < n; j += 1) {
            auto d = calculateDistanceTwoPoints(points[i], points[j]);
            distances.emplace_back(PairDistance{.i1 = i, .i2 = j, .distance = d});
        }
    }

    std::ranges::sort(distances, {}, &PairDistance::distance);

    // to store the point, use a vector of a tuple <int, int int>
    // to store the "circuit" information, can do something like a union finda

    std::vector<int> parents(n);
    std::iota(parents.begin(), parents.end(), 0);
    // need a way to store the # of point in a cirtui, might need another vector?
}
