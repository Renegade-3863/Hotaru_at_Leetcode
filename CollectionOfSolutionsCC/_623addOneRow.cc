#include "Solution.h"

Leetcode601_700::TreeNode* Leetcode601_700::Soltuion::addOneRow(Leetcode601_700::TreeNode* root, int val, int depth)
{
    // 首先分析一下这题的要求
    // 要求对每个深度为 depth 的非空树结点 cur 进行修改，把 cur 的左右孩子修改成一对新的，值为 val 的新树结点
    // 原 cur 的左子树变成现在 cur 左孩子的左子树，原 cur 的右子树变成现在 cur 右孩子的右子树
    // 如果 depth == 1，那么我们需要新建一个值为 val 的新树根 newRoot，而 root 作为 newRoot 的左子树
    // 明确了需求，我们就可以用递归方法来模拟一下这个过程了
    // 首先，如果 depth == 1，那么需要特殊处理
    if(depth == 1)
    {
        TreeNode* newRoot = new TreeNode(val);
        newRoot->left = root;
        return newRoot;
    }
    // 定义一个 dfs 函数，用于执行上面提到的一般情况
    function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int d) -> void
    {
        // 结束条件定义到后面，不在这里单独定义了
        if(d == depth-1)
        {
            // d == depth-1，说明这既是我们要添加结点的行，也是我们的结束条件
            TreeNode* newLeft = new TreeNode(val);
            newLeft->left = node->left;
            node->left = newLeft;
            TreeNode* newRight = new TreeNode(val);
            newRight->right = node->right;
            node->right = newRight;
            // 这一枝的当前行已经处理完成，我们返回，作为结束条件
            return;
        }
        // 否则，我们往左右递归，处理左右子树
        if(node->left)
        {
            dfs(node->left, d+1);
        }
        if(node->right)
        {
            dfs(node->right, d+1);
        }
    };
    dfs(root, 1);
    return root;
}