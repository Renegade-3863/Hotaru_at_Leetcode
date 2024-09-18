#include "Solution.h"

int Leetcode1_100::Solution::jump(vector<int>& nums)
{
    // 给定一组可跳跃长度的记录集合，要求我们计算出到达 nums[n-1] 的最小跳跃次数
    // 感觉可以使用类似贪心的方法进行推导
    // 就是说，我们用一个额外的数组，记录到达每个下标所需的最少跳跃次数
    // 然后从下标 0 开始，按顺序更新所有可能到达的结点的最小步数即可 (利用类似图算法中的边的松弛操作)
    int n = nums.size();
    vector<int> dp(n, n+1);
    dp[0] = 0;
    for(int i = 0; i < n; ++i)
    {
        // 把所有可达的下标位置都执行松弛操作即可
        for(int j = i; j <= nums[i] && j < n; ++j)
        {
            dp[j] = min(dp[i]+1, dp[j]);
        }
    }
    return dp[n-1];
}