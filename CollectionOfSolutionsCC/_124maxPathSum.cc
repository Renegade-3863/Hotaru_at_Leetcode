#include "Solution.h"

// 第一版：单纯 DFS，没有记忆化优化
int Leetcode101_200::Solution::maxPathSum(Leetcode101_200::TreeNode* root)
{
    // 二叉树的问题基本都可以靠递归来解决，基本可以遵循先写递归解法，之后考虑能否转换成迭代方案的策略进行
    // 要求是找出一棵二叉树中所有可能的路径中路径和最大的那一条路径的路径和
    // 我们依然可以采用遍历+子情况计算的方式来求解
    // 定义如下的回调函数
    // dfs(subRoot) 代表经过 subRoot 的所有路径中路径和最大的那一条路径的路径和
    // 那么我们只需要对整棵树进行任意形式的遍历(前/中/后序遍历)即可找出最终的全局答案
    // 但是如何计算这个值呢？假设我们确定了一个 subRoot?
    // 如果我们要计算经过 subRoot 的最大路径值，那么显然需要这样两个值
    // 1. 从 subRoot 向左深入，可以得到的最大子路径和
    // 2. 从 subRoot 向右深入，可以得到的最大子路径和
    // 1 和 2 的值的和，跟 subRoot->val 求和，就是我们要的 dfs(subRoot) 结果
    // 当然从这个角度来看，这个函数名取得就不合适了，因为这个函数本身没有被递归调用
    // 所以我们改名叫 maxCross(subRoot) 更好一些
    // 至于 1 和 2 的求解函数，应该不难理解是真正的递归过程
    // 定义为 dfs(node)，返回值为由 node 出发，包括其结点本身，向左/向右不断深入可以得到的最大路径和
    // 那么我们显然可以得到如下的递归定义：
    // dfs(node) = max(dfs(node->left), dfs(node->right))+node->val
    // 等等，这行是后面新加入的，注意上面的递归定义，我们不是一定要取 max(dfs(node->left), dfs(node->right))+node->val 这个值，如果这个和为负数，那么显然会有问题
    // 为什么呢？注意到我们调用 dfs 函数的契机，它实际上是交给 maxCross 函数拿来判断 subRoot 结点应不应该向某个子结点进行深入，以及深入了，最大的可得贡献是多少的子过程
    // 那么，如果 dfs 函数告诉 maxCross 函数，它向右深入的最大可拿路径和竟然是个负数，那么 subRoot 还有必要向这边深入吗？很遗憾，我们在 maxCross 的逻辑中选择了深入
    // 所以，要避免这种情况发生，我们要么可以修改 maxCross，让它具备判断力，知道如果 dfs 告诉我走这边最大也只能拿一个负值，那么我就不走了
    // 要么就修改 dfs，让它如果发现走自己只能最大拿到一个负值，就告诉 maxCross 函数让 subRoot 不要走这边(即返回一个0)就行了
    // 我这里的逻辑采用了第二种方案
    // 总结好了上面的整体思路，我们就可以开始写代码了
    // 全局的最优解
    int res = INT_MIN;
    function<int(TreeNode*)> dfs = [&](TreeNode* node) ->int 
    {
        // 递归结束条件：node 为空结点
        if(!node)
        {
            return 0;
        }
        int leftBranch = dfs(node->left), rightBranch = dfs(node->right);
        return max(max(leftBranch, rightBranch)+node->val, 0);
    };
    function<int(TreeNode*)> maxCross = [&](TreeNode* subRoot) ->int
    {
        // 如果 subRoot 本身就是空结点，那么显然无法进行下面的逻辑，进行特判
        if(!subRoot)
        {
            return 0;
        }
        int goLeft = dfs(subRoot->left), goRight = dfs(subRoot->right);
        int loc = goLeft + subRoot->val + goRight;
        // 更新全局最优解
        res = max(res, loc);
        return loc;
    };
    // 最外层用中序遍历对整棵树进行遍历
    function<void(TreeNode*)> inorder = [&](TreeNode* root)
    {
        if(!root)
        {
            return;
        }
        inorder(root->left);
        maxCross(root);
        inorder(root->right);
    };
    // 调用入口
    inorder(root);
    return res;
}

