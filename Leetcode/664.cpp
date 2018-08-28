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
        int dp[100][100][27];

        for (int i=0; i<N; i++)
            for (int j=0; j<N; j++)
                for (int k=0; k<27; k++)
                    dp[i][j][k] = -1;

        function<int(int, int , int)> dfs = [&](int i, int j, int k) {
            if (i > j || k < 0 || k > 26) return 0;
            if (dp[i][j][k] >= 0) return dp[i][j][k];

            if (target[i] == k) {
                dp[i][j][k] = dfs(i+1, j, k);
            } else {
                dp[i][j][k] = min(dfs(i+1, j, k) + 1, dfs(i, j, target[i]) + 1);

                for (int mid=i+1; mid<=j; mid++) {
                    if (target[i] != target[mid]) continue;

                    int temp = dfs(i, mid, target[i]) + dfs(mid+1, j, k) + 1;

                    dp[i][j][k] = min(dp[i][j][k], temp);
                }
            }

            return dp[i][j][k];
        };

        return dfs(0, N-1, 0);
    }
};
