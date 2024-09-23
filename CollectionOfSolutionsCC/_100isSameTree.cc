#include "Solution.h"

bool Leetcode1_100::Solution::isSameTree(Leetcode1_100::TreeNode* p, Leetcode1_100::TreeNode* q)
{
    // 要求判断两棵树是否相同，比较常规的 DFS 类二叉树问题
    // 如果一棵以 p 为根结点的子树和 一棵以 q 为根结点的子树相等，那么必然有：
    // 1. p == nullptr && q == nullptr
    // 2. p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right)
    // 之间写出 DFS 代码即可
    if(!p || !q)
    {
        return p == q;
    }
    return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}