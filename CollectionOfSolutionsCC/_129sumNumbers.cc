#include "Solution.h"

int Leetcode101_200::sumNumbers(Leetcode101_200::TreeNode* root)
{
    // 要求我们计算从树的根结点到其所有叶子结点到路径形成的数字之和
    // 直观上看，第一感觉其实是回溯，虽然特征不是很明显，不过还是有 "所有情况" 这一特性在
    // 考虑使用传统的回溯模版进行求解
    // 如果是一棵空树，则可以直接返回0作为结果
    if(!root)
    {
        return 0;
    }
    // 全局的结果值
    int res = 0;
    // 路径值，用于记录每条路径上的数字
    int path = 0;
    // cur 记录的是当前在访问的结点
    function<void(TreeNode*)> backtrack = [&](TreeNode* cur)
    {
        // 如果这是一个叶子结点，我们就把记录下来的路径数添加到全局的结果中
        if(!cur->left && !cur->right)
        {
            res += path;
            return;
        }
        // 否则，不是一个叶子结点，我们尝试往两个方向进行深入
        // 先尝试把左孩子的值添加到 path 中
        if(cur->left)
        {
            path = path*10+cur->left->val;
            backtrack(cur->left);
            path /= 10;
        }
        if(cur->right)
        {
            path = path*10+cur->right->val;
            backtrack(cur->right);
            path /= 10;
        }
    };
    // 进行函数调用即可，注意需要先给 path 添加 root 结点的值，由于我们使用的是 "先添加再深入" 的策略
    path = root->val;
    backtrack(root);
    return res;
}