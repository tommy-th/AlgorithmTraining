#include "leetcode.h"

class Solution {
public:
    int subarrayBitwiseORs(vector<int>& A) {
        unordered_set<int> res, cur;

        for (int v : A) {
            unordered_set<int> temp = {v};

            for (int prev : cur)
                temp.insert(prev | v);

            for (int newval : temp)
                res.insert(newval);

            cur = move(temp);
        }

        return res.size();
    }
};