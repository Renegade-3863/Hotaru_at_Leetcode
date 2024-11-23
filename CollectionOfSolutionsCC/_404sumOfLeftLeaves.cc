#include "Solution.h"

int Leetcode401_500::Solution::sumOfLeftLeaves(Leetcode401_500::TreeNode* root)
{
    // 很简单的广搜题，我们只需要用广度优先算法遍历一次整棵树即可
    // 每次往下一层深入的时候，我们都需要检查一下，两个孩子结点是不是叶子结点
    // 如果左孩子是一个叶子结点，那么我们把这个叶子结点添加到结果值中
    // 其它情况下，如果不是叶子结点，我们才把这个结点添加到队列中
    if(!root)
    {
        return 0;
    }
    int res = 0;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty())
    {
        TreeNode* cur = q.front();
        if(cur->left)
        {
            // 进一步检查这个左孩子是不是叶子
            if(!cur->left->left && !cur->left->right)
            {
                res += cur->left->val;
            }
            //  不是叶子结点，压入队列中，等待下一轮检查
            else
            {
                q.push(cur->left);
            }
        }
        if(cur->right)
        {
            if(cur->right->left || cur->right->right)
            {
                q.push(cur->right);
            }
        }
        q.pop();
    }
    return res;
}