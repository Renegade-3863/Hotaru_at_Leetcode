#include "Solution.h"

Leetcode201_300::TreeNode* Leetcode201_300::Solution::lowestCommonAncestor(Leetcode201_300::TreeNode* root, Leetcode201_300::TreeNode* p, Leetcode201_300::TreeNode* q)
{
    // 可以使用和上一题类似的方案来求解，还是要简化递归的过程，不要重复做无用功
    if(!root)
    {
        return nullptr;
    }
    if(p == root || q == root)
    {
        return root;
    }
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    // 如果p，q在左子树和右子树中都没有最近的公共祖先，那么要么是二者在左子树和右子树中都不存在，要么是二者分立左右两个子树中
    // 这里对应的是二者分立的情况，由于我们在递归返回条件中定义的是，如果根结点是 p 或 q，那么直接返回这个结点作为 "可能" 的公共祖先
    // 因而这里两侧都有结点的情况就代表了结点 p 和 q 分别在根结点的两侧，我们此时直接返回根结点即可
    if(left && right)
    {
        return root;
    }
    // 否则，如果 left 为空，说明 p 和 q 都在右子树中，直接返回 right 即可
    if(!left)
    {
        return right;
    }
    // 同上
    if(!right)
    {
        return left;
    }
    // 否则，两侧都不存在对应结点，我们直接返回 nullptr 即可，代表当前子树中不存在 p 和 q 的公共祖先
    return nullptr;
}