#include "Solution.h"

vector<vector<int>> Leetcode101_200::Solution::levelOrderBottom(Leetcode101_200::TreeNode*)
{
    if(!root)
    {
        return {};
    }
    // 不是很明白本题能有什么高端解法，先搞一遍层序遍历，之后把遍历的结果按行反转
    queue<TreeNode*> q;
    vector<vector<int>> res;
    q.push(root);
    int idx = 0;
    while(!q.empty())
    {
        int n = q.size();
        res.push_back(vector<int>(n, 0));
        for(int i = 0; i < n; ++i)
        {
            TreeNode* cur = q.front();
            q.pop();
            res[idx][i] = cur->val;
            if(cur->left)
            {
                q.push(cur->left);
            }
            if(cur->right)
            {
                q.push(cur->right);
            }
        }
        ++idx;
    }
    reverse(res.begin(), res.end());
    return res;
}