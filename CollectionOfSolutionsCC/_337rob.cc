#include "Solution.h"

// 第一版：暴力 DFS，不加任何记忆化
int Leetcode301_400::Solution::rob(Leetcode301_400::TreeNode* root)
{
    // 打家劫舍之：小偷是个下岗的码农
    // 本质上还是 DP，不过从不允许偷窃数组中相邻的房子变成了不允许偷窃树中相邻的房子，没有其它区别
    // 我们依然先从自顶向下的角度入手
    // 定义下面的 DFS 子过程：
    // dfs(node, steal) 代表小偷在以 node 为根的子树中偷窃，并且 (steal == true -> 偷窃, steal == false -> 不偷窃) 当前 node 的房屋，最多可以偷到的金额数
    // 考虑递推过程
    // 对于这个母问题，很明显
    // dfs(node, true) = node->val + dfs(node->left, false) + dfs(node->right, false)
    // 即：偷了当前结点，之后，左右子树的根结点都不偷的情况下，再进入对应子树可以拿到的最大金额之和
    // dfs(node, false) = max(dfs(node->left, true), dfs(node->left, false)) + max(dfs(node->right, true), dfs(node->right, false))
    // 这一步需要稍微理解一下：
    // 当前房屋不偷，那么我们显然可以：偷左孩子，并继续深入偷窃，或者不偷左孩子，并继续深入偷窃
    // 同样的，可以：偷右孩子，并继续深入偷窃，或者不偷右孩子，并继续深入偷窃
    // 而左右孩子的情况处理是完全独立的，所以我们没必要分四种组合进行讨论，直接取各自的最大值即可
    // 明确了上面的逻辑，剩下的就是写答案了
    function<int(TreeNode*, bool)> dfs = [&](TreeNode* node, bool steal) 
    {
        // 明确一下最终的子问题，可以直接求解的那种
        if(!node)
        {
            // 空结点，此时我们很显然直接返回 0 即可，因为没有房子可以偷
            return 0;
        }
        // 其它情况：我们会需要根据上面的逻辑进行递归求解
        if(steal)
        {
            return node->val + dfs(node->left, false) + dfs(node->right, false);
        }
        return max(dfs(node->left, true), dfs(node->left, false)) + max(dfs(node->right, true), dfs(node->right, false));
    };
    // 直接对根结点调用即可
    return max(dfs(root, true), dfs(root, false));
}

// 第二版：DFS 加记忆化加速
int rob(Leetcode301_400::TreeNode* root)
{
    // 打家劫舍之：小偷是个下岗的码农
    // 本质上还是 DP，不过从不允许偷窃数组中相邻的房子变成了不允许偷窃树中相邻的房子，没有其它区别
    // 我们依然先从自顶向下的角度入手
    // 定义下面的 DFS 子过程：
    // dfs(node, steal) 代表小偷在以 node 为根的子树中偷窃，并且 (steal == true -> 偷窃, steal == false -> 不偷窃) 当前 node 的房屋，最多可以偷到的金额数
    // 考虑递推过程
    // 对于这个母问题，很明显
    // dfs(node, true) = node->val + dfs(node->left, false) + dfs(node->right, false)
    // 即：偷了当前结点，之后，左右子树的根结点都不偷的情况下，再进入对应子树可以拿到的最大金额之和
    // dfs(node, false) = max(dfs(node->left, true), dfs(node->left, false)) + max(dfs(node->right, true), dfs(node->right, false))
    // 这一步需要稍微理解一下：
    // 当前房屋不偷，那么我们显然可以：偷左孩子，并继续深入偷窃，或者不偷左孩子，并继续深入偷窃
    // 同样的，可以：偷右孩子，并继续深入偷窃，或者不偷右孩子，并继续深入偷窃
    // 而左右孩子的情况处理是完全独立的，所以我们没必要分四种组合进行讨论，直接取各自的最大值即可
    // 明确了上面的逻辑，剩下的就是写答案了
    // 添加一个记忆化哈希表
    // 这里的键是数对，所以我们还需要重载哈希表的哈希函数和全等函数
    struct myPair {
    public:
        myPair(TreeNode* _node, bool _steal) : node(_node), steal(_steal) {}
        TreeNode* node;
        bool steal;
    };
    struct hashFunc {
        size_t operator() (const myPair& a) const
        {
            return hash<TreeNode*>()(a.node) ^ hash<int>()(a.steal);
        }
    };
    struct equalFunc {
        bool operator() (const myPair& a, const myPair& b) const
        {
            return a.node == b.node && a.steal == b.steal;
        }
    };
    unordered_map<myPair, int, hashFunc, equalFunc> memo;
    function<int(TreeNode*, bool)> dfs = [&](TreeNode* node, bool steal) 
    {
        // 记忆化加速
        if(memo.find({node, steal}) != memo.end())
        {
            return memo[{node, steal}];
        }
        // 明确一下最终的子问题，可以直接求解的那种
        if(!node)
        {
            memo[{node, steal}] = 0;
            // 空结点，此时我们很显然直接返回 0 即可，因为没有房子可以偷
            return 0;
        }
        // 其它情况：我们会需要根据上面的逻辑进行递归求解
        if(steal)
        {
            memo[{node, steal}] = node->val + dfs(node->left, false) + dfs(node->right, false);
            return memo[{node, steal}];
        }
        memo[{node, steal}] = max(dfs(node->left, true), dfs(node->left, false)) + max(dfs(node->right, true), dfs(node->right, false));
        return memo[{node, steal}];
    };
    // 直接对根结点调用即可
    return max(dfs(root, true), dfs(root, false));
}