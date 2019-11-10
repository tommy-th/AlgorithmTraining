#include "leetcode.h"

class Solution {
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        int N = words.size();
        int MAX_CASES = std::pow(2, N);

        int SCORE_IDX = 26;
        int VISIT_IDX = 27;

        auto wordNums = vector<vector<int>>(N, vector<int>(26, 0));
        for (int i=0; i<N; i++) {
            const auto &word = words[i];
            for (const char c : word) {
                wordNums[i][c - 'a'] += 1;
            }
        }

        auto dp = vector<vector<int>>(MAX_CASES+1,vector<int>(30, 0));

        queue<int> q;
        q.push(0);
        dp[0][VISIT_IDX] = 1;
        for (const char c : letters) {
            dp[0][c - 'a'] += 1;
        }

        while (not q.empty()) {
            int cur = q.front(); q.pop();

            for (int i=0; i<N; i++) {
                if ((cur & (1<<i)) == 0) {
                    int next = cur | (1<<i);

                    if (dp[next][VISIT_IDX] == 0) {
                        dp[next][VISIT_IDX] = 1;
                        dp[next][SCORE_IDX] = dp[cur][SCORE_IDX];

                        for (int c = 0; c < 26; c++) {
                            dp[next][c] = dp[cur][c] - wordNums[i][c];
                            dp[next][SCORE_IDX] += (score[c] * wordNums[i][c]);

                            if (dp[next][c] < 0) {
                                dp[next][VISIT_IDX] = -1;
                                break;
                            }
                        }

                        if (dp[next][VISIT_IDX] == 1) {
                            q.push(next);
                        }
                    }
                }
            }
        }

        int ret = 0;
        for (int i=0; i<MAX_CASES+1; i++) {
            if (dp[i][VISIT_IDX] == 1) {
                ret = max(ret, dp[i][SCORE_IDX]);
            }
        }

        return ret;
    }
};