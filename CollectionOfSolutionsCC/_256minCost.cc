#include "Solution.h"

// 第一版：单纯暴力 DFS，不包含任何记忆化，可以预见的 TLE
int Leetcode201_300::Solution::minCost(vector<vector<int>>& costs)
{
    // 经典的 DP 形式的问题，我们可以先从自顶向下的角度来考虑定义本题的子问题
    // 定义 dfs(i, color) 代表的是粉刷完前 i 间房子，并且最后一间房粉刷为 color 色的最低花销
    // 按 color 的颜色进行分类讨论
    // 1. color == RED
    // 那么 dfs(i, RED) = min(dfs(i-1, BLUE), dfs(i-1, GREEN)) + costs[i-1][0]
    // 2. color == BLUE
    // 那么 dfs(i, BLUE) = min(dfs(i-1, RED), dfs(i-1, GREEN)) + costs[i-1][1]
    // 3. color == GREEN
    // 那么 dfs(i, GREEN) = min(dfs(i-1, RED), dfs(i-1, BLUE)) + costs[i-1][2]
    function<int(int, int)> dfs = [&](int i, int color)
    {
        // 递归的基本情况：
        // 如果 i == 1，代表此时我们只有一间房子需要粉刷，我们可以直接返回对应的结果
        if(i == 1)
        {
            switch(color)
            {
                case 0: 
                    return costs[0][0]; 
                case 1:
                    return costs[0][1];
                default:
                    return costs[0][2];
            }
        }
        // 常规情况
        // 按照上面的方案进行递归即可
        // 情况1.
        if(color == 0)
        {
            return min(dfs(i-1, 1), dfs(i-1, 2)) + costs[i-1][0];
        }
        if(color == 1)
        {
            return min(dfs(i-1, 0), dfs(i-1, 2)) + costs[i-1][1];
        }
        return min(dfs(i-1, 0), dfs(i-1, 1)) + costs[i-1][2];
    };
    // 进行调用即可
    int n = costs.size();
    return min(min(dfs(n, 0), dfs(n, 1)), dfs(n, 2));
}

// 第二版：DFS + 使用数组进行记忆化
int minCost(vector<vector<int>>& costs)
{
    // 添加一个记忆化数组
    vector<vector<int>> memo(costs.size(), vector<int>(3, -1));
    // 经典的 DP 形式的问题，我们可以先从自顶向下的角度来考虑定义本题的子问题
    // 定义 dfs(i, color) 代表的是粉刷完前 i 间房子，并且最后一间房粉刷为 color 色的最低花销
    // 按 color 的颜色进行分类讨论
    // 1. color == RED
    // 那么 dfs(i, RED) = min(dfs(i-1, BLUE), dfs(i-1, GREEN)) + costs[i-1][0]
    // 2. color == BLUE
    // 那么 dfs(i, BLUE) = min(dfs(i-1, RED), dfs(i-1, GREEN)) + costs[i-1][1]
    // 3. color == GREEN
    // 那么 dfs(i, GREEN) = min(dfs(i-1, RED), dfs(i-1, BLUE)) + costs[i-1][2]
    function<int(int, int)> dfs = [&](int i, int color)
    {
        // 记忆化步骤
        if(memo[i-1][color] != -1)
        {
            return memo[i-1][color];
        }
        // 递归的基本情况：
        // 如果 i == 1，代表此时我们只有一间房子需要粉刷，我们可以直接返回对应的结果
        if(i == 1)
        {
            switch(color)
            {
                case 0: 
                    memo[0][0] = costs[0][0];
                    return costs[0][0]; 
                case 1:
                    memo[0][1] = costs[0][1];
                    return costs[0][1];
                default:
                    memo[0][2] = costs[0][2]; 
                    return costs[0][2];
            }
        }
        // 常规情况
        // 按照上面的方案进行递归即可
        // 情况1.
        if(color == 0)
        {
            memo[i-1][0] = min(dfs(i-1, 1), dfs(i-1, 2)) + costs[i-1][0];
            return memo[i-1][0];
        }
        if(color == 1)
        {
            memo[i-1][1] = min(dfs(i-1, 0), dfs(i-1, 2)) + costs[i-1][1];
            return memo[i-1][1];
        }
        memo[i-1][2] = min(dfs(i-1, 0), dfs(i-1, 1)) + costs[i-1][2];
        return memo[i-1][2];
    };
    // 进行调用即可
    int n = costs.size();
    return min(min(dfs(n, 0), dfs(n, 1)), dfs(n, 2));
}

// 第三版：改成自底向上的 DP 方法
int minCost(vector<vector<int>>& costs)
{
    int n = costs.size();
    // 不合法情况判断
    if(n <= 0)
    {
        return 0;
    }
    vector<vector<int>> dp(costs.size(), vector<int>(3, 0));
    dp[0][0] = costs[0][0];
    dp[0][1] = costs[0][1];
    dp[0][2] = costs[0][2];
    // 进行递推即可
    for(int i = 1; i < n; ++i)
    {
        dp[i][0] = min(dp[i-1][1], dp[i-1][2])+costs[i][0];
        dp[i][1] = min(dp[i-1][0], dp[i-1][2])+costs[i][1];
        dp[i][2] = min(dp[i-1][0], dp[i-1][1])+costs[i][2];
    }
    // 返回结果
    return min(min(dp[n-1][0], dp[n-1][1]), dp[n-1][2]);
}

// 第四版：对二维 DP 进行空间优化
int minCost(vector<vector<int>>& costs)
{
    // 注意到第三版的递推填表过程，每一层三个值只与上一层的三个值有关，因而我们可以利用滚动数组进行空间优化
    int n = costs.size();
    if(n <= 0)
    {
        return 0;
    }
    int dp0 = costs[0][0], dp1 = costs[0][1], dp2 = costs[0][2];
    for(int i = 1; i < n; ++i)
    {
        int tmp0 = dp0, tmp1 = dp1;
        dp0 = min(dp1, dp2)+costs[i][0];
        dp1 = min(tmp0, dp2)+costs[i][1];
        dp2 = min(tmp0, tmp1)+costs[i][2];
    }
    return min(min(dp0, dp1), dp2);
}