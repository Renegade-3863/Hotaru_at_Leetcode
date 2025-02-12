#include "Solution.h"

int Leetcode501_600::Soltuion::getMinimumDifference(Leetcode501_600::TreeNode* root)
{
    // 简单的 BST 遍历题，我们直接用最优的 Morris 遍历即可
    // 考虑利用 BST 本身的性质来存储遍历时缺失的信息
    TreeNode* cur = root;
    // 定义一个结果值 res，初始为一个很大的值
    int res = INT_MAX;
    // 记录 "上一个访问的结点值"，用 -1 代表 "还没访问过结点"
    int pre = -1;
    while(cur)
    {
        // 两种情况，cur 有左孩子，和 cur 没有左孩子
        if(cur->left)
        {
            // 我们要做的中序遍历，所以先往左走
            // 不过走之前，需要记录一个 predecessor 关系，用于后面访问回来的时候
            TreeNode* predecessor = cur->left;
            // 两种情况结束循环
            // 1. 到达了最后一个结点
            // 2. 这个前驱-后继关系已经被记录过了
            while(predecessor->right && predecessor->right != cur)
            {
                predecessor = predecessor->right;
            }
            // 讨论结束循环的条件
            if(predecessor->right == cur)
            {
                // 记录过了，说明这个结点的左子树已经被访问过了，那么我们直接访问它就行
                // 只有 pre 有信息的时候，我们才更新结果
                if(pre != -1)
                {
                    res = min(res, abs(cur->val-pre));
                }
                // 更新 pre 值
                pre = cur->val;
                // 别忘了，重置结点信息
                predecessor->right = nullptr;
                // 访问完成，往右走
                cur = cur->right;
            }
            // 否则，左子树还没访问过，那么我们记录这个前驱-后继关系
            else
            {
                predecessor->right = cur;
                // 往左走，不进行访问
                cur = cur->left;
            }
        }
        // 否则，我们访问当前结点 cur，之后往右走，记录一个 "后继结点" 信息
        else
        {
            if(pre != -1)
            {
                res = min(res, abs(pre-cur->val));
            }
            pre = cur->val;
            cur = cur->right;
        }
    }
    return res;
}