#include "leetcode.h"

class Solution {
public:
    int oddCells(int n, int m, vector<vector<int>>& indices) {
        int ret = 0;

        for (int row = 0; row < n; row++) {
            for (int col = 0; col < m; col++) {
                int counts = 0;
                for (const auto& indice : indices) {
                    if (row == indice[0]) counts++;
                    if (col == indice[1]) counts++;
                }
                if (counts % 2 == 1) ret++;
            }
        }

        return ret;
    }
};