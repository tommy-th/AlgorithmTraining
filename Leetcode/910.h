#include "leetcode.h"

class Solution {
public:
    int smallestRangeII(vector<int>& A, int K) {
        function<int(int, int, int)> bsearch = [&](int s, int e, int tmax) {
            if (s > e) return -1;
            int mid = (s + e) / 2;

            if (A[mid] + K > tmax) {
                int tmp = bsearch(s, mid-1, tmax);
                if (tmp >= 0) return tmp;
                else return mid;
            } else {
                int tmp = bsearch(mid+1, e, tmax);
                if (tmp >= 0) return tmp;
                else return -1;
            }
        };

        sort(A.begin(), A.end());
        int ret = A[A.size()-1] - A[0];

        for (int i=0; i < A.size(); i++) {
            int tmax = A[i] + K;
            int tmin = A[0] + K;
            if (tmax < A[A.size()-1] - K)
                continue;

            int minidx = bsearch(0, A.size()-1, tmax);
            if (minidx > 0)
                tmin = min(tmin, A[minidx] - K);

            ret = min(ret, tmax - tmin);
        }

        int tmax = A[A.size()-1] - K;
        int tmin = A[0] + K;
        int minidx = bsearch(0, A.size()-1, tmax);

        if (minidx >= 0)
            tmin = min(tmin, A[minidx] - K);

        ret = min(ret, tmax - tmin);

        return ret;
    }
};