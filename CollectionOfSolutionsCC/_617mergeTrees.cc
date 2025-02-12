#include "Solution.h"

Leetcode601_700::TreeNode* Leetcode601_700::Soltuion::mergeTrees(Leetcode601_700::TreeNode* root1, Leetcode601_700::TreeNode* root2)
{
    // 简单的递归类问题
    // 我们可以直接用解答函数作为递归模版函数
    // 如果 root1 和 root2 均为空结点，那么直接返回 nullptr 即可，合并没有任何结果
    if(!root1 && !root2)
    {
        return nullptr;
    }
    // 否则，如果 root1 或 root2 中有一个为空，那么我们返回另一个结点即可
    if(!root1)
    {
        return root2;
    }
    if(!root2)
    {
        return root1;
    }
    // 其它情况下，root1 和 root2 均非空，那么我们把 root2 的值合并到 root1 中，把 root1 作为合并后的根结点
    root1->val += root2->val;
    // 递归合并 root1 和 root2 的左孩子，作为 root1 的左孩子
    root1->left = mergeTrees(root1->left, root2->left);
    root1->right = mergeTrees(root1->right, root2->right);
    // 合并完成，返回 root1 即可
    return root1;
}