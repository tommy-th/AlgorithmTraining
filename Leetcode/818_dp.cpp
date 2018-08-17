class Solution {
public:
    int dp[10001];

    int racecar(int t) {
        if (dp[t] > 0) return dp[t];
        int n = floor(log2(t)) + 1;
        if ((1 << n) - 1 == t) dp[t] = n;
        else {
            int res = racecar((1 << n) - 1 - t);
            dp[t] = res + n + 1;
            for (int m = 0; m < n - 1; ++m) {
                res = racecar(t - ((1 << (n - 1)) - 1) + ((1 << m) - 1));
                dp[t] = min(dp[t], res + n + m + 1);
            }
        }
        return dp[t];
    }
};
