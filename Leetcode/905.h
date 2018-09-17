#include "leetcode.h"

class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& A) {
        vector<int> odds;
        vector<int> evens;

        for (int a: A) {
            if (a%2==0)
                evens.push_back(a);
            else
                odds.push_back(a);
        }
        for (int o: odds) {
            evens.push_back(o);
        }
        return evens;
    }
};