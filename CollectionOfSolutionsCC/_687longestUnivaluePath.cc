#include "Solution.h"

int Leetcode601_700::Soltuion::longestUnivaluePath(Leetcode601_700::TreeNode* root)
{
    // 嘴皮子说烂了，二叉树的题，永远先从递归入手！！
    // 我们定义这样一个 dfs 函数：
    // dfs(node) 代表从 node 出发，只向左/向右走，可以拿到的最长同值路径长度
    // 那么我们可以这样计算 dfs(node) 的结果
    // 如果 node->left && node->left->val == node->val
    // 那么我们考虑进 dfs(node->left)+1 这个值
    // 如果 node->right && node->right->val == node->val
    // 那么我们考虑进 dfs(node->right)+1 这个值
    // 最后，上面两种情况下的较大值就可以作为 dfs(node) 的结果
    // 而题目说明了路径不必经过 root 根结点，所以我们只需要对所有结点都遍历一遍
    // 每个结点进行如下处理：
    // 以这个结点 node 为起点，如果 node->left && node->left->val == node->val
    // 那么 cur = dfs(node->left)
    // 如果 node->right && node->right->val == node->val
    // 那么 cur += dfs(node->right)
    // 最后，++cur，因为 node 本身还有长度
    // 遍历过程中记录一个全局的 res
    // 每计算完一个 cur，就更新 res：res = max(res, cur)
    // 都遍历完成后，拿到的最终结果就是 res 了
    // 最后，考虑树形 dp 形式的遍历，因为最外层对树的遍历这一部分，dfs 的结果实际上是可以复用的
    // 使用一个哈希表进行记忆化即可
    unordered_map<TreeNode*, int> memo;
    // 定义 dfs 函数
    function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int
    {
        // 如果 node 为空结点，那么直接返回 0 即可
        if(!node)
        {
            return 0;
        }
        // 添加记忆化
        if(memo.count(node))
        {
            return memo[node];
        }
        // 其它情况下，按上面说明的方法来做就行
        int res = 1;
        if(node->left && node->left->val == node->val)
        {
            res = max(res, 1+dfs(node->left));
        }
        if(node->right && node->right->val == node->val)
        {
            res = max(res, 1+dfs(node->right));
        }
        memo[node] = res;
        return res;
    };
    // 定义一个全局的结果值 maximum，初始为 1
    int maximum = 0;
    // 定义 traverse 函数
    function<int(TreeNode*)> traverse = [&](TreeNode* root) -> int
    {
        if(!root)
        {
            return 0;
        }
        // 其它情况下，按上面说的，进行树形 dp 处理，利用 memo 减少重复计算的次数
        traverse(root->left);
        traverse(root->right);
        // 左右孩子处理完成，开始对 node 本身进行处理，这就是后序遍历，也是树形 dp 的基本格式
        // 此时 memo 中已经记录了 dfs(node->left) 和 dfs(node->right) 的结果
        int ans = 0;
        if(root->left && root->left->val == root->val)
        {
            ans = dfs(root->left);
        }
        if(root->right && root->right->val == root->val)
        {
            ans += dfs(root->right);
        }
        maximum = max(maximum, ans);
        return ans;
    };
    traverse(root);
    return maximum;
}   