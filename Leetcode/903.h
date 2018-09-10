#include "leetcode.h"

class Solution {
    using LL = long long int;
public:
    int numPermsDISequence(string S) {
        int n = S.size();
        LL mod = 1e9 + 7;
        //dp[i][f] = S를 i번 째 수행할 때 앞에 f개 있을 때 경우의 수
        auto dp = vector<vector<LL>>(205, vector<LL>(205, 0));

        for (int f=0; f<=n; f++) {
            dp[0][f] = 1;
        }

        for (int i=1; i<=n; i++) {
            int lest = n-i+1;
            for (int f=0; f<=lest; f++) {
                if (S[i-1] == 'D') {
                    for (int k=1; f-k>=0; k++) {
                        dp[i][f-k] = (dp[i][f-k] + dp[i-1][f]) % mod;
                    }
                } else {
                    int b = lest-f;
                    for (int k=1; b-k>=0; k++) {
                        dp[i][f+k-1] = (dp[i][f+k-1] + dp[i-1][f]) % mod;
                    }
                }
            }
        }

        return dp[n][0];
    }
};