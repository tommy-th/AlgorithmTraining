#include "leetcode.h"

class Solution {
public:
    int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {
        int n = group.size();
        std::unordered_map<int, int> m;

        for (int idx = 0; idx < n; idx++) {
            vector<std::pair<int, int>> v;

            v.push_back({group[idx] * 1000 + profit[idx], 1});
            for (auto hash : m) {
                int people = hash.first / 1000;
                int gain = hash.first % 1000;
                int cases = hash.second;

                int nextPeople = people + group[idx];
                if (nextPeople > G) continue;
                int nextGain = gain + profit[idx];
                if (nextGain > P) nextGain = P;

                int nextKey = nextPeople * 1000 + nextGain;

                v.push_back({nextKey, cases});
            }

            for (auto newCase : v) {
                auto iter = m.find(newCase.first);
                if (iter != m.end()) {
                    m[newCase.first] = (newCase.second + iter->second) % mod;
                } else {
                    m[newCase.first] = newCase.second;
                }
            }
        }

        int result = 0;
        for (auto hash : m) {
            int people = hash.first / 1000;
            int gain = hash.first % 1000;
            int cases = hash.second;

            if (people <= G && gain >= P)
                result = (result + cases) % mod;
        }

        return result;
    }

private:
    const long long int mod = 1e9+7;
};
