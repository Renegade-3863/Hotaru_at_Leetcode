#include "Solution.h"

int Leetcode501_600::Soltuion::findTilt(Leetcode501_600::TreeNode* root)
{
    // 简单的二叉树遍历问题
    // 我们按常规的后序遍历方法对每一个结点进行访问即可
    unordered_map<TreeNode*, int> memo;
    // 可以用 Morris 遍历，但是 Morris 的后序遍历不是很好写，我们还是用栈的放式来完成
    stack<TreeNode*> stk;
    if(!root)
    {
        return 0;
    }
    TreeNode* cur = root, *pre = nullptr;
    // res 记录最终结果
    int res = 0;
    while(cur || !stk.empty())
    {
        if(cur)
        {
            // 先访问左子树
            stk.push(cur);
            cur = cur->left;
        }
        // cur 为空
        else
        {
            // 取出一个左子树已经访问完成的根结点
            cur = stk.top();
            // 检查右子树是否为空，或者是否已经访问完成
            if(!cur->right || cur->right == pre)
            {
                // 右子树已经访问完成，我们可以到哈希表中查找左右子树的 "坡度值"，并计算差值，记录到哈希表中
                memo[cur] = abs((cur->left ? cur->left->val : 0)-(cur->right ? cur->right->val : 0));
                cur->val += (cur->left ? cur->left->val : 0) + (cur->right ? cur->right->val : 0);
                res += memo[cur];
                pre = cur;
                // 别忘了把 cur 置空
                cur = nullptr;
                stk.pop();
            }
            else
            {
                cur = cur->right;
            }
        }
    }
    return res;
}