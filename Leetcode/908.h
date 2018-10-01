#include "leetcode.h"

class Solution {
public:
    int smallestRangeI(vector<int>& A, int K) {
        int minval = 1000000;
        int maxval = 0;

        for (auto v : A) {
            minval = min(minval, v);
            maxval = max(maxval, v);
        }

        maxval = maxval - K > minval ? maxval - K : minval;
        minval = minval + K > maxval ? maxval : minval + K;

        return maxval - minval;
    }
};