#include "leetcode.h"

class Solution {
public:
    int minAddToMakeValid(string S) {
        int ret = 0;

        int lc = 0, rc = 0;

        for (int i=0; i<S.size(); i++) {
            if (S[i] == '(') {
                lc++;
            } else {
                rc++;
            }

            if (rc > lc) {
                ret++;
                lc = rc = 0;
            }
        }

        return ret + lc - rc;
    }
};