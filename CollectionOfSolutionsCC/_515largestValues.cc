#include "Solution.h"

vector<int> Leetcode501_600::Soltuion::largestValues(Leetcode501_600::TreeNode* root)
{
    // 依然是简单的层序遍历
    if(!root)
    {
        return {};
    }
    // 使用一个队列即可实现
    vector<int> res;
    queue<TreeNode*> q;   
    q.push(root);
    while(!q.empty())
    {
        int n = q.size();
        // 记录当前层的最大值
        int maximum = INT_MIN;
        for(int i = 0; i < n; ++i)
        {
            TreeNode* cur = q.front();
            q.pop();
            maximum = max(maximum, cur->val);
            if(cur->left)
            {
                q.push(cur->left);
            }
            if(cur->right)
            {
                q.push(cur->right);
            }
        }
        res.push_back(maximum);
    }
    return res;
}