#include "leetcode.h"

class Solution {
    using LL = long long int;
public:
    void palindLoop(LL limit, const function<void(LL)> &f) {
        LL seed = 0;

        while (true) {
            LL p1 = ++seed;
            for (LL div = seed / 10; div; div/=10) {
                p1 = p1*10 + div%10;
            }

            LL p2 = seed;
            for (LL div = seed; div; div/=10) {
                p2 = p2*10 + div%10;
            }

            if (p1 >= limit) break;
            else f(p1);
            if (p2 < limit) f(p2);
        }
    }

    bool isPalind(const string &pp) {
        int i = 0, j = pp.size() - 1;
        while (i < j) {
            if (pp[i] != pp[j]) return false;
            i++, j--;
        }
        return true;
    }

    int superpalindromesInRange(string L, string R) {
       LL l = stoll(L), r = stoll(R);
       LL limit = sqrt(r) + 1;

       int ret = 0;

       auto f = [&](LL p) {
           LL pp = p*p;

           if (pp >= l && isPalind(to_string(pp))) {
               ret++;
           }
       };

       palindLoop(limit, f);

       return ret;
    }
};