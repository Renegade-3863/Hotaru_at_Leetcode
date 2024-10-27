#include "Solution.h"

// 第一版：暴力 DFS，不加记忆化，直接 TLE
int Leetcode301_400::Solution::maxProfit5(vector<int>& prices)
{
    // 股票系列，经典的动态规划问题
    // 依然是先从自顶向下的递归角度考虑问题，这样比较简单
    // 定义如下子问题：
    // dfs(i, hold, frozen)
    // 代表前 i 天进行股票购买，第 i 天手上 (hold == true -> 持有，hold == false -> 不持有) 股票，并且处于 (frozen == false -> 不冷冻，frozen == true -> 冷冻) 状态
    // 下，能获取的最大收益值
    // 之后考虑如何进行递推
    // 无非四种可能：
    // 1. dfs(i, true, true)
    // 此时说明我们手上持有股票，并且处于冷冻期
    // 那么对于更小的子问题，很显然有：
    // dfs(i, true, true) = max(dfs(i-1, false, false)-prices[i-1], dfs(i-1, true, true));
    // 即：等于：前 i-1 天进行股票购买，第 i-1 天手上不持有股票，并且不处于冷冻期、第 i-1 天手上持有股票，并且处于冷冻期两种情况下，前 i 天的子问题所能拿到的最大利润
    // 2. dfs(i, true, false) = 0 -> 之所以赋值为零，是因为这种情况根本不可能发生，同时我们也不想让它干扰其它子问题的结果，所以我们直接返回0
    // 3. dfs(i, false, true)
    // 此时说明我们手上不持有股票，并且处于冷冻期
    // 那么对于更小的子问题，很显然有：
    // dfs(i, false, true) = dfs(i-1, true, true)+prices[i-1]
    // 这里不难理解，因为如果当前第 i 天处于冷冻期，并且手上不持有股票，那么一定是前一天手上还持有着股票，今天卖掉了，没有任何其它可能(因为冷冻期只持续一天)
    // 4. dfs(i, false, false)
    // 此时说明我们手上不持有股票，并且不处于冷冻期
    // 那么对于更小的子问题，很显然有：
    // dfs(i, false, false) = max(dfs(i-1, false, false), dfs(i-1, false, true))
    // 即：等于：前 i-1 天进行股票购买，第 i-1 天手上不持有股票，并且不处于冷冻期、第 i-1 天手上不持有股票，但是处于冷冻期两种情况下，前 i 天的子问题所能拿到的最大利润
    // 明确了以上四种子问题的递推模式，我们写代码就不难了
    function<int(int, bool, bool)> dfs = [&](int i, bool hold, bool frozen)
    {
        // 先明确递归的结束点，最小的子问题
        // i == 1，即只考虑第一天购买股票的情况
        if(i == 1)
        {
            // 分 hold 和 frozen 的组合情况决定要返回什么结果
            // 否则，直接返回 0 即可
            return hold ? -prices[0] : 0;
        }
        // 一般情况
        // 根据上面的四种情况(实际只会用到三种)进行讨论即可
        if(hold)
        {
            return frozen ? max(dfs(i-1, false, false)-prices[i-1], dfs(i-1, true, true)) : 0;
        }
        return frozen ? dfs(i-1, true, true)+prices[i-1] : max(dfs(i-1, false, false), dfs(i-1, false, true));
    };
    // 最终的结果是下面值的最大者：
    // dfs(prices.size(), true, true), dfs(prices.size(), false, false), dfs(prices.size(), false, true)
    // 实际上，不难看出 dfs(prices.size(), true, true) 本身不可能成为最终的答案
    return max(dfs(prices.size(), false, false), dfs(prices.size(), false, true));
}

