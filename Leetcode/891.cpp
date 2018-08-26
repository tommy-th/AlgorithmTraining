class Solution {
using LL = long long int;
public:
    int sumSubseqWidths(vector<int>& A) {
        LL ret = 0;
        LL exp = 1;
        LL mod = 1e9 + 7;

        sort(A.begin(), A.end());

        int i = 0, j = A.size()-1;
        LL left = 0, right = 0;

        while (i < j) {
            right += A[j];
            left += A[i];

            LL cases = (right - left) * exp;

            ret = (ret + cases) % mod;
            exp = (exp * 2) % mod;
            j--, i++;
        }

        if (A.size() % 2 == 0) {
            j++, i--;
        }

        while (i > 0 && j < A.size() - 1) {
            right -= A[j];
            left -= A[i];

            LL cases = (right - left) * exp;

            ret = (ret + cases) % mod;
            exp = (exp * 2) % mod;
            j++, i--;
        }

        return ret;
    }
};
