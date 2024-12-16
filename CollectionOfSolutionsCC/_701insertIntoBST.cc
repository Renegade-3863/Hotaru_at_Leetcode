#include "Solution.h"

Leetcode701_800::TreeNode* Leetcode701_800::Soltuion::insertIntoBST(Leetcode701_800::TreeNode* root, int val)
{
    // 简单题，往一棵 BST 中插入一个新值，不考虑平衡性的话，直接使用二分查找即可找到对应值，或者找到一个可以插入新值的叶子结点
    // cur 记录当前结点，pre 记录 cur 的父结点，一开始 pre 为 nullptr
    TreeNode* cur = root, * pre = nullptr;
    // 当遇到一个可行的空位时退出，此时 pre 就是这个空位的父结点
    while(cur)
    {
        // 更新 pre 值
        pre = cur;
        if(cur->val > val)
        {
            // 当前结点值更大，val 应该插到左子树中
            cur = cur->left;
        }
        else if(cur->val == val)
        {
            // 当前结点值等于要插入的值，我们不能重复插入
            return root;
        }
        else
        {
            // 当前结点值更小，val 应该插到右子树中
            cur = cur->right;
        }
    }
    // 循环结束，有两种可能
    // 1. pre == nullptr，说明原树是空的
    // 此时我们需要新建根结点，设置好值并返回
    if(!pre)
    {
        return new TreeNode(val);
    }
    // 2. pre != nullptr，此时我们只需要把 val 设到 pre 为空的任意一个孩子即可
    if(pre->val)
    {
        pre->left = new TreeNode(val);
        return root;
    }
    pre->right = new TreeNode(val);
    return root;
}