#include "leetcode.h"

class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        int totalCount = 0;
        int ylen = grid.size();
        int xlen = grid[0].size();

        for (int i=0; i<ylen; i++) {
            for (int j=0; j<xlen; j++) {
                if (grid[i][j] > 0)
                    totalCount++;
            }
        }

        for (int i=0; i<ylen; i++) {
            int max = 0;
            for (int j=0; j<xlen; j++) {
                if (grid[i][j] > max)
                    max = grid[i][j];
            }
            totalCount += max;
        }

        for (int j=0; j<xlen; j++) {
            int max = 0;
            for (int i=0; i<ylen; i++) {
                if (grid[i][j] > max)
                    max = grid[i][j];
            }
            totalCount += max;
        }
        return totalCount;
    }
};
