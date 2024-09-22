#include "Solution.h"

// 第一版：单纯 DFS，不加记忆化，纯纯鸡蛋碰石头，绝对超时的解法
bool Leetcode1_100::Solution::isScramble(string s1, string s2)
{
    // 看到这道题目，基本就可以确定本质是要进行 DFS+记忆化/动态规划 的策略了
    // 不过直接思考动态规划的状态转移方程可能比较困难，我们从最基本的 DFS 策略开始切入
    // 定义一个递归的回调函数 dfs
    // 返回值代表的是，s1 的 [l1, r1] 部分和 s2 的 [l2, r2] 部分是否能够构成扰乱字符串
    function<bool(int, int, int, int)> dfs = [&](int l1, int r1, int l2, int r2)
    {
        // 基本情况：如果两个串的长度为1
        // 那么我们可以直接返回 s1[i] == s2[i]，也就是两个单一字符的字符串是否相等来进行判断
        if(r1 == l1)
        {
            return s1[l1] == s2[l2];
        }
        // 本函数的返回值
        bool res = false;
        // 1. 遍历整个区间中所有可能的下标尝试进行切分
        for(int k = 0; k < r1-l1; ++k)
        {
            // 切分成的是 [l1, k]，[k+1，r1] 两部分，根据这两个区间长度到 s2 中找对应同长度的子串
            // 先考虑不交换
            res = res | (dfs(l1, l1+k, l2, l2+k) && dfs(l1+k+1, r1, l2+k+1, r2));
            // 再考虑交换
            res = res | (dfs(l1, l1+k, r2-k, r2) && dfs(l1+k+1, r1, l2, r2-k-1));
        }
        return res;
    };
    int n = s1.size();
    return dfs(0, n-1, 0, n-1);
}

// 第二版：第一版的基础上增加了极其简单粗暴的四维数组记忆化，勉强通过，只击败了 5%
bool isScrambleMemo(string s1, string s2)
{
    // 看到这道题目，基本就可以确定本质是要进行 DFS+记忆化/动态规划 的策略了
    // 不过直接思考动态规划的状态转移方程可能比较困难，我们从最基本的 DFS 策略开始切入
    // 定义一个递归的回调函数 dfs
    // 返回值代表的是，s1 的 [l1, r1] 部分和 s2 的 [l2, r2] 部分是否能够构成扰乱字符串
    int n = s1.size();
    // 添加一个记忆化数组，用于记录已经检查过的情况
    vector<vector<vector<vector<int>>>> memo(n, vector<vector<vector<int>>>(n, vector<vector<int>>(n, vector<int>(n, -1))));
    function<bool(int, int, int, int)> dfs = [&](int l1, int r1, int l2, int r2)
    {
        if(memo[l1][r1][l2][r2] == 0 || memo[l1][r1][l2][r2] == 1)
        {
            return memo[l1][r1][l2][r2] == 1;
        }
        // 基本情况：如果两个串的长度为1
        // 那么我们可以直接返回 s1[i] == s2[i]，也就是两个单一字符的字符串是否相等来进行判断
        if(r1 == l1)
        {
            return s1[l1] == s2[l2];
        }
        // 本函数的返回值
        bool res = false;
        // 1. 遍历整个区间中所有可能的下标尝试进行切分
        for(int k = 0; k < r1-l1; ++k)
        {
            // 切分成的是 [l1, k]，[k+1，r1] 两部分，根据这两个区间长度到 s2 中找对应同长度的子串
            // 先考虑不交换
            res = res | (dfs(l1, l1+k, l2, l2+k) && dfs(l1+k+1, r1, l2+k+1, r2));
            // 再考虑交换
            res = res | (dfs(l1, l1+k, r2-k, r2) && dfs(l1+k+1, r1, l2, r2-k-1));
        }
        memo[l1][r1][l2][r2] = res ? 1 : 0;
        return res;
    };
    return dfs(0, n-1, 0, n-1);
}

// 第三版：DFS + 记忆化优化为三维区间 DP
bool isScrambleDP(string s1, string s2)
{
    // 根据上面两版的深搜状态定义，我们可以如法定义 dp 数组的含义
    // dp[l1][r1][l2][r2] 代表 s1 的 [l1..r1] 区间构成的子串和 s2 的 [l2..r2] 区间构成的子串是否能够形成一对扰乱字符串
    // 不过，注意到这四个维度之间其实有一些内部联系
    // 由于我们要求的是一对扰乱字符串必须长度相同，因而实际上有：r1-l1 == r2-l2
    // 因此，我们不难将这个数组压缩成三维：
    // dp[i][j][len] 代表 s1 的 [i..i+len-1] 区间构成的子串和 s2 的 [j..j+len-1] 区间构成的子串是否能够形成一对扰乱字符串
    // 观察到本题的子结构是由 长度更小的区间构成的，因而我们可以遵循区间 DP 的一贯方式，按最外层区间长度，向内枚举两个子串开始下标的形式进行递推
    int n = s1.size();
    // 由于长度值最大要取到 n，所以我们最后一维的长度是 n+1
    vector<vector<vector<bool>>> dp(n, vector<vector<bool>>(n, vector<bool>(n+1, false)));
    // 定义边界情况
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            dp[i][j][1] = s1[i] == s2[j];
        }
    } 
    // 执行实际的递推过程
    for(int len = 2; len <= n; ++len)
    {
        for(int i = 0; i+len-1 < n; ++i)
        {
            for(int j = 0; j+len-1 < n; ++j)
            {
                // 内部需要枚举分割点
                for(int k = 0; k < len-1; ++k)
                {
                    // 对应不对调顺序的情况
                    dp[i][j][len] = dp[i][j][len] || (dp[i][j][k+1] && dp[i+k+1][j+k+1][len-k-1]);
                    // 对应对调顺序的情况
                    dp[i][j][len] = dp[i][j][len] || (dp[i][j+len-1-k][k+1] && dp[i+k+1][j][len-k-1]);
                }
            }
        }
    }
    // 定义上，这个值就是答案
    return dp[0][0][n];
}