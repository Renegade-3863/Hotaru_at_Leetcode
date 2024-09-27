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

// 第三版：完全优化的 DP 方案
int maxPathSumDP(Leetcode101_200::TreeNode* root)
{
    // 正常在树上的自底向上方案常常是不那么容易理解的
    // 这样考虑：
    // 我们第二版和第一版中实现的递归回调函数 dfs
    // 总有 dfs(node) = max(max(dfs(node->left), dfs(node->right)), 0) 
    // 也就是说，我们在计算当前结点之前，必须要知道它的左右孩子的计算结果
    // 这实际上与后序遍历的思想不谋而合，我们可以使用递推数组/哈希表+后序遍历的方式来实现不使用递归函数调用的方案实现
    unordered_map<TreeNode*, int> dp;
    // 边界情况：空指针的答案记录为0
    dp[nullptr] = 0;
    int res = INT_MIN;
    function<void(TreeNode*)> postOrder = [&](TreeNode* node)
    {
        if(!node)
        {
            return;
        }
        postOrder(node->left);
        postOrder(node->right);
        int ret = max(max(dp[node->left], dp[node->right])+node->val, 0);
        dp[node] = ret;
        // 在这里就可以更新最大结果了
        res = max(res, dp[node->left]+dp[node->right]+node->val);
    };
    postOrder(root);
    return res;
}

// 第四版：完全优化的 DP 方案 + 迭代方案重写
int maxPathSumDPIter(Leetcode101_200::TreeNode* root)
{
    unordered_map<TreeNode*, int> dp;
    int res = INT_MIN;
    dp[nullptr] = 0;
    function<void(TreeNode*)> postOrder = [&](TreeNode* node)
    {
        TreeNode* cur = node, * pre = nullptr;
        stack<TreeNode*> stk;
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
                if(cur->right && cur->right != pre)
                {
                    cur = cur->right;
                    continue;
                }
                else
                {
                    int ret = max(max(dp[cur->left], dp[cur->right])+cur->val, 0);
                    dp[cur] = ret;
                    res = max(res, dp[cur->left]+cur->val+dp[cur->right]);
                    stk.pop();
                    pre = cur;
                    cur = nullptr;
                }
            }
        }
    };
    postOrder(root);
    return res;
}

