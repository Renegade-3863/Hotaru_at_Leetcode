#include "Solution.h"

Leetcode601_700::TreeNode* Leetcode601_700::Soltuion::trimBST(Leetcode601_700::TreeNode* root, int low, int high)
{
    // 依然要记住一句话：二叉树/任何树类型的问题，DFS/递归总是很有效的解法/切入点
    // 本题我们可以定义这样一个子问题：
    // TreeNode* dfs(node) -> 对以 node 为根结点的子树进行题目要求的修剪操作，返回值为修建后，这个子树的新根结点
    // 不用引入 low 和 high 参数，因为它们在全程都是不变的
    function<TreeNode*(TreeNode*)> dfs = [&](TreeNode* node) -> TreeNode*
    {
        // 定义基本情况：
        // 如果 node 为 nullptr
        // 那么我们直接返回 nullptr 即可
        if(!node)
        {
            return nullptr;
        }
        // 其它情况下，我们考虑先检查 node 的值是否在 [low, high] 区间中
        // 如果不在，那么我们需要对它进行 "裁剪操作"
        if(node->val < low)
        {
            // 如果 node->val 在 (-inf, low) 中，那么 node 以及它的左子树都可以直接剪掉了
            // 我们只需要返回 dfs(node->right) 即可，因为 node->right 这棵子树还有可能存在可行的结点
            return dfs(node->right);
        }
        if(node->val > high)
        {
            // 道理类似，此时我们不用管 node 以及 node->right 整棵子树了
            return dfs(node->left);
        }
        // 否则，node 可以保留，那么我们递归处理 node->left 和 node->right 两棵子树即可
        node->left = dfs(node->left);
        node->right = dfs(node->right);
        // 修剪完成，返回 node 即可
        return node;
    };
    return dfs(root);
}