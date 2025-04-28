#include "Solution.h"

int Leetcode701_800::Soltuion::countPalindromicSubsequences(string s)
{
    // 一看就知道是 DP 类问题的一道题
    // 我们从 DFS 的角度来考虑这个问题
    // 定义下面的子问题：
    // dfs(i, j) 代表 (i, j) 区间的不同回文子序列个数 
    // 考虑如何进行递推
    // 如果 s[i] == s[j]
    const int mod = 1e9+7, n = s.size();
    int dp[n][n];

    memset(dp, 0, sizeof dp);
    for(int i = 0; i < n; ++i)
    {
        dp[i][i] = 1;
    }

    for(int len = 2; len <= n; ++len)
    {
        for(int i = 0; i+len <= n; ++i)
        {
            int j = i+len-1;
            if(s[i] == s[j])
            {
                int l = i+1, r = j-1;
                while(l <= r && s[l] != s[i])
                {
                    ++l;
                }
                while(l <= r && s[r] != s[i])
                {
                    --r;
                }
                dp[i][j] = dp[i+1][j-1] << 1;
                if(l > r)
                {
                    dp[i][j] += 2;
                }
                else if(l == r)
                {
                    dp[i][j] += 1;
                }
                else
                {
                    dp[i][j] -= dp[l+1][r-1];
                }
            }
            else
            {
                dp[i][j] = dp[i+1][j]+dp[i][j-1]-dp[i+1][j-1];
            }
            dp[i][j] = dp[i][j] >= 0 ? dp[i][j] % mod : dp[i][j]+mod;
        }
    }
    return dp[0][n-1];
}