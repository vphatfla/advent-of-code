#include "parser.h"
#include <deque>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

const auto FILE_PATH= "data/day_4.txt";

inline auto isPaperRoll(const std::vector<std::string>& matrix, const int& x, const int& y) -> bool {
    if (x < 0 || x >= matrix.size() || y < 0 || y >= matrix[x].size() || matrix[x][y] != '@') {
        return false;
    }
    return true;
}
inline auto countAdjRoll(const std::vector<std::string>& matrix, const std::vector<int>& direction, const int& x, const int& y) -> int {
    auto res = 0;
    for (const auto& i: direction) {
        for (const auto& j: direction) {
            if (i==0 && j==0) {
                continue;
            }
            if (isPaperRoll(matrix, x+i, y+j)) {
                res += 1;
            }
        }
    }
    return res;
}

inline auto processCell(const std::vector<std::string>& matrix, std::vector<std::vector<int>>& countNeighborRolls, std::deque<std::pair<int, int>>& coordinateJobs, const std::vector<int>& direction, const int& x, const int& y) {
   for (const auto& i: direction) {
        for (const auto& j: direction) {
            if (i==0 && j==0) {
                continue;
            }
            auto neighborRow = x + i;
            auto neighborCol = y + j;
            if (isPaperRoll(matrix, neighborRow, neighborCol) && countNeighborRolls[neighborRow][neighborCol] >=0) {
                countNeighborRolls[neighborRow][neighborCol] -= 1;
                if (countNeighborRolls[neighborRow][neighborCol] < 4) {
                    coordinateJobs.emplace_back(std::pair<int, int>{neighborRow, neighborCol});
                }
            }
        }
    }
}
inline auto countAccessablePaperRoll() -> long {
    long res = 0;
    auto matrix = parseArrayOfLineFromFile(FILE_PATH);
    std::vector<std::vector<int>> countNeighborRolls;
    std::deque<std::pair<int, int>> coordinateJobs;
    countNeighborRolls.resize(matrix.size());
    for (auto i =0; i<countNeighborRolls.size(); i+=1 ){
        countNeighborRolls[i].resize(matrix[i].size());
    }
    auto direction = std::vector<int> { -1,0,1};

    for (auto r = 0; r < matrix.size(); r+=1) {
        for (auto c = 0; c < matrix[r].size(); c += 1) {
            if (matrix[r][c] != '@') {
                continue;
            }
            countNeighborRolls[r][c] = countAdjRoll(matrix, direction, r, c);
            if (countNeighborRolls[r][c] < 4) {
                coordinateJobs.emplace_back(std::pair<int, int>{r,c});
            }
        }
    }

    while (!coordinateJobs.empty()) {
        auto [r, c] = coordinateJobs.front();
        coordinateJobs.pop_front();
        if (countNeighborRolls[r][c] == -1) {
            continue;
        }
        processCell(matrix, countNeighborRolls, coordinateJobs, direction, r, c);
        countNeighborRolls[r][c] = -1;
        res += 1;
    }

    return res;
}
