#include "leetcode.h"

class Solution {
public:
    bool isMonotonic(vector<int>& A) {
        bool ret = true;

        int min = -100001;
        for (int i=0; i < A.size(); i++) {
            if (A[i] >= min) {
                min = A[i];
            } else {
                ret = false;
                break;
            }
        }

        if (ret == true)
            return ret;

        ret = true;
        int max = 100001;
        for (int i=0; i < A.size(); i++) {
            if (A[i] <= max) {
                max = A[i];
            } else {
                ret = false;
                break;
            }
        }
        return ret;
    }
};