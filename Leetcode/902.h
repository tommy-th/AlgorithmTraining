#include "leetcode.h"

class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& D, int N) {
        vector<bool> disit = vector<bool>(11, false);
        vector<int> less = vector<int>(11, 0);

        for (int i=1, j=0; i<10; i++) {
            less[i] = less[i-1];

            if (j < D.size() && D[j][0] - 48 == i) {
                less[i]++;
                disit[i] = true;
                j++;
            }
        }

        int idx = 0;
        vector<vector<int>> dp;
        dp.push_back({less[9], less[N % 10]});

        int dec = 10;
        while (dec <= N) {
            int cur = (N / dec) % 10;

            int all = dp[idx][0] * less[9];
            int lessEquals = disit[cur] ? dp[idx][0] * (less[cur] - 1) + dp[idx][1] : dp[idx][0] * less[cur];

            dp.push_back({all, lessEquals});

            dec *= 10;
            idx++;
        }

        int ret = dp[dp.size()-1][1];
        for (int i=0; i < dp.size()-1; i++) {
            ret += dp[i][0];
        }

        return ret;
    }
};