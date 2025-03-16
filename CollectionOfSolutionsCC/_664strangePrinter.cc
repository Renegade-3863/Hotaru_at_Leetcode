#include "Solution.h"

// 第一版：不加记忆化，纯暴力 DFS
int Leetcode601_700::Soltuion::strangePrinter(string s)
{
    // 个人认为这种区间处理类型的 DP 问题是所有类型的 DP 问题中，递推方程最不好想的类型了
    // 我们依旧定义下面的子问题：
    // dfs(i, j) 代表：
    // 把区间 [i, j] 中的字符串打印出来，需要的最少打印次数
    // 那么考虑从 i 和 j 两个位置上的元素入手：
    // s[i] 与 s[j] 无非两种可能的关系：
    // 1. s[i] == s[j]
    // 此时我们完全可以考虑把 s[i] 和 s[j] 一起打印出来，这样的操作总次数就是 
    // 1+dfs(i+1, j-1)
    // 但这种想法实际上是错误的：
    // 为什么不能考虑把 s[i]、s[j] 和区间 [i+1, j-1] 中的那些也等于 s[i] 的字符一起打印？这样不是步数更少吗？
    // 自然是可以的
    // 所以我们退一步考虑：
    // 把区间 [i, j-1] 中的所有字符先打印出来，再考虑把 s[j] 在打印 s[i] 对应的那个子序列的时候顺便一起打印出来
    // 或者把区间 [i+1, j] 中的所有字符先打印出来，再考虑把 s[i] 在打印 s[j] 对应的那个子序列的时候顺便一起打印出来
    // 但依然会有人有疑问：
    // 这样做为什么是最优的？
    // 换句话说，为什么把一串连续的字符一起打印出来，会比分开打印它们更优？
    // 其实简单点来想，并不那么难理解：
    // 就是：一遍可以做完的事，没必要分开两次做
    // 中间要插入其它字符，那是插入字符的事，和我本次打印没有任何关系
    // 总结：dfs(i, j) = min(dfs(i, j-1), dfs(i+1, j))
    // 2. s[i] != s[j]
    // 此时我们就没法像上面那样进行 "顺带" 打印了
    // 只能拆分子问题，考虑中间取一个分割点 k
    // 分别打印区间 [i, k] 和区间 [k+1, j]
    // 故此时：
    // dfs(i, j) = for all k from i to j-1：
    // min(dfs(i, k)+dfs(k+1, j))
    // 最后，我们要求的最大子问题就是：
    // dfs(0, s.size()-1)
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 考虑最小子问题：
        // i == j，那么我们可以直接返回 1，一个字符，打印一次即可
        if(i == j)
        {
            return 1;
        }
        // 其它一般情况
        // 情况1.
        if(s[i] == s[j])
        {
            return min(dfs(i, j-1), dfs(i+1, j));
        }
        // 情况2.
        int res = 0x3f3f3f3f;
        for(int k = i; k < j; ++k)
        {
            res = min(res, dfs(i, k)+dfs(k+1, j));
        }
        return res;
    };
    return dfs(0, s.size()-1);
}

// 第二版：给 DFS 加上记忆化数组，依然 TLE。。
int strangePrinter(string s)
{
    // 记忆化数组
    int n = s.size();
    vector<vector<int>> memo(n, vector<int>(n, -1));
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 考虑最小子问题：
        // i == j，那么我们可以直接返回 1，一个字符，打印一次即可
        if(i == j)
        {
            return 1;
        }
        // 加上记忆化
        if(memo[i][j] != -1)
        {
            return memo[i][j];
        }
        // 其它一般情况
        // 情况1.
        if(s[i] == s[j])
        {
            return min(dfs(i, j-1), dfs(i+1, j));
        }
        // 情况2.
        int res = 0x3f3f3f3f;
        for(int k = i; k < j; ++k)
        {
            res = min(res, dfs(i, k)+dfs(k+1, j));
        }
        return res;
    };
    return dfs(0, s.size()-1);
}

// 第三版：把 DFS 换成自底向上的 DP 方法
int strangePrinter(string s)
{
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0x3f3f3f3f));
    // 初始化边界情况
    for(int i = 0; i < n; ++i)
    {
        dp[i][i] = 1;
    }
    // 之后就是区间遍历了
    // 注意到：
    // 任何一个区间 [i, j]，会用到的都是那些长度比它更短的区间，所以我们只需要按区间长度从短到长进行遍历即可
    for(int len = 2; len <= n; ++len)
    {
        for(int i = 0; i <= n-len; ++i)
        {
            int j = i+len-1;
            // 情况1.
            if(s[i] == s[j])
            {
                dp[i][j] = min(dp[i+1][j], dp[i][j-1]);
            }
            else
            {
                int minimum = INT_MAX;
                for(int k = i; k < j; ++k)
                {
                    minimum = min(minimum, dp[i][k]+dp[k+1][j]);
                }
                dp[i][j] = minimum;
            }
        }
    }
    return dp[0][n-1];
}