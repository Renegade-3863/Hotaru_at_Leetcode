#include "Solution.h"

Leetcode601_700::TreeNode* Leetcode601_700::Soltuion::searchBST(Leetcode601_700::TreeNode* root, int val)
{
    // 数据结构最简单的一类模版题了。。
    // 跟上一题比起来一个天堂一个地府。。
    // 直接 dfs 秒了！
    if(!root)
    {
        return nullptr;
    }
    // 检查 root->val 是否等于 val
    if(root->val == val)
    {
        return root;
    }
    // 否则，根据 root->val 和 val 的大小关系，决定是要往左检查还是往右检查
    if(root->val > val)
    {
        // 结果可能在左子树，往左检查
        return searchBST(root->left, val);
    }
    // 否则，结果可能在右子树，往右检查
    return searchBST(root->right, val);
}