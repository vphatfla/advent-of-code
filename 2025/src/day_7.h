#pragma once

#include "parser.h"
#include "helper.h"
#include <deque>
#include <string>
#include <utility>
#include <vector>
const auto FILE_PATH = "data/day_7.txt";

inline auto isCellValid(const std::vector<std::string>& input, int r, int c) -> bool {
    if (r < 0 || r >= input.size() || c < 0 || c >= input[0].size()) {
        return false;
    }
    return true;
};
inline auto countSplitting() -> unsigned long {
    long res = 0;
    auto raw_input = parseArrayOfLineFromFile(FILE_PATH);
    int n = raw_input.size(), m = raw_input[0].size();
    int r = 0, c = -1; // start cell
    for (int col = 0; col < m; col+=1) {
        if (raw_input[0][col] == 'S') {
            c = col;
            break;
        }
    }
    std::vector<int> splitColDirection = {-1, 1};
    std::vector<std::vector<bool>> processedCell(n, std::vector<bool>(m, false));
    std::deque<std::pair<int, int>> queue;
    queue.emplace_back(std::pair<int, int> (r,c));
    while (!queue.empty()) {
        auto [r,c] = queue.front();
        queue.pop_front();
        if (processedCell[r][c]) {
            continue;
        }
        processedCell[r][c] = true;
        if (raw_input[r][c] == '^') {
            for (const auto& d: splitColDirection) {
                if (isCellValid(raw_input, r + 1, c + d)) {
                    queue.emplace_back(std::pair<int, int> (r+1, c+d));
                }
            }
            if (r <= n) {
                res += 1;
            }
        } else if (isCellValid(raw_input, r+1, c)) {
            queue.emplace_back(std::pair<int, int> (r+1, c));
        }
    }

    return res;
}

inline auto countTimeline() -> unsigned long long {
    // DP
    unsigned long long res = 0;
    auto raw_input = parseArrayOfLineFromFile(FILE_PATH);
    int n = raw_input.size(), m = raw_input[0].size();
    int r = 0, c = -1; // start cell
    for (int col = 0; col < m; col+=1) {
        if (raw_input[0][col] == 'S') {
            c = col;
            break;
        }
    }

    std::vector<int> splitColDirection = {-1, 1};
    std::vector<std::vector<unsigned long long>> dp(n, std::vector<unsigned long long>(m, 0));
    dp[r][c] = 1;
    std::deque<std::pair<int, int>> queue;
    queue.emplace_back(std::pair<int, int> (r,c));
    while (!queue.empty()) {
        auto [r,c] = queue.front();
        queue.pop_front();
        /* if (dp[r][c] != 0) {
            continue;
        } */
        if (raw_input[r][c] == '^') {
           for (const auto& d: splitColDirection) {
                if (isCellValid(raw_input, r + 1, c + d)) {
                    if (dp[r+1][c+d] == 0) {
                        queue.emplace_back(std::pair<int, int> (r+1, c+d));
                    }
                    dp[r+1][c+d] += dp[r][c];
                }
            }
        } else if (isCellValid(raw_input, r+1, c)) {
                if (dp[r+1][c] == 0) {
                    queue.emplace_back(std::pair<int, int> (r+1, c));
                }
                dp[r+1][c] += dp[r][c];
        }
    }

    /*for (auto r = 0; r<n; r +=1) {
        for (auto c = 0; c < m; c+=1) {
            std::cout << dp[r][c] << "  ";
        }
        std::cout << std::endl;
    } */

    for (auto col = 0; col < m; col +=1) {
        res += dp[n-1][col];
    }

    return res;
}
