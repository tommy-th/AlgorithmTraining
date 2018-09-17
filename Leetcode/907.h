#include "leetcode.h"

class Solution {
using LL = long long int;
public:
    int sumSubarrayMins(vector<int>& A) {
        LL mod = 1e9 + 7;
        vector<pair<int, int>> lens = vector<pair<int, int>>(A.size()+1, {-1, -1});

        stack<int> st;
        for (int i=0; i<A.size(); i++) {
            lens[i].first = i;

            while(not st.empty()) {
                int prev =  st.top();

                if (A[prev] >= A[i]) {
                    lens[i].first = lens[prev].first;
                    lens[prev].second = i-1;
                    st.pop();
                } else {
                    break;
                }
            }

            st.push(i);
        }

        while(not st.empty()) {
            int prev = st.top(); st.pop();
            lens[prev].second = A.size()-1;
        }

        LL ret = 0;
        for (int i=0; i<A.size(); i++) {
            LL lc = i - lens[i].first + 1;
            LL rc = lens[i].second - i + 1;

            ret = (ret + lc*rc*A[i]) % mod;
        }

        return ret;
    }
};