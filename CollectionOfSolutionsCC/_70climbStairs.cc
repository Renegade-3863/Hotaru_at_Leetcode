#include "Solution.h"

int Leetcode1_100::Solution::climbStairs(int n)
{
    // 不想多说，最最基础的 DP 题目
    // 递推关系为：到达某一级的方法数量等于它的上一步，也就是到达 n-1 级和 n-2 级的方法之和
    // 不空间优化：
#if 0
    if(n == 1)
    {
        return 1;
    }
    vector<int> dp(n, 0);
    // 边界情况
    dp[0] = 1; dp[1] = 2;
    // 递推过程
    for(int i = 2; i < n; ++i)
    {
        dp[i] = dp[i-1]+dp[i-2];
    }
    return dp[n-1];
#endif
    // 空间优化：
    if(n == 1)
    {
        return 1;
    }
    int dp0 = 1, dp1 = 2;
    for(int i = 2; i < n; ++i)
    {
        int tmp = dp1;
        dp1 = dp0+dp1;
        dp0 = tmp;
    }
    return dp1;
}