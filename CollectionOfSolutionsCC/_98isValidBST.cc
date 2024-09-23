#include "Solution.h"

bool Leetcode1_100::Solution::isValidBST(Leetcode1_100::TreeNode* root)
{
    // 要验证一棵二叉树是不是二叉搜索树，我们只需要对其进行中序遍历，检查是不是满足每一个遍历到的值都比它的前驱结点值大即可
    // 标记当前遍历到的是不是首个结点
    bool first = true;
    int pre = -1;
    stack<TreeNode*> stk;
    TreeNode* cur = root;
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
            if(!first && cur->val <= pre)
            {
                return false;
            }
            pre = cur->val;
            first = false;
            cur = cur->right;
        }
    }
    return true;
}