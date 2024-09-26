#include "Solution.h"

vector<vector<int>> levelOrder(Leetcode101_200::TreeNode* root)
{
    // 要求对二叉树做层序遍历，也是一道二叉树最最基本的题目了
    // 可以简单地使用 BFS，也就是队列实现
    queue<TreeNode*> q;
    if(!root)
    {
        return {};
    }
    // 存储全局结果的数组
    vector<vector<int>> res;
    // 标记当前添加的元素所在的层号
    int idx = 0;
    q.push(root);
    while(!q.empty())
    {
        // 记录当前层的结点个数
        int n = q.size();
        // 按层弹出结点并添加到 res 中新的一行中
        // 这里一次性分配大小正好的空间，避免后面一次次调用 push_back 引起额外的开销
        res.push_back(vector<int>(n, 0));
        for(int i = 0; i < n; ++i)
        {
            TreeNode* cur = q.front();
            q.pop();
            res[idx][i] = cur->val;
            // 使用弹出来的这个新结点添加下一行中它的两个孩子结点
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
    return res;
}