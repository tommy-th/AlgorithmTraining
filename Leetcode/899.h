#include "leetcode.h"

class Solution {
public:
    string orderlyQueue(string S, int K) {
        string ret = S;
        if (K==1) {
            for (int i=1; i < S.size(); i++) {
                string temp = S.substr(i, S.size()-i) + S.substr(0, i);
                if (temp < ret) {
                    ret = temp;
                }
            }
        } else {
            sort(ret.begin(), ret.end());
        }

        return ret;
    }
};