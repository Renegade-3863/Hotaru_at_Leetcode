#include "Solution.h"

vector<int> Leetcode301_400::Solution::countBits(int n)
{
    // 又是一个比较离谱的动态规划类问题，可以说发现了递推关系就很好做，否则，看一天也不一定能想出答案。。。
    // 这题就不从自顶向下开始入手了，直接给出 DP 解法。。。
    // 定义 dp[i] 代表数字 i 二进制表示中 1 的个数
    // 那么如果 i 是一个偶数，那么它的 1 的个数很显然和 i>>1 (i/2) 是一样的
    // 所以 dp[i] = dp[i>>1]
    // 如果 i 是一个奇数，那么它很显然是通过比它小1的那个偶数在最低位添加一个1得来的
    // 所以 dp[i] = dp[i-1]+1
    // 以此类推即可
    vector<int> dp(n+1, 0);
    for(int i = 1; i <= n; ++i)
    {
        dp[i] = i%2 ? dp[i-1]+1 : dp[i>>1];
    }
    return dp;
}