#include "leetcode.h"

class Solution {
public:
    int gcd(int a, int b){
          while(b!=0){
                int r = a%b;
                a= b;
                b= r;
          }
          return a;
    }

    int lcm(int a, int b){
        return a * b / gcd(a,b);
    }

    int nthMagicalNumber(int N, int A, int B) {
        long long int MOD = 1000000007;
        int lcmab = lcm(A, B);

        int Anums = lcmab / A - 1;
        int Bnums = lcmab / B - 1;

        int cycle = Anums + Bnums + 1;

        int cycleNum = N / cycle;
        int restNum = N % cycle;

        long long int result = lcmab * cycleNum;
        result %= MOD;

        long long int asums = 0;
        long long int bsums = 0;
        for (int i=0; i<restNum; i++) {
            if (asums + A < bsums + B) {
                asums += A;
            } else {
                bsums += B;
            }
        }

        result += std::max(asums, bsums);
        result %= MOD;

        return result;
    }
};
