#include "Solution.h"

// 第一版：暴力 DFS，直接 TLE
int Leetcode301_400::Solution::integerBreak(int n)
{
    // 观察题目的要求，感觉和动态规划里矩阵乘法的那道题有些类似，所以考虑使用 DP 的解法
    // 我们还是先从自顶向下的 DFS 角度考虑这个问题
    // 定义一个递归子问题结构
    // dfs(i, k) 代表把 i 这个数进行拆分，拆成 k 个数的和，可以拆出来，得到最大乘积的方案的结果
    // 观察我们的问题本身，如果把这个数看成是一堆分立的1
    // 问题就更加明朗了
    // 那么如何求解 dfs(i, k) 呢？
    // 比较明显的是：我们可以枚举最后一次拆出来的数值，并进行递归
    // 最后一次拆出来一个 1:
    // 结果是 1*dfs(i-1, k-1)
    // 最后一次拆出来一个 2:
    // 结果是 2*dfs(i-2, k-1)
    // 之后是 3*dfs(i-3, k-1)
    // 以此类推。。。
    // 这些值中最大的那一个就是我们最后需要的拆解方案
    // 而对于全局的这个 n，我们要做的就是遍历所有可能的 k 值(注意，一个整数 n 最多拆成 n 个 1 相加，不可能再多了)
    function<int(int, int)> dfs = [&](int i, int k) -> int
    {
        // 递归的基本情况是：k == 1
        // 此时我们只需要返回 i 本身即可，因为我们要求是只分成一份，就是这个数本身
        if(k == 1)
        {
            return i;
        }
        int res = 0;
        for(int j = 1; j < i; ++j)
        {
            res = max(res, j*dfs(i-j, k-1));
        }
        return res;
    };
    // 循环调用即可
    int ans = 0;
    for(int k = 2; k <= n; ++k)
    {
        ans = max(ans, dfs(n, k));
    }
    return ans;
}

// 第二版：尝试给 DFS 加上记忆化加速，极限可通过
int integerBreak(int n)
{
    // 观察题目的要求，感觉和动态规划里矩阵乘法的那道题有些类似，所以考虑使用 DP 的解法
    // 我们还是先从自顶向下的 DFS 角度考虑这个问题
    // 定义一个递归子问题结构
    // dfs(i, k) 代表把 i 这个数进行拆分，拆成 k 个数的和，可以拆出来，得到最大乘积的方案的结果
    // 观察我们的问题本身，如果把这个数看成是一堆分立的1
    // 问题就更加明朗了
    // 那么如何求解 dfs(i, k) 呢？
    // 比较明显的是：我们可以枚举最后一次拆出来的数值，并进行递归
    // 最后一次拆出来一个 1:
    // 结果是 1*dfs(i-1, k-1)
    // 最后一次拆出来一个 2:
    // 结果是 2*dfs(i-2, k-1)
    // 之后是 3*dfs(i-3, k-1)
    // 以此类推。。。
    // 这些值中最大的那一个就是我们最后需要的拆解方案
    // 而对于全局的这个 n，我们要做的就是遍历所有可能的 k 值(注意，一个整数 n 最多拆成 n 个 1 相加，不可能再多了)
    // 添加一个记忆化数组
    vector<vector<int>> memo(n+1, vector<int>(n+1, -1));
    function<int(int, int)> dfs = [&](int i, int k) -> int
    {
        // 记忆化加速
        if(memo[i][k] != -1)
        {
            return memo[i][k];
        }
        // 递归的基本情况是：k == 1
        // 此时我们只需要返回 i 本身即可，因为我们要求是只分成一份，就是这个数本身
        if(k == 1)
        {
            memo[i][k] = i;
            return i;
        }
        int res = 0;
        for(int j = 1; j < i; ++j)
        {
            res = max(res, j*dfs(i-j, k-1));
        }
        memo[i][k] = res;
        return res;
    };
    // 循环调用即可
    int ans = 0;
    for(int k = 2; k <= n; ++k)
    {
        ans = max(ans, dfs(n, k));
    }
    return ans;
}

// 第三版：把 DFS 优化成自底向上的 DP，省去递归调用的开销
int integerBreak(int n)
{
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
    // 对边界情况先进行初始化
    for(int i = 1; i <= n; ++i)
    {
        dp[i][1] = i;
    }
    // 之后进行递推过程
    for(int k = 2; k <= n; ++k)
    {
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j < i; ++j)
            {
                dp[i][k] = max(dp[i][k], j*dp[i-j][k-1]);
            }
        }
    }
    // 最后一轮循环进行检查
    int ans = 0;
    for(int k = 2; k <= n; ++k)
    {
        ans = max(ans, dp[n][k]);
    }
    return ans;
}

// 第四版：时间复杂度优化
int integerBreak(int n)
{
    // 我们总是会很容易被题目误导
    // 本题并没有要求我们明确求出：k 等于几的时候，能够拿到最大解
    // 所以我们可以修改递归的定义：
    // dp[i] 代表的是：我们把 i 这个数拆分成至少 2 份，乘积最大的拆法的结果
    // 那么我们可以考虑最后一个拆出来的值
    // 这个值一定是 [1, i-1] 之间的一个数，否则我们没法把 i 拆成至少两份
    // 递推关系为：
    // dp[i] = max(j * (i-j), j*dp[i-j])
    // 两层含义：1. j * (i-j) 代表我们只把 i 拆成两个数，那么这个结果就是 j*(i-j)
    // 2. j*dp[i-j] 代表我们先拆出 j 这个数，剩下的 i-j 再拆成至少两份，所能拿到的最大乘积
    // 这两种结果取最大值，就是我们最终要的结果
    // 最后：j 取 [1, i-1] 中的所有值中最优的那一个
    vector<int> dp(n+1, 0);
    // 基本情况设定： dp[1] = 0，因为很明显我们没法把 1 拆成两个值。。。
    dp[1] = 0;
    // 之后进行递推即可
    for(int i = 2; i <= n; ++i)
    {
        int maximum = 0;
        for(int j = 1; j < i; ++j)
        {
            maximum = max({maximum, j*(i-j), j*dp[i-j]});
        }
        dp[i] = maximum;
    }
    return dp[n];
}