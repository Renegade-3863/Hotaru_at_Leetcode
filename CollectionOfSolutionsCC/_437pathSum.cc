#include "Solution.h"

int Leetcode101_200::Solution::pathSum3(Leetcode101_200::TreeNode* root, int targetSum)
{
    // 定义全局的结果
    int res = 0;
    // 本题相对于路径总和 II 进行了问题的一般化，要求找出的不再是从一棵子树的根结点出发到叶子结点的限制性路径了
    // 变成了树中任意一条方向向下的简单路径
    // 个人认为本题依然可以采用递归的方案来解决
    // 定义如下的递归回调函数
    // int dfs(root, targetSum) 代表以 root 作为起点的所有向下的，和为 targetSum 的简单路径的总数
    // 此时我们的答案不再是某一个回调函数的结果，而是一个全局的变量 (sum)
    // 我们在遍历整棵树的过程中动态滴地更新这个全局变量即可
    function<int(TreeNode*, long long)> dfs = [&](TreeNode* subRoot, long long target) -> int
    {
        // 如果是空树，那么必然不存在路径，直接返回0即可
        if(!subRoot)
        {
            return 0;
        }
        int loc = 0;
        // 如果不是空树，先判断当前这个结点本身的值是不是就已经等于 target 了
        if(subRoot->val == target)
        {
            ++loc;
        }
        // 既不代表空树，也不是一个叶子结点，那么就需要递归地进行判断了
        // 先计算以当前 subRoot 为路径起点的所有路径和为 target 的路径个数
        int leftCnt = dfs(subRoot->left, target-subRoot->val), rightCnt = dfs(subRoot->right, target-subRoot->val);
        loc += leftCnt; loc += rightCnt;
        // 简单返回本地结果即可
        return loc;
    };  
    // 对整棵树进行遍历，遍历过程中调用上面的递归函数
    // 如果是空树，直接返回0即可
    if(!root)
    {
        return 0;
    }
    // 否则，对树进行遍历(前中后序均可，这里采用中序)
    // 递归版中序，写法简单一些
    res += pathSum(root->left, targetSum);
    res += dfs(root, targetSum);
    res += pathSum(root->right, targetSum);
    return res;
}

// 题解给出的前缀和解法其实感觉类似两数之和的想法，不过感觉真正面试中不是很好想到那种方案，不过这里还是尝试自己再写一遍
// 定义一个全局的哈希函数，用于记录已经遍历过的路径上的前缀和
// 记录的是到当前结点的路径上出现过的所有前缀和的值的个数
unordered_map<long long, int> prefix;
int pathSum(Leetcode101_200::TreeNode* root, int targetSum)
{
    function<int(TreeNode*, long long)> dfs = [&](TreeNode* subRoot, long long cur) ->int
    {
        if(!subRoot)
        {
            return 0;
        }
        int ret = 0;
        cur += subRoot->val;
        if(prefix.find(cur-targetSum) != prefix.end())
        {
            ret = prefix[cur-targetSum];
        }
        ++prefix[cur];
        ret += dfs(subRoot->left, cur);
        ret += dfs(subRoot->right, cur);
        --prefix[cur];

        return ret;
    };
    prefix[0] = 1;
    return dfs(root, 0);
}

// 算法跳动给出的进阶问题：请你打印出所有可行的路径
// 对于这种打印路径的问题，其实不用多想，不是回溯就是回溯
// 我们依然是按照前/中/后序遍历的方式，找出从每个结点开始的所有和为 targetSum 的向下延伸路径即可
vector<vector<int>> pathSum(Leetcode101_200::TreeNode* root, int targetSum)
{
    // 本题我们按照回溯的标准写法来编写回溯函数
    function<void(vector<vector<int>>&, vector<int>&, TreeNode*, int)> backtrack = [&](vector<vector<int>>& res, vector<int>& path, TreeNode* cur, int curVal)
    {
        // 回溯的结束标志：当前遍历到的结点是一个空结点
        // 只需要返回即可
        if(!cur)
        {
            return;
        }
        path.push_back(cur->val);
        // 否则，检查算上当前结点，当前路径的总和是否等于了 targetSum
        if(curVal + cur->val == targetSum)
        {
            // 等于了，就把当前路径记录到全局结果中
            res.push_back(path);
            // 注意，我们要的不是到叶子结点到路径，继续向下深入可能还会有后续的可行路径
        }
        // 尝试进行递归步骤
        // 深入
        // 先向左
        backtrack(res, path, cur->left, curVal+cur->val);
        // 再向右
        backtrack(res, path, cur->right, curVal+cur->val);
        // 回溯
        path.pop_back();
    };
    // 使用前/中/后序遍历对从这棵树中所有结点开始的路径都执行上面的回溯过程
    vector<vector<int>> res;
    vector<int> path;
    function<void(TreeNode*)> traverse = [&](TreeNode* subRoot)
    {
        if(!subRoot)
        {
            return;
        }
        // 中序遍历
        traverse(res, path, subRoot->left);
        backtrack(res, path, subRoot, 0);
        traverse(res, path, subRoot->right);
    };
    // 调用函数即可
    traverse(root);
    return res;
}