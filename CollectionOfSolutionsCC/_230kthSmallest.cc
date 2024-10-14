#include "Solution.h"

int kthSmallest(Leetcode201_300::TreeNode* root, int k)
{
    // 本题如果是一道朴素二叉树的题目，那么显然我们很难求解，不过既然是一棵 BST，那么我们显然有一种简单暴力的方案：中序遍历一次这棵树，返回升序序列中第 k 个元素
    // 这里只给出迭代版本的实现方案，递归相信是个人都会写了。。。
    // 注意，题目限定了树中一定有至少一个结点，所以这里不用检查树是否为空了
    // if(!root)
    // {
    //     return 0;
    // }
    stack<TreeNode*> stk;
    TreeNode* cur = root;
    int cnt = 0;
    while(cur || !stk.empty())
    {
        if(cur)
        {
            stk.push(cur);
            cur = cur->left;
        }
        else
        {
            cur = stk.top();
            stk.pop();
            if(++cnt == k)
            {
                return cur->val;
            }
            cur = cur->right;
        }
    }
    // 理论上不会执行到这一行
    return 0;
}