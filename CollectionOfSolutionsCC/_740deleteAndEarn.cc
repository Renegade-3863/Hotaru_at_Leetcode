#include "Solution.h"

// 第一版：暴力 DFS，不加记忆化
int Leetcode701_800::Soltuion::deleteAndEarn(vector<int>& nums)
{
    // 打家劫舍问题的变种，本质上是一个二维 DP 问题
    // 我们考虑这样定义递归的子问题：
    // dfs(i, deleted) 代表我们只考虑不大于 i 的那些元素，同时 deleted == true 代表我们删除了至少一个 i
    // deleted == false 代表我们没有删除 i
    // 这两种情况下的最大点数值
    // 那么考虑如何递推：
    // 1. 如果当前我们没有删除 i 这个值，那么这个状态之前可以是 dfs(i-1, false) 或者 dfs(i-1, true)
    // 因为我们这种情况下没有删除 i，所以我们可以选择删除 i-1 这种值，或者者不删除
    // 也就是 dfs(i, false) = max(dfs(i-1, false), dfs(i-1, true))
    // 2. 如果我们这一状态下删除了 i 这个值，那么我们就没法在前面的状态中删除 i-1 这个值了
    // 也就是 dfs(i, true) = dfs(i-1, false)+i*count[i]
    // 注意：只要想删除某种元素，删除它的所有个实例一定是最优的，count[i] 代表 nums 中 i 的个数
    // 我们先预处理 count 哈希表
    unordered_map<int, int> count;
    // maximum 用于最后调用 dfs 函数
    int maximum = 0;
    for(const auto& num : nums)
    {
        ++count[num];
        maximum = max(maximum, num);
    }
    function<int(int, bool)> dfs = [&](int i, bool d) -> int
    {
        // 先考虑结束条件
        // 如果 i == 1，说明我们只考虑了 1 这种元素
        // 那么我们根据 deleted 的值来判断要返回什么
        if(i == 1)
        {
            return d ? count[1] : 0;
        }
        // 之后是一般情况
        if(d)
        {
            // 我们删除了 i 这种值，那么我们就不能删除 i-1 这种值
            return dfs(i-1, false)+i*count[i];
        }
        return max(dfs(i-1, false), dfs(i-1, true));
    };
    // 两种情况取最大值即可
    return max(dfs(maximum, false), dfs(maximum, true));
}

// 第二版：给 DFS 加上记忆化
int deleteAndEarn(vector<int>& nums)
{
    unordered_map<int, int> count;
    // maximum 用于最后调用 dfs 函数
    int maximum = 0;
    for(const auto& num : nums)
    {
        ++count[num];
        maximum = max(maximum, num);
    }
    // 添加一个记忆化数组
    // -1 代表没有计算过
    vector<vector<int>> memo(maximum+1, vector<int>(2, -1));
    function<int(int, bool)> dfs = [&](int i, bool d) -> int
    {
        // 先考虑结束条件
        // 如果 i == 1，说明我们只考虑了 1 这种元素
        // 那么我们根据 deleted 的值来判断要返回什么
        if(i == 1)
        {
            return d ? count[1] : 0;
        }
        // 记忆化代码
        if(memo[i][d] != -1)
        {
            return memo[i][d];
        }
        // 之后是一般情况
        if(d)
        {
            // 我们删除了 i 这种值，那么我们就不能删除 i-1 这种值
            memo[i][d] = dfs(i-1, false)+i*count[i];
            return memo[i][d];
        }
        memo[i][d] = max(dfs(i-1, false), dfs(i-1, true));
        return memo[i][d];
    };
    // 两种情况取最大值即可
    return max(dfs(maximum, false), dfs(maximum, true));
}

// 第三版：把自顶向下的 DFS 方法改成自底向上的 DP 方法
int deleteAndEarn(vector<int>& nums)
{
    unordered_map<int, int> count;
    // maximum 用于最后调用 dfs 函数
    int maximum = 0;
    for(const auto& num : nums)
    {
        ++count[num];
        maximum = max(maximum, num);
    }
    // 初始化 dp 数组
    vector<vector<int>> dp(maximum+1, vector<int>(2, 0));
    // 初始化基本情况，也就是 dp[1][0] 和 dp[1][1]
    dp[1][0] = 0;
    dp[1][1] = count[1];
    // 开始递推
    for(int i = 2; i <= maximum; ++i)
    {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
        dp[i][1] = dp[i-1][0]+i*count[i];
    }
    // 两种情况取最大值即可
    return max(dp[maximum][0], dp[maximum][1]);
}