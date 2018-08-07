class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int nums = piles.size();
        pair<int, int> dp[505][505];

        for (int i=0; i < nums; i++) {
            dp[1][i] = {piles[i], 0};
        }

        for (int k=2; k <= nums; k++) {
            for (int i=0; i <= nums - k; i++) {
                int left = i, right = i + k - 1;

                if (dp[k-1][i+1].second + piles[left] > dp[k-1][i].second + piles[right]) {
                    dp[k][i] = {dp[k-1][i+1].second + piles[left], dp[k-1][i+1].first};
                } else {
                    dp[k][i] = {dp[k-1][i].second + piles[right], dp[k-1][i].first};
                }
            }
        }

        if (dp[nums][0].first > dp[nums][0].second) {
            return true;
        } else {
            return false;
        }
    }
};
