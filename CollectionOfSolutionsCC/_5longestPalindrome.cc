#include "Solution.h"

string Leetcode1_100::Solution::longestPalindrome(string s)
{
    // 目的是找出给定字符串 s 中最长的回文子串
    // 本题有几种不同的求解方案，写法最简便，也最容易理解的方案显然是动态规划的解法
    // 定义 dp[i][j] 代表 s 的从 i 到 j 到字符构成的子串是否是一个回文串
    // 对于所有的长度为1和2的区间，我们可以进行预先计算，判断它们是否是一个合法的回文串
    // 递推关系为
    // 对于任意一个长度为 k 的区间 dp[i][i+k-1](k > 2)
    // 如果有 (s[i] == s[i+k-1]) && (dp[i+1][i+k-2] == true)，那么 dp[i][i+k-1] = true，否则为 false
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, false));
    string res = "";
    res += s[0];
    for(int i = 0; i < n; ++i)
    {
        // 长度为1的区间一定是一个回文串
        dp[i][i] = true;
        // 头尾相等的长度为2的区间也是一个回文串
        if(i > 0)
        {
            dp[i-1][i] = s[i-1] == s[i];
            if(s[i-1] == s[i] && res.size() < 2)
            {
                res = s.substr(i-1, 2);
            }
        }
    }
    // 从小到大枚举子串长度，这样可以保证每次递推到时候对应的更小长度的串的结果都已经确定
    for(int l = 3; l <= n; ++l)
    {
        // 枚举子串的起点
        // 最大可以取到n-l，此时只有起点为n-l，终点为n-1，长度为l的子串
        for(int i = 0; i <= n-l; ++i)
        {
            // 算出对应的右端点
            int j = i + l - 1;
            // 执行递推
            if(s[i] == s[j] && dp[i+1][j-1])
            {
                dp[i][j] = true;
                if(res.size() < j-i+1)
                {
                    res = s.substr(i, j-i+1);
                }
            }
        }
    }
    return res;
}