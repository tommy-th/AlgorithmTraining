#include "leetcode.h"

class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int M, int N) {
        vector<int> dp(N, -1);
        vector<vector<pair<int, int>>> froms(N);

        for (int i = 0; i < edges.size(); i++) {
            int a = edges[i][0];
            int b = edges[i][1];
            int len = edges[i][2];

            froms[a].push_back({b, len});
            froms[b].push_back({a, len});
        }

        vector<bool> hash(N, false);
        queue<int> bfs;
        bfs.push(0);
        dp[0] = M;

        while (not bfs.empty()) {
            int node = bfs.front(); bfs.pop();
            int moves = dp[node];

            hash[node] = false;

            for (auto from : froms[node]) {
                int next = from.first;
                int len = from.second;

                if (moves - len - 1 > dp[next]) {
                    dp[next] = moves - len - 1;

                    if (not hash[next]) {
                        hash[next] = true;
                        bfs.push(next);
                    }
                }
            }
        }

        int result = 0;
        for (int i=0; i < edges.size(); i++) {
            int sum = max(dp[edges[i][0]], 0) + max(dp[edges[i][1]], 0);
            result += min(sum, edges[i][2]);
        }

        for (int i=0; i < N; i++)
            if (dp[i] >= 0)
                result++;

        return result;
    }
};
