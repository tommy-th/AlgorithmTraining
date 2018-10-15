#include "leetcode.h"

class Solution {
    using LL = long long int;
    constexpr static LL mod = 1e9 + 7;

public:
    int threeSumMulti(vector<int>& A, int target) {
        vector<LL> firsts = vector<LL>(101, 0);
        vector<LL> seconds = vector<LL>(201, 0);
        LL results = 0;

        for (int a : A) {
            int last = target - a;

            if (last >= 0 && last <= 200) {
                if (seconds[last] > 0)
                    results = (results + seconds[last]) % mod;
            }

            for (int i=0; i<=100; i++) {
                seconds[i+a] += firsts[i];
            }

            firsts[a]++;
        }


        return results;
    }
};