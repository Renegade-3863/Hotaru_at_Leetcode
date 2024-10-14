#include "Solution.h"

Leetcode201_300::TreeNode* invertTree(Leetcode201_300::TreeNode* root)
{
    // 简单题简单做，二叉树类的题目基本都是递归方法
    // 我们考虑利用母函数进行递归
    // 定义递归的结束条件
    // 如果要翻转的二叉树是空的，那么直接返回空结点即可
    if(!root)
    {
        return nullptr;
    }
    // 递归步骤
    // 观察到，要翻转这课二叉树，我们不需要对根结点进行任何操作，只需要先翻转它的两棵子树，之后再交换根结点的左右孩子即可
    TreeNode* leftRev = invertTree(root->left);
    TreeNode* rightRev = invertTree(root->right);
    root->left = rightRev; root->right = leftRev;
    return root;
}