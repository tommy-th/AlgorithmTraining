class Solution {
public:
    int sumSubseqWidths(vector<int> A) {
        sort(A.begin(), A.end());
        long c = 1, res = 0, mod = 1e9 + 7;
        for (int i = 0; i < A.size(); ++i, c = (c << 1) % mod)
            res = (res + A[i] * c - A[A.size() - i - 1] * c) % mod;
        return (res + mod) % mod;
    }
};
