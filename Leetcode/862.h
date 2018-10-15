#include "leetcode.h"

class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
        vector<int> sums = vector<int>(A.size()+1, 0);
        list<int> prevs;

        int ret = A.size() + 1;
        for (int i=0; i<A.size(); i++) {
            sums[i+1] = sums[i] + A[i];

            if (A[i] >= K) return 1;

            while (not prevs.empty() && sums[i+1] - sums[prevs.front()] >= K) {
                ret = min(i - prevs.front() + 1, ret);
                prevs.pop_front();
            }

            while (not prevs.empty() && sums[i] <= sums[prevs.back()]) {
                prevs.pop_back();
            }

            prevs.push_back(i);
        }

        return ret == A.size() + 1 ? -1 : ret;
    }
};