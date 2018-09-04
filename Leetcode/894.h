#include "leetcode.h"

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<TreeNode*> allPossibleFBT(int N) {
        vector<TreeNode*> ret;

        if (N < 1) return ret;

        N--;

        if (N == 0) {
            ret.push_back(new TreeNode(0));
            return ret;
        }

        for (int i=1; i<=N; i+=2) {
            vector<TreeNode*> leftchilds = allPossibleFBT(N-i);
            vector<TreeNode*> rightchilds = allPossibleFBT(i);

            for (TreeNode* leftchild : leftchilds) {
                for (TreeNode* rightchild : rightchilds) {
                    TreeNode* temp = new TreeNode(0);
                    temp->left = leftchild;
                    temp->right = rightchild;
                    ret.push_back(temp);
                }
            }
        }

        return ret;
    }
};
