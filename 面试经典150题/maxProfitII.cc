#include <iostream>

class Solution {
public:
    int maxProfit(vector<int>& prices) 
    {
        // 常规动态规划类题目，我们可以考虑一下如何定义状态方程
        // 我们可以把题目要我们解决的问题抽象成下面的数组：
        // dp[i][0]：代表我们在第 i 天结束时，手上不持有股票的情况下，可以获得的最大利润值
        // dp[i][1]；代表我们在第 i 天结束时，手上持有股票的情况下，可以获得的最大利润值
        // 思考一下如何进行状态递推：
        // 对于 dp[i][0]，第 i 天手上并不持有股票，那么我们前一天可能也不持有股票，或者前一天可能持有股票，但是今天卖掉了
        // 也就是：dp[i][0] = max(dp[i-1][0], dp[i-1][1]+prices[i])
        // 对于 dp[i][1]，我们可以进行类似的推理：
        // dp[i][1] = max(dp[i-1][1], dp[i-1][0]-prices[i])
        // 最后，基础情况为：
        // dp[0][0] = 0, dp[0][1] = -prices[0]
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, 0));
        dp[0][1] = -prices[0];
        for(int i = 1; i < n; ++i)
        {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1]+prices[i]);
            dp[i][1] = max(dp[i-1][1], dp[i-1][0]-prices[i]);
        }
        return max(dp[n-1][0], dp[n-1][1]);
    }
};

// 空间优化：
class Solution {
public:
    int maxProfit(vector<int>& prices) 
    {
        // 常规动态规划类题目，我们可以考虑一下如何定义状态方程
        // 我们可以把题目要我们解决的问题抽象成下面的数组：
        // dp[i][0]：代表我们在第 i 天结束时，手上不持有股票的情况下，可以获得的最大利润值
        // dp[i][1]；代表我们在第 i 天结束时，手上持有股票的情况下，可以获得的最大利润值
        // 思考一下如何进行状态递推：
        // 对于 dp[i][0]，第 i 天手上并不持有股票，那么我们前一天可能也不持有股票，或者前一天可能持有股票，但是今天卖掉了
        // 也就是：dp[i][0] = max(dp[i-1][0], dp[i-1][1]+prices[i])
        // 对于 dp[i][1]，我们可以进行类似的推理：
        // dp[i][1] = max(dp[i-1][1], dp[i-1][0]-prices[i])
        // 最后，基础情况为：
        // dp[0][0] = 0, dp[0][1] = -prices[0]
        int n = prices.size();
        // 可以把二维数组压缩成两个数据
        // vector<vector<int>> dp(n, vector<int>(2, 0));
        // dp[0][1] = -prices[0];
        int dp0 = 0, dp1 = -prices[0], tmp = dp0;
        for(int i = 1; i < n; ++i)
        {
            // dp[i][0] = max(dp[i-1][0], dp[i-1][1]+prices[i]);
            // dp[i][1] = max(dp[i-1][1], dp[i-1][0]-prices[i]);
            tmp = dp0;
            dp0 = max(dp0, dp1+prices[i]);
            dp1 = max(dp1, tmp-prices[i]);
        }
        return max(dp0, dp1);
    }
};