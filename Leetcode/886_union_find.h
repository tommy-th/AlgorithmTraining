#include "leetcode.h"

class Solution {
public:
    vector<int> acks = vector<int>(2005);
    vector<int> diss = vector<int>(2005);

    int root(int n) {
        if (n < 0) return n;
        if (n != acks[n]) {
            acks[n] = root(acks[n]);
            return acks[n];
        } else {
            return n;
        }
    }

    bool addTree(int a, int b) {
        int ra = root(a);
        int rb = root(b);
        int disra = root(diss[ra]);
        int disrb = root(diss[rb]);

        if (ra == rb || (disra == disrb && disra != -1))
            return false;

        if (disrb >= 0)
            acks[disrb] = ra;

        if (disra >= 0)
            acks[disra] = rb;

        diss[rb] = ra;
        diss[ra] = rb;

        return true;
    }

    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        for (int i=0; i<N; i++) {
            acks[i] = i;
            diss[i] = -1;
        }

        for (auto edge : dislikes) {
            if (not addTree(edge[0], edge[1])) {
                return false;
            }
        }
        return true;
    }
};