// 第二版：DFS + 记忆化优化
int maxPathSum(Leetcode101_200::TreeNode* root)
{
    // 不难发现第一版代码中，dfs 函数被我们重复调用了很多次，所以这里我们考虑利用全局的记忆化进行效率优化
    // 记忆哈希表
    unordered_map<TreeNode*, int> memo;
    // 二叉树的问题基本都可以靠递归来解决，基本可以遵循先写递归解法，之后考虑能否转换成迭代方案的策略进行
    // 要求是找出一棵二叉树中所有可能的路径中路径和最大的那一条路径的路径和
    // 我们依然可以采用遍历+子情况计算的方式来求解
    // 定义如下的回调函数
    // dfs(subRoot) 代表经过 subRoot 的所有路径中路径和最大的那一条路径的路径和
    // 那么我们只需要对整棵树进行任意形式的遍历(前/中/后序遍历)即可找出最终的全局答案
    // 但是如何计算这个值呢？假设我们确定了一个 subRoot?
    // 如果我们要计算经过 subRoot 的最大路径值，那么显然需要这样两个值
    // 1. 从 subRoot 向左深入，可以得到的最大子路径和
    // 2. 从 subRoot 向右深入，可以得到的最大子路径和
    // 1 和 2 的值的和，跟 subRoot->val 求和，就是我们要的 dfs(subRoot) 结果
    // 当然从这个角度来看，这个函数名取得就不合适了，因为这个函数本身没有被递归调用
    // 所以我们改名叫 maxCross(subRoot) 更好一些
    // 至于 1 和 2 的求解函数，应该不难理解是真正的递归过程
    // 定义为 dfs(node)，返回值为由 node 出发，包括其结点本身，向左/向右不断深入可以得到的最大路径和
    // 那么我们显然可以得到如下的递归定义：
    // dfs(node) = max(dfs(node->left), dfs(node->right))+node->val
    // 等等，这行是后面新加入的，注意上面的递归定义，我们不是一定要取 max(dfs(node->left), dfs(node->right))+node->val 这个值，如果这个和为负数，那么显然会有问题
    // 为什么呢？注意到我们调用 dfs 函数的契机，它实际上是交给 maxCross 函数拿来判断 subRoot 结点应不应该向某个子结点进行深入，以及深入了，最大的可得贡献是多少的子过程
    // 那么，如果 dfs 函数告诉 maxCross 函数，它向右深入的最大可拿路径和竟然是个负数，那么 subRoot 还有必要向这边深入吗？很遗憾，我们在 maxCross 的逻辑中选择了深入
    // 所以，要避免这种情况发生，我们要么可以修改 maxCross，让它具备判断力，知道如果 dfs 告诉我走这边最大也只能拿一个负值，那么我就不走了
    // 要么就修改 dfs，让它如果发现走自己只能最大拿到一个负值，就告诉 maxCross 函数让 subRoot 不要走这边(即返回一个0)就行了
    // 我这里的逻辑采用了第二种方案
    // 总结好了上面的整体思路，我们就可以开始写代码了
    // 全局的最优解
    int res = INT_MIN;
    function<int(TreeNode*)> dfs = [&](TreeNode* node) ->int 
    {
        // 递归结束条件：node 为空结点
        if(!node)
        {
            return 0;
        }
        if(memo.find(node) != memo.end())
        {
            return memo[node];
        }
        int leftBranch = dfs(node->left), rightBranch = dfs(node->right);
        memo[node] = max(max(leftBranch, rightBranch)+node->val, 0);
        return memo[node];
    };
    // 最后补充一点，这个 maxCross 函数其实是可以直接放进 inorder 函数体内的，因为它本身不涉及递归过程。。。
    // function<int(TreeNode*)> maxCross = [&](TreeNode* subRoot) ->int
    // {
    //     // 如果 subRoot 本身就是空结点，那么显然无法进行下面的逻辑，进行特判
    //     if(!subRoot)
    //     {
    //         return 0;
    //     }
    //     int goLeft = dfs(subRoot->left), goRight = dfs(subRoot->right);
    //     int loc = goLeft + subRoot->val + goRight;
    //     // 更新全局最优解
    //     res = max(res, loc);
    //     return loc;
    // };
    // 最外层用中序遍历对整棵树进行遍历
    function<void(TreeNode*)> inorder = [&](TreeNode* root)
    {
        if(!root)
        {
            return;
        }
        inorder(root->left);
        int goLeft = dfs(root->left), goRight = dfs(root->right);
        // 更新全局最优解
        res = max(res, goLeft + root->val + goRight);
        inorder(root->right);
    };
    // 调用入口
    inorder(root);
    return res;
}