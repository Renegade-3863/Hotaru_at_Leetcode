#include "Solution.h"

Leetcode501_600::TreeNode* Leetcode501_600::Soltuion::convertBST(Leetcode501_600::TreeNode* root)
{
    // 熟悉 BST 特性的，这道题很容易看出来，就是反向的中序遍历而已
    // 我们用空间最优的 Morris 遍历即可找出结果
    TreeNode* cur = root;
    TreeNode* pre = nullptr;
    while(cur)
    {
        // 如果 cur 的右孩子非空，那么我们先往右走
        // 不过在走之前，我们还需要确认右子树没有访问过
        if(cur->right)
        {
            // 反向遍历，我们此时需要检查的是后继关系，做一下修改即可
            TreeNode* successor = cur->right;
            while(successor->left && successor->left != cur)
            {
                successor = successor->left;
            }
            // 根据 cur 的内容，我们判断是否已经访问过了右子树
            if(!successor->left)
            {
                // 没访问过，我们记录后继关系，往右走
                successor->left = cur;
                cur = cur->right;
            }
            else
            {
                // 否则，右子树已经访问过了，那么我们可以对 cur 进行访问即可
                cur->val = pre->val+cur->val;
                // 修改 pre 的内容
                pre = cur;
                // 别忘了把树复原
                successor->left = nullptr;
                // 访问结束，我们往左走即可
                cur = cur->left;
            }
        }
        else
        {
            // cur->right 为空，那么我们可以直接对 cur 进行访问，然后往左走即可
            // 别忘了记录 pre
            if(pre)
            {
                cur->val += pre->val;
            }
            pre = cur;
            cur = cur->left;
        }
    }
    // root 这棵树就已经修改完了，返回作为答案即可
    return root;
}