#pragma once

#include "parser.h"
#include "helper.h"
#include <algorithm>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>
const auto FILE_PATH = "data/temp_data.txt";

using TPoint = std::pair<int, int>;
using resultType = unsigned long long;

inline auto calculateArea(const TPoint& p1, const TPoint& p2) -> resultType {
    return static_cast<resultType>(std::abs(p1.first - p2.first + 1)) * static_cast<resultType>(std::abs(p1.second - p2.second + 1));
}

inline auto largestRectangleAre() -> unsigned long long {
    unsigned long long res = 0;

    auto raw_input = parseArrayOfLineFromFile(FILE_PATH);

    std::vector<std::pair<int, int>> points;
    for (const auto& str: raw_input) {
        auto temp =  splitString(str, ',');
        points.emplace_back(std::stoi(temp[0]), std::stoi(temp[1]));
    }

    for (auto i = 0; i < points.size(); i+=1) {
        for (auto j = i+1; j < points.size(); j+=1) {
            res = std::max(res, calculateArea(points[i], points[j]));
        }
    }

    return res;
}

inline auto drawGreenLine(std::vector<std::vector<int>>& matrix, const TPoint& p1, TPoint& p2) -> void {
    if (p1.first == p2.first) {
        auto min = std::min(p1.second, p2.second), max = std::max(p1.second, p2.second);
        for (auto i = min + 1; i < max; i+=1) {
            matrix[p1.first][i] = 2;
        }
    } else if (p1.second == p2.second) {
        auto min = std::min(p1.first, p2.first), max = std::max(p1.first, p2.first);
        for (auto i = min + 1; i < max; i+=1) {
            matrix[i][p1.second] = 2;
        }
    }
}

inline auto checkLoop(std::vector<std::vector<int>>& matrix, const TPoint& p1, TPoint& p2) -> bool {
    auto rowMin = std::min(p1.first, p2.first), rowMax = std::max(p1.first, p2.first);
    auto colMin = std::min(p1.second, p2.second), colMax = std::max(p1.second, p2.second);
    std::cout << "checking loop " << rowMin << " -> " << rowMax << "  |||   " << colMin << " -> " << colMax << std::endl;
    for (auto i = rowMin; i <= rowMax; i+=1) {
       if (matrix[i][colMin] == 0 || matrix[i][colMax] == 0) {
            return false;
       }
    }

    for (auto j= colMin; j < colMax; j +=1) {
        if (matrix[rowMin][j] == 0 || matrix[rowMax][j] == 0) {
            return false;
        }
    }
    return true;
}

inline auto largestRedGreenArea() -> resultType {
    resultType res = 0;
    auto raw_input = parseArrayOfLineFromFile(FILE_PATH);

    std::vector<std::pair<int, int>> points;
    auto n = 0, m = 0;
    for (const auto& str: raw_input) {
        auto temp =  splitString(str, ',');
        auto x = std::stoi(temp[1]), y = std::stoi(temp[0]);
        points.emplace_back(x, y);
        n = std::max(x + 1 ,  n);
        m = std::max(y+ 1, m);
    }

    auto matrix = std::vector<std::vector<int>>(n, std::vector<int>(m, 0));
    std::cout << n << " ; " << m << std::endl;
   for (auto i = 0; i < points.size(); i+=1) {
       matrix[points[i].first][points[i].second] = 1;
       for (auto j=i+1; j < points.size(); j+=1) {
            drawGreenLine(matrix, points[i], points[j]);
       }
   }

   for (auto i=0; i<n; i+=1) {
        for (auto j = 0; j<m; j+=1) {
            std::cout << matrix[i][j] << "  ;  ";
        }
        std::cout << std::endl;
   }
   for (auto i = 0; i < points.size(); i+=1) {
       for (auto j=i+1; j < points.size(); j+=1) {
            auto area = calculateArea(points[i], points[j]);
            std::cout << points[i].first << ";" << points[i].second << " and " <<  points[j].first << " ; "<< points[j].second << "  area = " << area << std::endl;
            if (checkLoop(matrix, points[i], points[j]) && res < area) {
                res = area;
            }
       }
   }

   return  res;
}
