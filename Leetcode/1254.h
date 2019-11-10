#include "leetcode.h"

class Solution {
public:
    int rows = 0;
    int cols = 0;
    const vector<vector<int>> dirs = {{0,1}, {1,0}, {-1,0}, {0,-1}};

    bool checkIsIsland(int row, int col, vector<vector<int>>& grid) {
        bool ret = true;

        queue<pair<int, int>> q;
        q.push({row, col});

        while (not q.empty()) {
            auto p = q.front(); q.pop();

            if (p.first == 0 || p.second == 0 || p.first == rows-1 || p.second == cols-1)
                ret = false;

            for (const auto& dir : dirs) {
                int nrow = p.first + dir[0];
                int ncol = p.second + dir[1];

                if (nrow < 0 || ncol < 0 || nrow >= rows || ncol >= cols)
                    continue;

                if (grid[nrow][ncol] == 0) {
                    grid[nrow][ncol] = 1;
                    q.push({nrow, ncol});
                }
            }
        }

        return ret;
    }

    int closedIsland(vector<vector<int>>& grid) {
        int ret = 0;
        rows = grid.size();
        cols = grid[0].size();

        for (int row=0; row<rows; row++) {
            for (int col=0; col<cols; col++) {
                if (grid[row][col]==0 && checkIsIsland(row, col, grid)) {
                    ++ret;
                }
            }
        }
        return ret;
    }
};