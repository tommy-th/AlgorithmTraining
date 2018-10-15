#include "leetcode.h"

class Solution {
public:
    int partitionDisjoint(vector<int>& A) {
        vector<int> minRight = vector<int>(A.size() + 1, 100000000);

        for (int i=A.size()-1; i>=0; i--) {
            minRight[i] = min(minRight[i+1], A[i]);
        }

        int maxLeft = 0;
        for (int i=0; i<A.size(); i++) {
            maxLeft = max(maxLeft, A[i]);

            if (maxLeft <= minRight[i+1])
                return i+1;
        }

        return -1;
    }
};