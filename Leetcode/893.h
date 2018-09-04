#include "leetcode.h"

class Solution {
public:
    int numSpecialEquivGroups(vector<string>& A) {
        unordered_set<string> groups;

        for (const auto v : A) {
            vector<char> odd;
            vector<char> even;

            for (int i=0; i<v.size(); i++) {
                if (i%2==0) odd.push_back(v[i]);
                else even.push_back(v[i]);
            }

            sort(odd.begin(), odd.end());
            sort(even.begin(), even.end());

            string ret =
                string(odd.begin(), odd.end()) + string(even.begin(), even.end());

            groups.insert(ret);
        }

        return groups.size();
    }
};
