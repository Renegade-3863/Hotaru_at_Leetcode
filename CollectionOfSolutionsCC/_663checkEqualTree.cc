#include "Solution.h"

bool Leetcode601_700::Soltuion::checkEqualTree(Leetcode601_700::TreeNode* root)
{
    // 分析题目的要求，本质上来说，我们要去掉一条边
    // 就一定需要找到一棵子树，这棵子树的值总和等于整棵树的一半
    // 这就简化了我们需要完成的任务
    // 不再是找边这种抽象的任务
    // 而变成了找子树
    // 综上，我们用一轮 dfs，记录每个结点所在子树的值之和，最后查找是否存在 sum/2 (sum 为 root 树中所有结点的值之和)
    // 这样的子树即可
    // dfs(node) 用于计算并记录以 node 为根结点的子树的值之和
    // 用一个哈希表处理一下记忆化
    unordered_map<TreeNode*, int> memo;
    unordered_map<int, int> exist;
    function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int
    {
        // 空子树，基本情况，值之和为 0
        if(!node)
        {
            return 0;
        }
        // 其它情况下，值之和为左右子树的值之和，加上当前 node->val
        // 记忆化步骤
        if(memo.count(node))
        {
            return memo[node];
        }
        memo[node] = dfs(node->left)+dfs(node->right)+node->val;
        ++exist[memo[node]];
        return memo[node];
    };
    // 对 root 调用一次 dfs
    dfs(root);
    // 检查 exist 中是否记录了 memo[root]/2 这个值
    // 一个特殊情况：如果 memo[root] == 0，那么我们需要判断 exist[memo[root]/2] 是否大于 1
    if(memo[root] == 0)
    {
        return exist[memo[root]/2] > 1;
    }
    // 首先，我们知道，如果 memo[root] 不是偶数，那么我们不可能把它拆成两部分一样和的子树
    if(memo[root]%2)
    {
        return false;
    }
    return exist[memo[root]/2] > 0;
}