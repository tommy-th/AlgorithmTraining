#include "leetcode.h"

class Solution {
public:
    int strangePrinter(string s) {
        vector<int> target;

        char c = '\0';
        for (int i=0; i<s.size(); i++) {
            if (s[i] == c && i<s.size()-1) continue;
            else {
                c = s[i];
                target.push_back(c - 'a' + 1);
            }
        }

        int N = target.size();
        int dp[100][100] = {0, };

        function<int(int, int)> dfs = [&](int i, int j) {
            if (i > j) return 0;
            if (dp[i][j] > 0) return dp[i][j];

            dp[i][j] = 1 + dfs(i+1, j);
            for (int mid=i+1; mid<=j; mid++) {
                if (target[i] == target[mid]) {
                    dp[i][j] = min(dp[i][j], dfs(i, mid-1) + dfs(mid+1, j));
                }
            }

            return dp[i][j];
        };

        return dfs(0, N-1);
    }
};
