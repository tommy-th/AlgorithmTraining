/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        TreeNode* root = new TreeNode(pre[0]);
        TreeNode* cur = root;
        int j = 0;

        stack<TreeNode*> st;
        st.push(root);

        for (int i=1; i < pre.size(); i++) {
            if (cur->left == nullptr) {
                cur->left = new TreeNode(pre[i]);
                cur = cur->left;
                st.push(cur);
            } else if (cur->right == nullptr) {
                cur->right = new TreeNode(pre[i]);
                cur = cur->right;
                st.push(cur);
            }

            while (j < post.size() && cur->val == post[j]) {
                st.pop();
                if (st.empty())
                    break;
                cur = st.top();
                j++;
            }
        }

        return root;
    }
};
