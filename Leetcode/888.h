#include "leetcode.h"

class Solution {
public:
    vector<int> fairCandySwap(vector<int>& A, vector<int>& B) {
        vector<int> checkB(100001, 0);
        long long int asum = 0;
        long long int bsum = 0;
        long long int mid;

        for (int i=0; i < A.size(); i++) {
            asum += A[i];
        }

        for (int i=0; i < B.size(); i++) {
            bsum += B[i];
            checkB[B[i]] = i+1;
        }

        mid = (asum + bsum) / 2;

        for (int i=0; i < A.size(); i++) {
            int bval = mid - asum + A[i];
            if (bval > 0 && bval <= 100000) {
                if (checkB[bval] > 0)
                    return {A[i], bval};
            }
        }

        return {0, 0};
    }
};
