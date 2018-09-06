#include "leetcode.h"

class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int N = edges.size();
        vector<int> parents = vector<int>(N+1, 0);

        function<int(int)> getParent = [&](int n){
            if (n == parents[n]) return n;
            parents[n] = getParent(parents[n]);
            return parents[n];
        };

        for (int i = edges.size() - 1; i >= 0; i--) {
            bool success = true;

            for (int k=1; k <= N; k++)
                parents[k] = k;

            for (int j=0; j<edges.size(); j++) {
                if (i==j) continue;
                int from = edges[j][0], to = edges[j][1];

                if (getParent(to) != to || getParent(from) == to) {
                    success = false;
                    break;
                }
                parents[to] = getParent(from);
            }

            if (success)
                return edges[i];
        }
    }
};