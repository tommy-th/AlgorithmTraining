#include "leetcode.h"

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* increasingBST(TreeNode* root) {
        TreeNode* ret = nullptr;
        TreeNode* retcur = nullptr;

        function<void(TreeNode*)> search = [&](TreeNode* cur){
            if (cur->left)
                search(cur->left);

            if (ret == nullptr) {
                ret = new TreeNode(cur->val);
                retcur = ret;
            } else {
                retcur->right = new TreeNode(cur->val);
                retcur = retcur->right;
            }

            if (cur->right)
                search(cur->right);
        };

        search(root);

        return ret;
    }
};