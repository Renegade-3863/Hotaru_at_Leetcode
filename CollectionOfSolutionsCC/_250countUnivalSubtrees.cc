#include "Solution.h"

int Leetcode201_300::Solution::countUnivalSubtrees(Leetcode201_300::TreeNode* root)
{
    // 一道比较明显的树形 DFS 类问题，可以使用类似 DFS 的方案简单求解
    // 考虑下面的递归子过程：
    // 一个 dfs 函数：dfs(TreeNode* root)
    // 返回的是：以 root 为根结点的子树是否是一个同值子树
    // 保存一个全局的最大值
    // 注意对于全局最大值的更新策略：我们只有在第一次检查这个根结点的时候才能更新全局的最大值，不然会由于子问题导致重复更新全局结果，这样显然是不对的，我们使用哈希表的形式来避免重复更新
    unordered_map<TreeNode*, bool> memo;
    int res = 0;
    function<bool(TreeNode*)> dfs = [&](TreeNode* root) -> bool 
    {
        if(memo.find(root) != memo.end())
        {
            return memo[root];
        }
        // 空树，返回true即可
        if(!root)
        {
            return true;
        }
        // 否则，需要先判断左右两侧的子树是不是一棵同值子树
        bool leftUnival = dfs(root->left);
        bool rightUnival = dfs(root->right);
        // 如果左右子树都是同值子树，那么必须保证二者的根结点值都等于本根结点的值才能返回 true，否则就只能返回 false
        if(!leftUnival || !rightUnival)
        {
            memo[root] = false;
            return false;
        }
        // 左右均为同值子树的情况
        // 还需要判断两个子树是空树的情况，防止访问空结点
        if((!root->left || root->left->val == root->val) && (!root->right || root->right->val == root->val))
        {
            ++res;
            memo[root] = true;
            return true;
        }
        memo[root] = false;
        // 否则，只能返回 false 
        return false;
    };
    // 对整棵树进行遍历，并在过程中对每个结点进行处理即可
    stack<TreeNode*> stk;
    TreeNode* cur = root;
    while(cur || !stk.empty())
    {
        if(cur)
        {
            stk.push(cur);
            cur = cur->left;
        }
        else
        {
            cur = stk.top();
            stk.pop();
            // 进行访问
            dfs(cur);
            cur = cur->right;
        }
    }
    // 返回结果即可
    return res;
}