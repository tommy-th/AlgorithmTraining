#include "leetcode.h"

class Solution {
public:
    vector<string> wordSubsets(vector<string>& A, vector<string>& B) {
        vector<vector<int>> aAlphaSet = vector<vector<int>>(A.size(), vector<int>(27, 0));
        vector<vector<int>> bAlphaSet = vector<vector<int>>(B.size(), vector<int>(27, 0));
        vector<int> bAlphaResult = vector<int>(27, 0);

        for (int i=0; i<A.size(); i++){
            string& a = A[i];
            for (int j=0; j<a.size(); j++) {
                aAlphaSet[i][a[j]-'a']++;
            }
        }

        for (int i=0; i<B.size(); i++){
            string& b = B[i];
            for (int j=0; j<b.size(); j++)
                bAlphaSet[i][b[j]-'a']++;
        }

        for (int i=0; i<B.size(); i++) {
            for (int j=0; j<27; j++)
                bAlphaResult[j] = max(bAlphaResult[j], bAlphaSet[i][j]);
        }

        vector<string> ret;
        for (int i=0; i<A.size(); i++) {
            bool ch = true;
            for (int j=0; j<27; j++) {
                if (aAlphaSet[i][j] < bAlphaResult[j]) {
                    ch = false;
                    break;
                }
            }
            if (ch)
                ret.push_back(A[i]);
        }

        return ret;
    }
};