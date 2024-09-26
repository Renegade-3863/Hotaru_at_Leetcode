#include "Solution.h"

bool Leetcode101_200::Solution::hasPathSum(Leetcode101_200::TreeNode* root, int targetSum)
{
    // 本题较为简单，固定了路径的一端，要求找出这样的路径和等于 targetSum 的路径
    // 本质上还是递归
    // 回调函数同样可以使用这个大函数本身
    // 我们要检查是否存在从当前根结点到它所表示的二叉树的一个叶结点的路径和等于 targetSum
    // 那么就要检查它的两个孩子结点代表的子树中是否存在以它们为根结点，路径和为 targetSum-root->val 的路径
    // 按照这个思路写递归代码即可
    // 如果是空树，就不存在这样的路径(没有结点，哪来的路径)
    if(!root)
    {
        return false;
    }
    // 如果当前结点是一个叶子结点，那么就检查剩下的 targetSum 够不够这一个结点顶替
    if(!root->left && !root->right)
    {
        return root->val == targetSum;
    }
    // 否则，从 targetSum 中减去 root->val，之后递归查找两棵子树
    bool leftContains = hasPathSum(root->left, targetSum-root->val);
    bool rightContains = hasPathSum(root->right, targetSum-root->val);
    return leftContains || rightContains;
}