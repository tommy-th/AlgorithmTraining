#include "leetcode.h"

class Solution {
public:
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        vector<vector<int>> g = vector<vector<int>>(graph.size());

        for (int i=0; i<graph.size(); i++) {
            for (int j=0; j<graph[i].size(); j++) {
                if (graph[i][j] == 1 && i != j)
                    g[i].push_back(j);
            }
        }

        int minCount = 10000000;
        int ret = 100000;

        for (int i=0; i<initial.size(); i++) {
            int malCount = 0;
            vector<bool> visits = vector<bool>(graph.size(), false);
            queue<int> q;

            for (int j=0; j<initial.size(); j++) {
                if (i==j) continue;
                q.push(initial[j]);
                visits[initial[j]] = true;
                malCount++;
            }

            while (not q.empty()) {
                int cur = q.front(); q.pop();

                for (int i=0; i<g[cur].size(); i++) {
                    int next = g[cur][i];

                    if (not visits[next]) {
                        q.push(next);
                        malCount++;
                        visits[next] = true;
                    }
                }
            }

            if (malCount <= minCount && initial[i] < ret) {
                minCount = malCount;
                ret = initial[i];
            }
        }

        return ret;
    }
};