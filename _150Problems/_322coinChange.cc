class Solution
{
public:
    int coinChange(vector<int>& coins, int amount)
    {
        // 经典的 DP 问题，考虑如何进行递推
        // 定义下面的 dp 表达式
        // dp[i][j] 代表使用前 i 种硬币，凑出面额 j 所需的最少硬币个数
        // 递推公式：
        // 使用一次第 i 种硬币，剩下 j-coins[i-1] 的面额，还可以用前 i 种硬币来凑
        // 也就是 
        // dp[i][j] = dp[i][j-coins[i-1]]+1
        // 或者我们不使用第 i 种硬币
        // dp[i][j] = dp[i-1][j]
        // 两种情况取较小值即可
        int n = coins.size();
        vector<vector<int>> dp(n+1, vector<int>(amount+1, 0));
        dp[0][0] = 0;
        for(int j = 1; j <= amount; ++j)
        {
            if(j % coins[0] == 0)
            {
                dp[1][j] = j / coins[0];
            }
            else
            {
                // 无法构成
                dp[1][j] = -1;
            }
        }
        // 正常递推
        for(int i = 2; i <= n; ++i)
        {
            for(int j = 1; j <= amount; ++j)
            {
                // 对于 dp[i][j]，我们有两种选择
                // 1. 不使用 coins[i-1]
                dp[i][j] = dp[i-1][j];
                // 2. 使用 coins[i-1]
                if(j >= coins[i-1] && dp[i][j-coins[i-1]] != -1)
                {
                    // 注意，使用了一次 coins[i-1]，所以要再加一
                    dp[i][j] = dp[i][j] == -1 ? dp[i][j-coins[i-1]]+1 : min(dp[i][j], dp[i][j-coins[i-1]]+1);
                }
            }
        }
        return dp[n][amount];
    }
};