// 第二版：DFS + 记忆化
int maxProfit5(vector<int>& prices)
{
    // 股票系列，经典的动态规划问题
    // 依然是先从自顶向下的递归角度考虑问题，这样比较简单
    // 定义如下子问题：
    // dfs(i, hold, frozen)
    // 代表前 i 天进行股票购买，第 i 天手上 (hold == true -> 持有，hold == false -> 不持有) 股票，并且处于 (frozen == false -> 不冷冻，frozen == true -> 冷冻) 状态
    // 下，能获取的最大收益值
    // 之后考虑如何进行递推
    // 无非四种可能：
    // 1. dfs(i, true, true)
    // 此时说明我们手上持有股票，并且处于冷冻期
    // 那么对于更小的子问题，很显然有：
    // dfs(i, true, true) = max(dfs(i-1, false, false)-prices[i-1], dfs(i-1, true, true));
    // 即：等于：前 i-1 天进行股票购买，第 i-1 天手上不持有股票，并且不处于冷冻期、第 i-1 天手上持有股票，并且处于冷冻期两种情况下，前 i 天的子问题所能拿到的最大利润
    // 2. dfs(i, true, false) = 0 -> 之所以赋值为零，是因为这种情况根本不可能发生，同时我们也不想让它干扰其它子问题的结果，所以我们直接返回0
    // 3. dfs(i, false, true)
    // 此时说明我们手上不持有股票，并且处于冷冻期
    // 那么对于更小的子问题，很显然有：
    // dfs(i, false, true) = dfs(i-1, true, true)+prices[i-1]
    // 这里不难理解，因为如果当前第 i 天处于冷冻期，并且手上不持有股票，那么一定是前一天手上还持有着股票，今天卖掉了，没有任何其它可能(因为冷冻期只持续一天)
    // 4. dfs(i, false, false)
    // 此时说明我们手上不持有股票，并且不处于冷冻期
    // 那么对于更小的子问题，很显然有：
    // dfs(i, false, false) = max(dfs(i-1, false, false), dfs(i-1, false, true))
    // 即：等于：前 i-1 天进行股票购买，第 i-1 天手上不持有股票，并且不处于冷冻期、第 i-1 天手上不持有股票，但是处于冷冻期两种情况下，前 i 天的子问题所能拿到的最大利润
    // 明确了以上四种子问题的递推模式，我们写代码就不难了
    // 添加一个记忆化数组
    vector<vector<vector<int>>> memo(prices.size(), vector<vector<int>>(2, vector<int>(2, -1)));
    function<int(int, bool, bool)> dfs = [&](int i, bool hold, bool frozen)
    {
        if(memo[i-1][hold][frozen] != -1)
        {
            return memo[i-1][hold][frozen];
        }
        // 先明确递归的结束点，最小的子问题
        // i == 1，即只考虑第一天购买股票的情况
        if(i == 1)
        {
            // 分 hold 和 frozen 的组合情况决定要返回什么结果
            // 否则，直接返回 0 即可
            memo[0][hold][frozen] = hold ? -prices[0] : 0;
            return memo[0][hold][frozen];
        }
        // 一般情况
        // 根据上面的四种情况(实际只会用到三种)进行讨论即可
        if(hold)
        {
            memo[i-1][hold][frozen] = frozen ? max(dfs(i-1, false, false)-prices[i-1], dfs(i-1, true, true)) : 0;
            return memo[i-1][hold][frozen];
        }
        memo[i-1][hold][frozen] = frozen ? dfs(i-1, true, true)+prices[i-1] : max(dfs(i-1, false, false), dfs(i-1, false, true));
        return memo[i-1][hold][frozen];
    };
    // 最终的结果是下面值的最大者：
    // dfs(prices.size(), true, true), dfs(prices.size(), false, false), dfs(prices.size(), false, true)
    // 实际上，不难看出 dfs(prices.size(), true, true) 本身不可能成为最终的答案
    return max(dfs(prices.size(), false, false), dfs(prices.size(), false, true));
}

// 第三版：转换成自底向上的 DP 方案
int maxProfit5(vector<int>& prices)
{
    int n = prices.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(2, 0)));
    // 边界情况设定
    dp[0][true][true] = -prices[0];
    // 进行递推
    for(int i = 1; i < n; ++i)
    {
        dp[i][true][true] = max(dp[i-1][false][false]-prices[i], dp[i-1][true][true]);
        // dp[i][true][false] = 0;
        dp[i][false][true] = dp[i-1][true][true]+prices[i];
        dp[i][false][false] = max(dp[i-1][false][false], dp[i-1][false][true]);
    }
    // 返回结果即可
    return max(dp[n-1][false][false], dp[n-1][false][true]);
}


// 第四版：DP + 空间优化
int maxProfit5(vector<int>& prices)
{
    int n = prices.size();
    int dp0 = 0, dp1 = 0, dp2 = 0;
    dp0 = -prices[0];
    for(int i = 1; i < n; ++i)
    {
        int tmp1 = dp0, tmp2 = dp1, tmp3 = dp2;
        dp0 = max(dp2-prices[i], dp0);
        dp1 = tmp1+prices[i];
        dp2 = max(tmp3, tmp2);
    }
    return max(dp1, dp2);
}