#include "leetcode.h"

class Solution {
public:
    int surfaceArea(vector<vector<int>>& grid) {
        int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
        int ret = 0;

        for (int i=0; i<grid.size(); i++) {
            for (int j=0; j<grid[i].size(); j++) {
                if (grid[i][j]) {
                    ret+=2;
                }

                for (int k=1; k<=grid[i][j]; k++) {
                    for(int d =0; d<4; d++) {
                        int di = i+dir[d][0];
                        int dj = j+dir[d][1];

                        if (di >= 0 && di < grid.size() && dj >= 0 && dj < grid[i].size()) {
                            if (k > grid[di][dj])
                                ret++;
                        } else {
                            ret++;
                        }
                    }
                }
            }
        }

        return ret;
    }
};
