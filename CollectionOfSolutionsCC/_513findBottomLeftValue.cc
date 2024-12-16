#include "Solution.h"

int Leetcode501_600::Soltuion::findBottomLeftValue(Leetcode501_600::TreeNode* root)
{
    // 本题最简单的做法就是 BFS 层序遍历
    // 我们按层对 root 树进行遍历，直到达到最后一层，我们返回该层最左边的结点值即可
    queue<TreeNode*> q;
    // 题目保证二叉树中至少有一个结点
    q.push(root);
    int res;
    while(!q.empty())
    {
        int n = q.size();
        for(int i = 0; i < n; ++i)
        {
            TreeNode* cur = q.front();
            q.pop();
            if(i == 0)
            {
                res = cur->val;
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