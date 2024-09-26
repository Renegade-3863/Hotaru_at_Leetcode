#include "Solution.h"

// 第一版：不带记忆化
int Leetcode101_200::Solution::maxDepth(Leetcode101_200::TreeNode* root)
{
    // 简单的 DFS 题目
    // 可以考虑直接使用题中函数作为回调函数体
    // 返回值为从 root 结点到最远叶子结点的最长路径上的结点数
    // 空子树作为递归结束条件，返回0
    if(!root)
    {
        return 0;
    }
    // 进行递归计算
    // 记录左孩子到其最远叶子结点到路径上的结点数
    int left = maxDepth(root->left);
    // 记录右孩子到其最远叶子结点到路径上的结点数
    int right = maxDepth(root->right);
    // 更新当前根结点的最大结果
    return max(left+1, right+1);
}

// 第二版：带上记忆化
// 记忆化哈希表需要是全局的，因此定义在 maxDepth 函数体外
// 虽然测试下来似乎效果还不如不加记忆化。。。
unordered_map<TreeNode*, int> memo;
int maxDepth(Leetcode101_200::TreeNode* root)
{
    if(memo.find(root) != memo.end())
    {
        return memo[root];
    }
    // 简单的 DFS 题目
    // 可以考虑直接使用题中函数作为回调函数体
    // 返回值为从 root 结点到最远叶子结点的最长路径上的结点数
    // 空子树作为递归结束条件，返回0
    if(!root)
    {
        return 0;
    }
    // 进行递归计算
    // 记录左孩子到其最远叶子结点到路径上的结点数
    int left = maxDepth(root->left);
    // 记录右孩子到其最远叶子结点到路径上的结点数
    int right = maxDepth(root->right);
    // 更新当前根结点的最大结果
    memo[root] = max(left+1, right+1);
    return memo[root];
}