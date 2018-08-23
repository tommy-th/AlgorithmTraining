class Solution {
public:
// bottom up solution
    int removeBoxes(vector<int>& boxes) {
        int N = boxes.size();

        // dp[i][j][k] = i ~ j 까지 colors[i]가 앞에 k개 있을 때 최대 값
        auto dp = vector<vector<vector<int>>>(N, vector<vector<int>>(N, vector<int>(101, 0)));

        for (int i=0; i<N; i++)
            for (int k=0; k<=i; k++)
                dp[i][i][k] = (k + 1) * (k + 1);

        for (int len=2; len<=N; len++) {
            for (int i=0; i<N; i++) {
                int j=i+len-1;
                if (j >= N) break;

                for (int k=0; k<=i; k++) {
                    dp[i][j][k] = (k + 1) * (k + 1) + dp[i+1][j][0];

                    for (int m=i+1; m<=j; m++) {
                        if (boxes[i] == boxes[m]) {
                            dp[i][j][k] = max(dp[i][j][k], dp[i+1][m-1][0] + dp[m][j][k+1]);
                        }
                    }
                }
            }
        }

        return dp[0][N-1][0];
    }
};
