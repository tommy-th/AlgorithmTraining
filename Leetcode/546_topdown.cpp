class Solution {
public:
// top down solution
    int removeBoxes(vector<int>& boxes) {
        vector<int> colors, counts;

        for (int i=1, count=1; i <= boxes.size(); i++) {
            if (boxes[i] != boxes[i-1] || i==boxes.size()) {
                colors.push_back(boxes[i-1]);
                counts.push_back(count);
                count = 1;
            } else {
                count++;
            }
        }

        // dp[i][j][k] = i ~ j 까지 colors[i]가 앞에 k개 있을 때 최대 값
        int dp[100][100][100] = {0};

        function<int(int, int , int)> dfs = [&](int i, int j, int k) {
            if (i > j) return 0;
            if (dp[i][j][k]) return dp[i][j][k];

            dp[i][j][k] = (k+counts[i]) * (k+counts[i]) + dfs(i+1, j, 0);

            for (int pos=i+1; pos<=j; pos++) {
                if (colors[i] == colors[pos]) {
                    dp[i][j][k] = max(dp[i][j][k], dfs(i+1, pos-1, 0) + dfs(pos, j, k+counts[i]));
                }
            }

            return dp[i][j][k];
        };

        return dfs(0, colors.size()-1, 0);
    }
};
