//
// Created by tata8663 on 2019/12/05.
//

#ifndef LEETCODE_1263_H
#define LEETCODE_1263_H

#endif //LEETCODE_1263_H

#include "leetcode.h"

const int dirs[4][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}};
int rows;
int cols;

struct Point {
    int row;
    int col;

    Point (int row, int col) : row(row), col(col) {}

    bool isValid() const {
        if (row < 0 || row >= rows || col < 0 || col >= cols)
            return false;
        return true;
    }

    int hash() const {
        return row * 20 + col;
    }
};

bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.row == rhs.row && lhs.col == rhs.col;
}

class Solution {
    const char floor = '.';
    const char wall = '#';

public:
    bool reachable(
            const vector<vector<char>>& grid,
            const Point box,
            const Point player,
            const Point target)
    {
        if (not target.isValid()) return false;
        if (grid[target.row][target.col] == wall) return false;
        if (target == player) return true;

        queue<Point> bfs;
        int check[25][25] = {0, };
        bfs.push(player);
        check[player.row][player.col] = 1;

        while (not bfs.empty()) {
            Point cur = bfs.front(); bfs.pop();

            for (int d = 0; d < 4; d++) {
                Point next = Point(cur.row + dirs[d][0], cur.col + dirs[d][1]);
                if (not next.isValid()) continue;
                if (next == box) continue;
                if (grid[next.row][next.col] == wall) continue;

                if (next == target) return true;

                if (check[next.row][next.col] == 0) {
                    bfs.push(next);
                    check[next.row][next.col] = 1;
                }
            }
        }

        return false;
    }

    int minPushBox(vector<vector<char>>& grid) {
        rows = grid.size();
        cols = grid[0].size();

        auto dp = vector<vector<int>>(4, vector<int>(405, -1));

        Point player(-1, -1);
        Point box(-1, -1);
        Point target(-1, -1);

        for (int row =0; row < rows; row++) {
            for (int col =0; col < cols; col++) {
                if (grid[row][col] == 'S')
                    player = Point(row, col);
                else if (grid[row][col] == 'T')
                    target = Point(row, col);
                else if (grid[row][col] == 'B')
                    box = Point(row, col);
            }
        }

        int ret = -1;
        queue<pair<int, Point>> bfs;

        for (int d = 0; d<4; d++) {
            Point approach = Point(box.row + dirs[d][0], box.col + dirs[d][1]);
            if (not approach.isValid()) continue;
            if (grid[approach.row][approach.col] == wall) continue;
            if (reachable(grid, box, player, approach)) {
                bfs.push({d, box});
                dp[d][box.hash()] = 0;
            }
        }

        while (not bfs.empty()) {
            auto el = bfs.front(); bfs.pop();
            int pd = el.first;
            box = el.second;
            player = Point(box.row, box.col);
            Point next = Point(box.row + dirs[pd][0] * -1, box.col + dirs[pd][1] * -1);

            if (not next.isValid()) continue;
            if (grid[next.row][next.col] == wall) continue;
            int count = dp[pd][box.hash()] + 1;

            if (next == target) {
                if (ret == -1 || count < ret )
                    ret = count;
            }

            if (ret != -1 && count >= ret) continue;

            for (int d = 0; d<4; d++) {
                Point approach = Point(next.row + dirs[d][0], next.col + dirs[d][1]);
                if (not approach.isValid()) continue;
                if (grid[approach.row][approach.col] == wall) continue;

                if (reachable(grid, next, player, approach)) {
                    if (dp[d][next.hash()] == -1  || count < dp[d][next.hash()]) {
                        dp[d][next.hash()] = count;
                        bfs.push({d, next});
                    }
                }
            }
        }

        return ret;
    }
};