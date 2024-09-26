#include "Solution.h"

// 第一版：暴力 DFS，可以预见的 TLE
int Leetcode101_200::Solution::maxProfit2(vector<int>& prices)
{
    // 本来做完了 121 题，兴高采烈地想直接把第四版代码套过来改改参数就最优的，结果这题 cnt 的值无上限。。。 (就是允许无限多次交易)
    // 那么实际上我们如果沿用上一题的那种滚动平面的递推方案，稍微看看代码就知道是 O(n^2) 的时间复杂度，肯定是很容易 TLE 的
    // 所以对于本题，需要重新考虑如何进行子问题的定义
    // 一个简单粗暴的方法是，即然我带上这个 cnt 的取值进行遍历会把时间复杂度变成 O(n^2)，那我不要它了，是不是就能压缩成 O(n) ?
    // 就是按照如下方式进行子问题定义：
    // dfs(i, hold) 代表我们在第 i 天，手里 (hold == true -> 持有，hold == false -> 不持有) 股票的情况下所能获得的最大利润
    // 这样可以进行递归吗？
    // 显然会发现是完全可行的，考虑：
    // 1. hold == true，那么显然的情况是，我们前一天可以是手中持有股票的 dfs(i-1, true) 或者不持有股票的 dfs(i-1, false)
    // 而如果前一天不持有股票，那么我们应该是在当天 (第 i 天) 购买了这支股票，也就是 dfs(i-1, false) + prices[i-1]
    // 所以此时的最大利润应该是：前一天手里持有股票的最大利润，和前一天手里不持有股票，而今天购买了股票的 这两种状态利润的较大值
    // 即 dfs(i, true) = max(dfs(i-1, true), dfs(i-1, false)-prices[i-1])
    // 2. hold == false，如法推理：
    // dfs(i, false) = max(dfs(i-1, false), dfs(i-1, true)+prices[i-1])
    // 按照上面的思路，就不难写出递归代码了
    function<int(int, bool)> dfs = [&](int i, bool hold) 
    {
        // 边界情况：i == 1
        if(i == 1)
        {
            return (hold ? -prices[0] : 0);
        }
        // 进行递归
        if(hold)
        {
            return max(dfs(i-1, true), dfs(i-1, false)-prices[i-1]);
        }
        return max(dfs(i-1, false), dfs(i-1, true)+prices[i-1]);
    };
    // 全局的最大结果值
    int res = 0;
    // 遍历求解每一天的最大值即可
    for(int i = 1; i <= prices.size(); ++i)
    {
        res = max(res, dfs(i, false));
    }
    return res;
}

// 第二版：DFS + 记忆化
int maxProfit2Memo(vector<int>& prices)
{
    // 本来做完了 121 题，兴高采烈地想直接把第四版代码套过来改改参数就最优的，结果这题 cnt 的值无上限。。。 (就是允许无限多次交易)
    // 那么实际上我们如果沿用上一题的那种滚动平面的递推方案，稍微看看代码就知道是 O(n^2) 的时间复杂度，肯定是很容易 TLE 的
    // 所以对于本题，需要重新考虑如何进行子问题的定义
    // 一个简单粗暴的方法是，即然我带上这个 cnt 的取值进行遍历会把时间复杂度变成 O(n^2)，那我不要它了，是不是就能压缩成 O(n) ?
    // 就是按照如下方式进行子问题定义：
    // dfs(i, hold) 代表我们在第 i 天，手里 (hold == true -> 持有，hold == false -> 不持有) 股票的情况下所能获得的最大利润
    // 这样可以进行递归吗？
    // 显然会发现是完全可行的，考虑：
    // 1. hold == true，那么显然的情况是，我们前一天可以是手中持有股票的 dfs(i-1, true) 或者不持有股票的 dfs(i-1, false)
    // 而如果前一天不持有股票，那么我们应该是在当天 (第 i 天) 购买了这支股票，也就是 dfs(i-1, false) + prices[i-1]
    // 所以此时的最大利润应该是：前一天手里持有股票的最大利润，和前一天手里不持有股票，而今天购买了股票的 这两种状态利润的较大值
    // 即 dfs(i, true) = max(dfs(i-1, true), dfs(i-1, false)-prices[i-1])
    // 2. hold == false，如法推理：
    // dfs(i, false) = max(dfs(i-1, false), dfs(i-1, true)+prices[i-1])
    // 按照上面的思路，就不难写出递归代码了
    // 加一个记忆化数组
    vector<vector<int>> memo(prices.size()+1, vector<int>(2, INT_MIN));
    function<int(int, bool)> dfs = [&](int i, bool hold) 
    {
        if(memo[i][hold] != INT_MIN)
        {
            return memo[i][hold];
        }
        // 边界情况：i == 1
        if(i == 1)
        {
            return (hold ? -prices[0] : 0);
        }
        // 进行递归
        if(hold)
        {
            memo[i][hold] = max(dfs(i-1, true), dfs(i-1, false)-prices[i-1]);
            return memo[i][hold];
        }
        memo[i][hold] = max(dfs(i-1, false), dfs(i-1, true)+prices[i-1]);
        return memo[i][hold];
    };
    // 全局的最大结果值
    int res = 0;
    // 遍历求解每一天的最大值即可
    for(int i = 1; i <= prices.size(); ++i)
    {
        res = max(res, dfs(i, false));
    }
    return res;
}

// 第三版：完全优化的 DP 方案
int maxProfit2DP(vector<int>& prices)
{
    vector<vector<int>> dp(prices.size()+1, vector<int>(2, 0));
    // 边界情况设定
    dp[1][true] = -prices[0];
    // 全局的最大值
    int res = 0;
    for(int i = 2; i <= prices.size(); ++i)
    {
        for(int hold = 0; hold <= 1; ++hold)
        {
            if(hold)
            {
                dp[i][true] = max(dp[i-1][true], dp[i-1][false]-prices[i-1]);
            }
            else
            {
                dp[i][false] = max(dp[i-1][false], dp[i-1][true]+prices[i-1]);
                res = max(res, dp[i][false]);
            }
        }
    }
    return res;
}

// 第四版：完全优化的 DP 方案 + 空间优化
int maxProfit2DPOpt(vector<int>& prices)
{
    vector<int> dp(2, 0);
    dp[true] = -prices[0];
    int res = 0;
    // 注意到只有 dp[true] 需要记忆原值
    int memo = 0;
    for(int i = 2; i <= prices.size(); ++i)
    {
        for(int hold = 0; hold <= 1; ++hold)
        {
            if(hold)
            {
                dp[true] = max(dp[true], memo-prices[i-1]);
            }
            else
            {
                memo = dp[false];
                dp[false] = max(dp[false], dp[true]+prices[i-1]);
                res = max(res, dp[false]);
            }
        }
    }
    return res;
}