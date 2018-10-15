#include "leetcode.h"

class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& A) {
        vector<int> ret = vector<int>(A.size());

        int eveni=0;
        int oddi=1;
        for (int i=0; i<A.size(); i++) {
            if (A[i] % 2 == 0) {
                ret[eveni] = A[i];
                eveni+=2;
            } else {
                ret[oddi] = A[i];
                oddi+=2;
            }
        }
        return ret;
    }
};