// 算法跳动给出的进阶题目：请你输出所有不同的具有最大和值的路径？
vector<vector<int>> maxPathSumAllPaths(Leetcode101_200::TreeNode* root)
{
    // 要想知道这样一组 vector，每个内部保存一条路径值和最大的结果，我们需要的是一种返回子最大路径的策略，这几本上就是把 dfs 返回的东西从一个值(最大路径和)
    // 变成了一组子路径 (vector<<vector<int>>)
    // 同时，为了知道左右两侧的最大值路径哪一个更大，我们还需要上一题中的对应最大路径值信息，所以这里我们考虑使用一个结构体记录这两项信息
    // 我们尝试用代码来实现
    // 记忆化哈希表，这次我们记忆的是一些二维数组，而不是对应的最大路径和
    unordered_map<TreeNode*, info> memo;
    // 递归回调函数
    // 返回值为所有从本结点 node 出发可以拿到最大路径和的路径信息
    function<info(TreeNode*)> dfs = [&](TreeNode* node) ->info
    {
        // 如果是空结点，直接返回空集合，代表不存在路径
        if(!node)
        {
            return info();
        }
        if(memo.find(node) != memo.end())
        {
            return memo[node];
        }
        // 这个数组是用来记录本地的所有可得最大路径和的路径的
        vector<vector<int> > ret;
        // 分别找出左右两侧的最大和路径
        info leftInfo = dfs(node->left);
        info rightInfo = dfs(node->right);
        // 进行排列组合
        int m = leftInfo.paths.size(), n = rightInfo.paths.size();
        // 当前结点出发不存在正贡献的子路径，我们直接告诉上层调用者这一消息即可
        if(max(max(leftInfo.maxSum, rightInfo.maxSum)+node->val, 0) == 0)
        {
            memo[node] = info();
            return memo[node];
        }
        // 如果左侧子路径的最大值更大，我们要把这部分和 node 结点连起来作为答案返回
        else if(leftInfo.maxSum > rightInfo.maxSum)
        {
            for(int i = 0; i < leftInfo.paths.size(); ++i)
            {
                // 直接利用原子路径数组，在每一个结尾都加上一个 node 结点的值即可
                leftInfo.paths[i].push_back(node->val);
            }
            if(leftInfo.paths.size() == 0)
            {
                leftInfo.paths.push_back(vector<int>(1, node->val));
            }
            memo[node] = leftInfo;
            memo[node].maxSum = leftInfo.maxSum+node->val;
            // 返回这些更新后的路径
            return memo[node];
        }
        // 两侧子路径的最大值相同，我们需要把两部分的路径都添加 node 结点后返回
        else if(leftInfo.maxSum == rightInfo.maxSum)
        {
            for(int i = 0; i < leftInfo.paths.size(); ++i)
            {
                // 直接利用原子路径数组，在每一个结尾都加上一个 node 结点的值即可
                leftInfo.paths[i].push_back(node->val);
            }
            for(int i = 0; i < rightInfo.paths.size(); ++i)
            {
                // 直接利用原子路径数组，在每一个开头都加上一个 node 结点的值即可
                rightInfo.paths[i].insert(rightInfo.paths[i].begin(), node->val);
            }
            // 把两个大数组记录合并
            vector<vector<int> > ans(leftInfo.paths.begin(), leftInfo.paths.end());
            for(int i = 0; i < rightInfo.paths.size(); ++i)
            {
                ans.push_back(rightInfo.paths[i]);
            }
            if(leftInfo.paths.size() == 0)
            {
                ans.push_back(vector<int>(1, node->val));
            }
            memo[node] = info(leftInfo.maxSum+node->val, ans);
            memo[node].maxSum = leftInfo.maxSum+node->val;
            // 返回合并后的大数组
            return memo[node];
        }
        // 右侧子路径的最大值更大，我们要把这部分和 node 结点连起来作为答案返回
        for(int i = 0; i < rightInfo.paths.size(); ++i)
        {
            // 直接利用原子路径数组，在每一个开头都加上一个 node 结点的值即可
            rightInfo.paths[i].insert(rightInfo.paths[i].begin(), node->val);
        }
        if(rightInfo.paths.size() == 0)
        {
            rightInfo.paths.push_back(vector<int>(1, node->val));
        }
        memo[node] = rightInfo;
        memo[node].maxSum = rightInfo.maxSum+node->val;
        // 返回这些更新后的路径
        return memo[node];
    };
    vector<vector<int> > maxPaths;
    int res = INT_MIN;
    // 执行后序遍历
    function<void(TreeNode*)> postOrder = [&](TreeNode* root)
    {
        if(!root)
        {
            return;
        }
        postOrder(root->left);
        postOrder(root->right);
        info leftInfo = dfs(root->left), rightInfo = dfs(root->right);
        // 如果出现了更大的路径可能或者出现了更多的等于已知最大路径和的路径，就要更新记录最大路径的结果数组
        if(leftInfo.maxSum + root->val + rightInfo.maxSum >= res)
        {
            // 如果出现的是更大的路径和，要先清空结果数组
            if(leftInfo.maxSum + root->val + rightInfo.maxSum > res)
            {
                maxPaths = vector<vector<int> >();
            }
            vector<int> path;
            path.push_back(root->val);
            // 再次排列组合
            for(int i = 0; i < leftInfo.paths.size(); ++i)
            {
                path = vector<int>();
                path.push_back(root->val);
                for(int j = 0; j < rightInfo.paths.size(); ++j)
                {
                    for(int k = 0; k < leftInfo.paths[i].size(); ++k)
                    {
                        path.insert(path.begin(), leftInfo.paths[i][k]);
                    }
                    for(int k = 0; k < rightInfo.paths[j].size(); ++k)
                    {
                        if(path.size() > 1)
                        {
                            path.push_back(rightInfo.paths[j][k]);
                        }
                        else
                        {
                            path.insert(path.begin(), rightInfo.paths[j][k]);;
                        }
                    }
                }
            }
            maxPaths.push_back(path);
            res = leftInfo.maxSum + root->val + rightInfo.maxSum;
        }
    };
    postOrder(root);
    return maxPaths;
}