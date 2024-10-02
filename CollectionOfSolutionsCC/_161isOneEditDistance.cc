#include "Solution.h"

// 第一版：傻瓜式 DP，不做空间优化，炸内存了，不过个人认为这个方案可拓展性更高，可以拓展到 经过 k 次修改的情况，至于空间优化，做不出来了。。。
bool Leetcode101_200::Solution::isOneEditDistance(string s, string t)
{
        // 阉割版的编辑距离，只要求检查两个字符串是否可以通过一次编辑互相转化
        // 我们直接写就行
        int m = s.size(), n = t.size();
        // 依旧是动态规划
        // dp[i][j][k] 代表 s 的前 i 个字符组成的子串是否能够通过 1 次编辑得到 t 的前 j 个字符组成的子串
        // 那么我们最后要求的就是 dp[m][n][1]
        // 递推关系：
        // dp[i][j][k] = dp[i-1][j][k-1] (最后一次是把 s[i-1] 删除)
        //               || dp[i][j-1][k-1] (最后一次是往 s 中插入了 t[j-1] 这个字符)
        //               || dp[i-1][j-1][k] (最后一次是不做任何修改，这一条件需要 s[i-1] == t[j-1])
        //               || dp[i-1][j-1][k-1] (最后一次是把 s[i-1] 直接替换成 t[j-1])
        vector<vector<vector<bool>>> dp(m+1, vector<vector<bool>>(n+1, vector<bool>(2, false)));
        // 基础情况
        // dp[0][0][0] = true
        dp[0][0][0] = true;
        if(m >= 1)
        {
            dp[1][0][1] = true;
        }
        if(n >= 1)
        {
            dp[0][1][1] = true;
        }
        // 进行递推
        for(int i = 1; i <= m; ++i)
        {
            for(int j = 1; j <= n; ++j)
            {
                dp[i][j][0] = s[i-1] == t[j-1] && dp[i-1][j-1][0];
                dp[i][j][1] = dp[i-1][j][0] || dp[i][j-1][0] || dp[i-1][j-1][0];
                if(s[i-1] == t[j-1])
                {
                    dp[i][j][1] = dp[i-1][j][0] || dp[i][j-1][0] || dp[i-1][j-1][1];
                }
            }
        }
        return dp[m][n][1];
}