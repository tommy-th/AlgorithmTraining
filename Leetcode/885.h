#include "leetcode.h"

class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int R, int C, int r0, int c0) {
        int count = 0;
        vector<vector<int>> ret(R*C, vector<int>(2, 0));

        auto check = [&](int r, int c) {
            if (r < 0 || r >= R || c < 0 || c >= C) return;
            ret[count][0] = r;
            ret[count][1] = c;

            count++;
        };

        check(r0, c0);

        for (int i=1; i <=101; i++) {
            c0++;
            check(r0, c0);
            for (int d=1; d < i*2; d++) {
                r0++;
                check(r0, c0);
            }
            for (int d=0; d < i*2; d++) {
                c0--;
                check(r0, c0);
            }
            for (int d=0; d < i*2; d++) {
                r0--;
                check(r0, c0);
            }
            for (int d=0; d < i*2; d++) {
                c0++;
                check(r0, c0);
            }
        }

        return ret;
    }
};
