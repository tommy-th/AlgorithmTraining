#include "leetcode.h"

class Solution {
public:
    bool hasGroupsSizeX(vector<int>& deck) {
        int res = 0;
        unordered_map<int, int> counts;
        for (auto card : deck) counts[card]++;
        for (auto el : counts) res = gcd(el.second, res);

        return res >= 2;
    }
};