#include "leetcode.h"

class Solution {
using LL = long long int;
public:
    string decodeAtIndex(string S, int K) {
        LL totalCount = 0;

        for (int i=0; i<S.size(); i++) {
            if (isdigit(S[i])) {
                totalCount *= (S[i]-'0');
            } else {
                totalCount++;
            }
        }

        for (int i=S.size()-1; i>=0; i--) {
            if (isdigit(S[i])) {
                totalCount /= (S[i]-'0');
                if (K >= totalCount)
                    K %= totalCount;
                if (K == 0) K = totalCount;
            } else {
                if (K==totalCount) return S.substr(i, 1);
                totalCount--;
            }
        }

        return "";
    }
};
