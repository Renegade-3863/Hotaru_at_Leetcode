#include "Solution.h"

int Leetcode501_600::Soltuion::minDistance(string word1, string word2)
{
    // 说实话，这道题如果不告诉我，乍一看还真看不出来这道题和最长公共子序列的关系
    // 不过依然是正难则反
    // 与其说我们是在找 "最少的删除次数"
    // 不如说我们是在找 "两个字符串的最长公共子序列"
    // 那么这道题就很明显是一个 DP 类问题了
    // 回忆这道题的解决方案，我们用的是下面的 DP 递推式：
    // dp[i][j] 代表 "word1 的前 i 个字符形成的子串和 word2 的前 j 个字符形成的子串之间的最长公共子序列长度"
    // 那么我们可以从下面几种情况推理出 dp[i][j] 的解
    // 如果 word1[i-1] == word2[j-1]，那么我们可以把 dp[i-1][j-1] 的结果统计到 dp[i][j] 中
    // 同时其它任何情况都不可能比 dp[i-1][j-1]+1 长
    // 如果 word1[i-1] != word2[j-1]，那么我们只有两种选择
    // 1. 不考虑 word1[i-1]，这样的话，就只考虑 dp[i-1][j]，即：word1 的前 i-1 个字符形成的子串和 word2 的前 j 个字符形成的子串之间的最长公共子序列长度
    // 2. 不考虑 word2[j-1]，这样的话，就只考虑 dp[i][j-1]
    // 情况 1 和 2 的最长结果就是最后的结果
    int m = word1.size(), n = word2.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    // 初始化，dp[0][0] 为 0，两个长度为 0 的字符串的公共子序列的长度很明显也是 0
    // 对于 dp[i][0] 和 dp[0][j] 也是如此
    for(int i = 1; i <= m; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            if(word1[i-1] == word2[j-1])
            {
                dp[i][j] = dp[i-1][j-1]+1;
            }
            else
            {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return m+n-(2*dp[m][n]);
}

// 二维压缩到一维的解法就不写了 (懒～)