#include "Solution.h"

int Leetcode601_700::Soltuion::findSecondMinimumValue(Leetcode601_700::TreeNode* root)
{   
    // 不要想太复杂
    // 分析一下这棵树的性质：
    // 从上往下，一定是逐步递增的，或者是值维持不变的
    // 换句话说，每一条树中的路径，都一定是一个连续非递减数列
    // 从这个角度来说，我们可以明确一种最简单的 dfs 方法
    // 探索树的每一条可能的从根结点到达叶子结点的路径
    // 我们在探查任何一条路径的时候，每次遇到第一个递增的 pulse 关系，就记录增加后的那个值作为备选答案，
    // 最后实际上，我们只需要比较两个值即可得到答案
    int res = -1;
    function<void(TreeNode*)> dfs = [&](TreeNode* node)
    {
        if(!node)
        {
            return;
        }
        // 题目限定了，每个树结点，要么有两个孩子，要么没有孩子
        // 我们分类讨论一下即可
        if(!node->left && !node->right)
        {
            // 没有孩子，那么只能返回
            return;
        }
        // 有两个孩子
        // 那么我们检查是否有 pulse
        // 如果有 pulse 了，那么我们尝试更新 res，并返回
        if(node->left->val > node->val)
        {
            res = res == -1 ? node->left->val : min(node->left->val, res);
            dfs(node->right);
            return;
        }
        else if(node->right->val > node->val)
        {
            res = res == -1 ? node->right->val : min(node->right->val, res);
            dfs(node->left);
            return;
        }
        // 没有 pulse，那么我们只能进一步检查左右孩子
        dfs(node->left);
        dfs(node->right);
        return;
    };
    dfs(root);
    return res;
}