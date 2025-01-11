#include "Solution.h"

// 第一版：暴力 DFS，TLE
int Leetcode501_600::Soltuion::longestPalindromeSubseq(string s)
{
    // 经典的 DP 问题，我们先从 DFS 角度入手
    // 定义下面的 DFS 子问题：
    // dfs(i, j) 代表的是 s[i..j] 构成的子串中最长的回文子序列的长度
    // 至于为什么不用一维定义，我们这里简单做一下说明：
    // 一维的子问题定义，我们无非能想到下面几种：
    // 1. 状态式：
    // 定义 dfs(i) 为：子序列结尾于 s[i] 的所有子序列中最长的那一个的长度
    // 那么我们会发现没法递推更大的子问题：因为我们不知道这个所谓的 "最长子序列" 开始的位置在哪
    // 所以我们依然需要一个近似 O(n) 的时间来定位出 s[i] 对应的那个对称字符的位置
    // 而且这个定位过程也不好做，因为 s[i] 的左侧可能有很多个 s[i] 字符，我们不能很简单地定位到它对应的实际上是哪个字符
    // 2. 区间式：
    // 定义 dfs(i) 为：前 i 个字符组成的子序列中，最长的回文子序列的长度
    // 不难发现我们会遇到和 1 类似的问题：不知道最长子序列开始的位置在哪
    // 这种基于 "信息缺失" 的情况下，我们就应该想到需要通过补充维度来扩充子问题持有的信息量
    // 对于这道题，我们就可以通过引入 "左边界" 来实现
    // 修改子问题的定义：
    // dfs(i, j) 为：区间 [i, j] 之间的字符构成的子序列中，最长回文子序列的长度
    // 这样我们就有了一种递推子问题的方法：
    // 对于 dfs(i, j)，我们可以考察 s[i] 和 s[j]
    // 如果 s[i] == s[j]，那么我们可以把 s[i] 和 s[j] 拼接到 dfs(i+1, j-1) 得出的那个最长的回文子序列上
    // 也就是：dfs(i, j) = 2+dfs(i+1, j-1)
    // 否则，s[i] != s[j]，那么我们只能选择其中一侧的子问题来递推
    // 也就是：dfs(i, j) = max(dfs(i, j-1), dfs(i+1, j))
    // 换句话说，区间 [i..j] 中最长的回文子序列长度，等于区间 [i..j-1] 中最长的回文子序列，和区间 [i+1..j] 中最长的回文子序列中，更长的那一个的长度
    // 补充一点，其实在 s[i] == s[j] 的时候，上面这两个子区间的结果也是存在的，只不过它们都一定不会长于 2+dfs(i+1, j-1)，所以我们就直接用 2+dfs(i+1, j-1) 来代替了
    // 思路构建完成，写代码就很简单了
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 考虑 dfs 的基本情况：i == j
        // 此时我们返回 1 即可，长度为 1 的子串本身就是一个回文串
        if(i == j)
        {
            return 1;
        }
        // 如果 i > j，那么返回 0
        // 因为子串不存在
        if(i > j)
        {
            return 0;
        }
        // 其它情况下，我们按照上面的逻辑进行递推即可
        if(s[i] == s[j])
        {
            return 2+dfs(i+1, j-1);
        }
        return max(dfs(i+1, j), dfs(i, j-1));
    };
    // 最后的结果就是 dfs(0, s.size()-1)
    return dfs(0, s.size()-1);
}

// 第二版：给 DFS 添加记忆化数组
int longestPalindromeSubseq(string s)
{
    // 补充一个记忆化哈希表 memo
    int n = s.size();
    // 初始化为 -1，因为合法的长度值不会是 -1，我们可以通过这个条件来判断是否检查过了某个子问题
    vector<vector<int>> memo(n, vector<int>(n, -1));
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 考虑 dfs 的基本情况：i == j
        // 此时我们返回 1 即可，长度为 1 的子串本身就是一个回文串
        if(i == j)
        {
            return 1;
        }
        // 如果 i > j，那么返回 0
        // 因为子串不存在
        if(i > j)
        {
            return 0;
        }
        // 记忆化处理
        if(memo[i][j] != -1)
        {
            return memo[i][j];
        }
        // 其它情况下，我们按照上面的逻辑进行递推即可
        if(s[i] == s[j])
        {
            memo[i][j] = 2+dfs(i+1, j-1);
            return memo[i][j];
        }
        memo[i][j] = max(dfs(i+1, j), dfs(i, j-1));
        return memo[i][j];
    };
    // 最后的结果就是 dfs(0, s.size()-1)
    return dfs(0, n-1);
}

// 第三版：把 DFS 改成自底向上的 DP 方法
int longestPalindromeSubseq(string s)
{
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    // 进行初始化，主要初始化的是长度为 1 的那些子串
    for(int i = 0; i < n; ++i)
    {
        dp[i][i] = 1;
    }
    // 之后是区间 DP 常用的遍历方式
    // 注意一点即可：大区间必须在它所有求解需要的小区间被计算完成后才被求解
    // 枚举区间长度
    for(int len = 2; len <= n; ++len)
    {
        // 枚举区间左端点
        for(int i = 0; i <= n-len; ++i)
        {
            // 计算出右端点
            int j = i+len-1;
            // 正常递推
            if(s[i] == s[j])
            {
                dp[i][j] = 2+dp[i+1][j-1];
            }
            else
            {
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
            }
        }
    }
    // 返回结果
    return dp[0][n-1];
}