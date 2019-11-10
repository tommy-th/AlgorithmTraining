#include "leetcode.h"

class Solution {
public:
    vector<vector<int>> reconstructMatrix(int upper, int lower, vector<int>& colsum) {
        auto ret = vector<vector<int>>(2, vector<int>(colsum.size(), 0));

        int last = 0;
        for (int i=0; i<colsum.size(); i++) {
            int sums = colsum[i];
            if (sums > 2) return vector<vector<int>>();
            else if (sums == 2) {
                ret[0][i] = ret[1][i] = 1;
                --upper;
                --lower;
            } else if (sums == 1) {
                ++last;
            }
        }

        if (upper < 0 || lower < 0 || upper+lower != last)
            return vector<vector<int>>();

        for (int i=0; i<colsum.size(); i++) {
            int sums = colsum[i];

            if (sums != 1) continue;

            if (upper > 0) {
                ret[0][i] = 1;
                --upper;
            } else {
                ret[1][i] = 1;
            }
        }
        return ret;
    }
};