#include "Solution.h"

vector<int> Leetcode101_200::Solution::rightSideView(Leetcode101_200::TreeNode* root)
{
    // 我们要做的事情其实很简单，就是对整棵树进行一轮层序遍历即可
    // 对于每一层，需要输出的是该层最右侧的结点
    queue<TreeNode*> q;
    // 空树返回空集合即可
    if(!root)
    {
        return {};
    }
    q.push(root);
    vector<int> res;
    while(!q.empty())
    {
        int n = q.size();
        for(int i = 0; i < n; ++i)
        {
            TreeNode* cur = q.front();
            q.pop();
            if(i == n-1)
            {
                res.push_back(cur->val);
            }
            if(cur->left)
            {
                q.push(cur->left);
            }
            if(cur->right)
            {
                q.push(cur->right);
            }
        }
    }
    return res;
}