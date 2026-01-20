#pragma once

#include "parser.h"
#include "helper.h"
#include <algorithm>
#include <cstdlib>
#include <future>
#include <queue>
#include <string>
#include <utility>
#include <vector>
const auto FILE_PATH = "data/day_9.txt";

using TPoint = std::pair<int, int>;
using resultType = unsigned long long;

const auto direction = std::vector<int>{-1, 0, 1};

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

// @brief this does not work since sweepline can't properly find the compared products
inline auto largestRectangleAreaSweepLine() -> unsigned long long {
    resultType res = 0;
    auto raw_input = parseArrayOfLineFromFile(FILE_PATH);

    std::vector<TPoint> points;
    for (const auto& str: raw_input) {
        auto temp =  splitString(str, ',');
        points.emplace_back(std::stoi(temp[0]), std::stoi(temp[1]));
    }

    auto [minXPoint_it, maxXPoint_it] = std::ranges::minmax_element(points, {}, &TPoint::first);
    auto [minYPoint_it, maxYPoint_it] = std::ranges::minmax_element(points, {}, &TPoint::second);

    auto candidates = std::vector<TPoint>();
    for (const auto& p: points) {
        if (p.first == minXPoint_it->first || p.first == maxXPoint_it->first || p.second == minYPoint_it->second || p.second == maxYPoint_it->second) {
            candidates.emplace_back(p);
        }
    }

    for (auto i = 0; i < candidates.size(); i+=1) {
        for (auto j = i+1; j<candidates.size(); j+=1) {
            res = std::max(res, calculateArea(candidates[i], candidates[j]));
        }
    }

    return res;
}

inline auto drawGreenLine(std::vector<std::vector<int>>& matrix, const TPoint& p1, TPoint& p2) -> void {
    if (p1.first == p2.first) {
        auto min = std::min(p1.second, p2.second), max = std::max(p1.second, p2.second);
        for (auto i = min + 1; i <= max; i+=1) {
            matrix[p1.first][i] = 2;
        }
    } else if (p1.second == p2.second) {
        auto min = std::min(p1.first, p2.first), max = std::max(p1.first, p2.first);
        for (auto i = min + 1; i <= max; i+=1) {
            matrix[i][p1.second] = 2;
        }
    }
}

inline auto drawOutsider(std::vector<std::vector<int>>& matrix, const int& n, const int& m, const int& i, const int& j) -> void {
    if (i < 0 || i >= n || j < 0 || j >= m) {
        return;
    }
    if (matrix[i][j] != 0) {
        return;
    }

    std::queue<TPoint> q;
    q.push({i, j});
    matrix[i][j] = -1;

    while (!q.empty()) {
        auto [ci, cj] = q.front();
        q.pop();

        for (const auto& d1 : direction) {
            for (const auto& d2 : direction) {
                int ni = ci + d1;
                int nj = cj + d2;
                if (ni >= 0 && ni < n && nj >= 0 && nj < m && matrix[ni][nj] == 0) {
                    matrix[ni][nj] = -1;
                    q.push({ni, nj});
                }
            }
        }
    }
}

inline auto checkLoop(std::vector<std::vector<int>>& matrix, const TPoint& p1, TPoint& p2) -> bool {
    auto rowMin = std::min(p1.first, p2.first), rowMax = std::max(p1.first, p2.first);
    auto colMin = std::min(p1.second, p2.second), colMax = std::max(p1.second, p2.second);
    // std::cout << "checking loop " << rowMin << " -> " << rowMax << "  |||   " << colMin << " -> " << colMax << std::endl;
    for (auto r = rowMin; r <= rowMax; r +=1) {
        for (auto c = colMin; c <= colMax; c +=1) {
            if (matrix[r][c] == -1) {
                return false;
            }
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

   auto rowWork = std::async(std::launch::async, [&]() { for (int row = 0; row < n; row +=1) {
        drawOutsider(matrix, n, m, row, 0);
        drawOutsider(matrix, n, m, row, m-1);
   }
   });

   auto colWork = std::async(std::launch::async, [&]() { for (int col = 0; col < m; col +=1) {
       drawOutsider(matrix, n, m, 0, col);
       drawOutsider(matrix, n, m, n-1, col);
   }
   });

    rowWork.wait();
    colWork.wait();

   /* for (auto i=0; i<n; i+=1) {
        for (auto j = 0; j<m; j+=1) {
            std::cout << matrix[i][j] << "  ;  ";
        }
        std::cout << std::endl;
   } */

   for (auto i = 0; i < points.size(); i+=1) {
       for (auto j=i+1; j < points.size(); j+=1) {
            auto area = calculateArea(points[i], points[j]);
            // std::cout << points[i].first << ";" << points[i].second << " and " <<  points[j].first << " ; "<< points[j].second << "  area = " << area << std::endl;
            if (res < area && checkLoop(matrix, points[i], points[j])) {
                res = area;
            }
       }
   }

   return  res;
}
