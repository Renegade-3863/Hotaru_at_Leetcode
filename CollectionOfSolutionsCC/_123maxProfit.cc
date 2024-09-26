#include "Solution.h"

int Leetcode101_200::Solution::maxProfit3(vector<int>& prices)
{
    // 具体的四个版本的逻辑分析见 121 题解析，这里直接复制 121 题的第四版通用空间压缩代码改了改参数。。。
    // 两个记忆化的临时变量
    int memo0 = 0, memo1 = 0;
    int res = 0, n = prices.size();
    // 其实只有四个变量
    vector<vector<int>> dp(2, vector<int>(3, 0));
    // 初始情况，对应 i == 1 的情况
    for(int hold = 0; hold < 2; ++hold)
    {
        for(int cnt = 0; cnt <= 2; ++cnt)
        {
            dp[hold][cnt] = (hold ? -prices[0] : 0);
        }
    }
    // 初始情况，对应 cnt == 0 的情况，鉴于第三版中的经验，初始情况下我们不需要进行任何计算了
    // 主体进行递推
    for(int i = 2; i <= n; ++i)
    {
        memo0 = dp[true][0];
        memo1 = dp[false][1];
        dp[true][0] = max(dp[true][0], -prices[i-1]);
        // 一个来自题解的小优化，由于本题我们至多有必要检查进行 n 次交易的结果(多于这个值的话我们相当于有些天一天内进行了多次交易，这显然是没有必要的)
        // 故循环结束条件这里用了 min(n, k) 做限制
        for(int cnt = 1; cnt <= 2; ++cnt)
        {
            for(int hold = 0; hold < 2; ++hold)
            {
                if(hold)
                {
                    memo0 = dp[true][cnt];
                    dp[hold][cnt] = max(dp[true][cnt], memo1-prices[i-1]);
                }
                else
                {
                    memo1 = dp[false][cnt];
                    dp[hold][cnt] = max(memo0+prices[i-1], dp[false][cnt]);
                    res = max(res, dp[hold][cnt]);
                }
            }
        }
    }
    return res;
}