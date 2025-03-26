#include "Solution.h"

int Leetcode701_800::Soltuion::maxProfix(vector<int>& prices, int fee)
{
    // 股票系列又一题，经典的 DP 问题续作
    // 我们定义状态 DP 子问题：
    // dfs(i, st) 代表第 i 天时，手上 st == true -> 持有，st == false -> 不持有 股票的情况下
    // 能获得的最大收益
    // 那么我们考虑如何递推
    // 我们分类讨论 st 的值
    // st == true，那么当前我们手上持有股票，前一天手上可以持有股票，也可以不持有：
    // dfs(i, true) = max(dfs(i-1, false)-prices[i-1]-fee, dfs(i-1, true))
    // 如果前一天手上不持有股票，那么说明我们今天买了股票，也就是需要从前一天对应情况的最大利润中再减掉买股的价格和手续费
    // 而如果前一天手上已经持有了股票，那么我们今天什么也不用做
    // dfs(i, false) = max(dfs(i-1, true)+prices[i-1], dfs(i-1, false))
    // 推导过程类似上面的 dfs(i, true)
    // 两者取结果更大的即可
    function<int(int, bool)> dfs = [&](int i, bool st) -> int
    {
        // 考虑一下基本情况：
        // 如果 i == 1，说明是第一天，那么我们没法从 "前一天" 推导过来，只能根据 st 的值来决定当前结果
        if(i == 1)
        {
            if(st)
            {
                // st == true，说明我们第一天就买了股票，那么最大收益就是 -prices[0]-fee
                return -prices[0]-fee;
            }
            // 否则， st == false，说明我们第一天没买股票，那么返回 0 即可
            return 0;
        }
        // 一般情况：
        if(st)
        {
            return max(dfs(i-1, false)-prices[i-1]-fee, dfs(i-1, true));
        }
        return max(dfs(i-1, true)+prices[i-1], dfs(i-1, false));
    };
    // 调用即可
    return max(dfs(prices.size(), false), dfs(prices.size(), true));
}

// 第二版：给 dfs 加上记忆化
int maxProfix(vector<int>& prices, int fee)
{
    int n = prices.size();
    // 我们这里用 INT_MIN 来代指没记录过，实际上不严谨，但这种方法就是会有这样的问题 hhh
    vector<vector<int>> memo(n+1, vector<int>(2, INT_MIN));
    function<int(int, bool)> dfs = [&](int i, bool st) -> int
    {
        if(memo[i][st] != INT_MIN)
        {
            return memo[i][st];
        }
        // 考虑一下基本情况：
        // 如果 i == 1，说明是第一天，那么我们没法从 "前一天" 推导过来，只能根据 st 的值来决定当前结果
        if(i == 1)
        {
            if(st)
            {
                memo[i][st] = -prices[0]-fee;
                // st == true，说明我们第一天就买了股票，那么最大收益就是 -prices[0]-fee
                return memo[i][st];
            }
            // 否则， st == false，说明我们第一天没买股票，那么返回 0 即可
            memo[i][st] = 0;
            return 0;
        }
        // 一般情况：
        if(st)
        {
            memo[i][st] = max(dfs(i-1, false)-prices[i-1]-fee, dfs(i-1, true));
            return memo[i][st];
        }
        memo[i][st] = max(dfs(i-1, true)+prices[i-1], dfs(i-1, false));
        return memo[i][st];
    };
    // 调用即可
    return max(dfs(prices.size(), false), dfs(prices.size(), true));
}

// 加上了记忆化依然超时，我们最后考虑优化成纯 DP
int maxProfix(vector<int>& prices, int fee)
{
    int n = prices.size();
    vector<vector<int>> dp(n+1, vector<int>(2, 0));
    // 先初始化边界情况
    // 也就是 dp[1][true] 和 dp[1][false]
    dp[1][true] = -prices[0]-fee;
    // 之后按层递推即可
    for(int i = 2; i <= n; ++i)
    {
        dp[i][true] = max(dp[i-1][false]-prices[i-1]-fee, dp[i-1][true]);
        dp[i][false] = max(dp[i-1][true]+prices[i-1], dp[i-1][false]);
    }
    return max(dp[n][true], dp[n][false]);
}