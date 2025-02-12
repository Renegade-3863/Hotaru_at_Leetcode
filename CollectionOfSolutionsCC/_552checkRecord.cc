#include "Solution.h"

int Leetcode501_600::Soltuion::checkRecord(int n)
{
    // 看一下题目描述，就不难发现这应该是一道 DP 类问题了
    // 对于 DP 类问题，最重要的是想一下如何定义子问题
    // 分析题目要求，我们不难发现
    // 我们可以用更短的记录递推出更长的记录
    // 定义：dfs(i, j, k) 代表 "长度为 i，并且结尾处有 j 个连续 'L'，子串中一共有 k 个 'A' 的可行出勤记录的个数"
    // 不难发现，对于任何可行的串，j 都不可能不小于 3
    // 同时，k 都不可能不小于 2
    // 换句话说，j 只可能为 0, 1 或 2
    // k 只可能为 0 或 1
    // 之后，考虑进行递推
    // 对于 dfs(i, j, k)
    // 我们分情况进行讨论
    // 1. j == 0 && k == 0
    // 那么 dfs(i, 0, 0) 可以这样进行递推
    // dfs(i-1, 0, 0)+dfs(i-1, 1, 0)+dfs(i-1, 2, 0)
    // 因为当前位置只能选 'P' 这个字符
    // 2. j == 0 && k == 1
    // 那么 dfs(i, 0, 1) 可以这样进行递推
    // dfs(i-1, 0, 0)+dfs(i-1, 0, 1)+dfs(i-1, 1, 0)+dfs(i-1, 1, 1)+dfs(i-1, 2, 0)+dfs(i-1, 2, 1)
    // 因为 'L' 是可以被截断的(根据定义)，所以我们更短的子问题中，j 的值可以是 1 或 2 
    // 3. j == 1 && k == 0
    // 那么 dfs(i, 1, 0) 可以这样进行递推
    // dfs(i, 1, 0) = dfs(i-1. 0, 0)
    // 这种情况下，当前字符我们只能选 'L'，这是受 dfs 定义限制的
    // 4. j == 1 && k == 1
    // dfs(i, 1, 1) = dfs(i-1, 0, 1)
    // 一样的情况，当前字符我们只能选 'L'，这是受 dfs 定义限制的
    // 5. j == 2 && k == 0
    // dfs(i, 2, 0) = dfs(i-1, 1, 0)
    // 一样的，当前字符我们只能选 'L'，这是受 dfs 定义限制的
    // 6. j == 2 && k == 1
    // dfs(i, 2, 1) = dfs(i-1, 1, 1)
    // 最后，基本情况为 i == 0，此时只有 j 和 k 也同时为 0 的时候，我们才返回 1，其它情况下，根据 dfs 的定义，不可能有结果
    function<int(int, int, int)> dfs = [&](int i, int j, int k) -> int
    {
        // 写明基本情况
        if(i == 0)
        {
            return j == 0 && k == 0;
        }
        // 其它情况下，根据上面分析的六种情况进行递推即可
        if(j == 0 && k == 0)
        {
            return dfs(i-1, 0, 0)+dfs(i-1, 1, 0)+dfs(i-1, 2, 0);
        }
        if(j == 0 && k == 1)
        {
            return dfs(i-1, 0, 0)+dfs(i-1, 0, 1)+dfs(i-1, 1, 0)+dfs(i-1, 1, 1)+dfs(i-1, 2, 0)+dfs(i-1, 2, 1);
        }
        if(j == 1 && k == 0)
        {
            return dfs(i-1, 0, 0);
        }
        if(j == 1 && k == 1)
        {
            return dfs(i-1, 0, 1);
        }
        if(j == 2 && k == 0)
        {
            return dfs(i-1, 1, 0);
        }
        if(j == 2 && k == 1)
        {
            return dfs(i-1, 1, 1);
        }
        // 不会执行到这一行
        return -1;
    };
    return dfs(n, 0, 0)+dfs(n, 0, 1)+dfs(n, 1, 0)+dfs(n, 1, 1)+dfs(n, 2, 0)+dfs(n, 2, 1);
}

// 第一版是纯暴力 DFS 的算法，我们考虑用记忆化数组对其进行加速优化
int checkRecord(int n)
{
    const int MOD = 1e9+7;
    // 看一下题目描述，就不难发现这应该是一道 DP 类问题了
    // 对于 DP 类问题，最重要的是想一下如何定义子问题
    // 分析题目要求，我们不难发现
    // 我们可以用更短的记录递推出更长的记录
    // 定义：dfs(i, j, k) 代表 "长度为 i，并且结尾处有 j 个连续 'L'，子串中一共有 k 个 'A' 的可行出勤记录的个数"
    // 不难发现，对于任何可行的串，j 都不可能不小于 3
    // 同时，k 都不可能不小于 2
    // 换句话说，j 只可能为 0, 1 或 2
    // k 只可能为 0 或 1
    // 之后，考虑进行递推
    // 对于 dfs(i, j, k)
    // 我们分情况进行讨论
    // 1. j == 0 && k == 0
    // 那么 dfs(i, 0, 0) 可以这样进行递推
    // dfs(i-1, 0, 0)+dfs(i-1, 1, 0)+dfs(i-1, 2, 0)
    // 因为当前位置只能选 'P' 这个字符
    // 2. j == 0 && k == 1
    // 那么 dfs(i, 0, 1) 可以这样进行递推
    // dfs(i-1, 0, 0)+dfs(i-1, 0, 1)+dfs(i-1, 1, 0)+dfs(i-1, 1, 1)+dfs(i-1, 2, 0)+dfs(i-1, 2, 1)
    // 因为 'L' 是可以被截断的(根据定义)，所以我们更短的子问题中，j 的值可以是 1 或 2 
    // 3. j == 1 && k == 0
    // 那么 dfs(i, 1, 0) 可以这样进行递推
    // dfs(i, 1, 0) = dfs(i-1. 0, 0)
    // 这种情况下，当前字符我们只能选 'L'，这是受 dfs 定义限制的
    // 4. j == 1 && k == 1
    // dfs(i, 1, 1) = dfs(i-1, 0, 1)
    // 一样的情况，当前字符我们只能选 'L'，这是受 dfs 定义限制的
    // 5. j == 2 && k == 0
    // dfs(i, 2, 0) = dfs(i-1, 1, 0)
    // 一样的，当前字符我们只能选 'L'，这是受 dfs 定义限制的
    // 6. j == 2 && k == 1
    // dfs(i, 2, 1) = dfs(i-1, 1, 1)
    // 最后，基本情况为 i == 0，此时只有 j 和 k 也同时为 0 的时候，我们才返回 1，其它情况下，根据 dfs 的定义，不可能有结果
    // 记录一个基本算一维的记忆化数组
    vector<vector<vector<int>>> memo(n+1, vector<vector<int>>(3, vector<int>(2, -1)));
    function<int(int, int, int)> dfs = [&](int i, int j, int k) -> int
    {
        if(memo[i][j][k] != -1)
        {
            return memo[i][j][k];
        }
        // 写明基本情况
        if(i == 0)
        {
            memo[i][j][k] = j == 0 && k == 0;
            return memo[i][j][k];
        }
        // 其它情况下，根据上面分析的六种情况进行递推即可
        if(j == 0 && k == 0)
        {
            memo[i][j][k] = (dfs(i-1, 0, 0)%MOD+dfs(i-1, 1, 0)%MOD)%MOD+dfs(i-1, 2, 0)%MOD;
            return memo[i][j][k];
        }
        if(j == 0 && k == 1)
        {
            memo[i][j][k] = (dfs(i-1, 0, 0)%MOD+dfs(i-1, 0, 1)%MOD)%MOD;
            memo[i][j][k] = (memo[i][j][k]+dfs(i-1, 1, 0)%MOD)%MOD;
            memo[i][j][k] = (memo[i][j][k]+dfs(i-1, 1, 1)%MOD)%MOD;
            memo[i][j][k] = (memo[i][j][k]+dfs(i-1, 2, 0)%MOD)%MOD;
            memo[i][j][k] = (memo[i][j][k]+dfs(i-1, 2, 1)%MOD)%MOD;
            return memo[i][j][k];
        }
        if(j == 1 && k == 0)
        {
            memo[i][j][k] = dfs(i-1, 0, 0);
            return memo[i][j][k];
        }
        if(j == 1 && k == 1)
        {
            memo[i][j][k] = dfs(i-1, 0, 1);
            return memo[i][j][k];
        }
        if(j == 2 && k == 0)
        {
            memo[i][j][k] = dfs(i-1, 1, 0);
            return memo[i][j][k];
        }
        if(j == 2 && k == 1)
        {
            memo[i][j][k] = dfs(i-1, 1, 1);
            return memo[i][j][k];
        }
        // 不会执行到这一行
        return -1;
    };
    int res = (dfs(n, 0, 0)%MOD+dfs(n, 0, 1)%MOD)%MOD;
    res = (res+dfs(n, 1, 0)%MOD)%MOD;
    res = (res+dfs(n, 1, 1)%MOD)%MOD;
    res = (res+dfs(n, 2, 0)%MOD)%MOD;
    res = (res+dfs(n, 2, 1)%MOD)%MOD;
    return res;
}

// 把自顶向下的 DFS 改成自底向上的 DP 方法
int checkRecord(int n)
{
    const int MOD = 1e9+7;
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(2, vector<int>(3, 0)));
    // 处理边界情况，只有 dp[0][0][0] 为 1，其余暂时均置为 0
    dp[0][0][0] = 1;
    for(int i = 1; i <= n; ++i)
    {
        dp[i][0][0] = ((dp[i-1][0][0] + dp[i-1][0][1])%MOD + dp[i-1][0][2]%MOD) % MOD;
        dp[i][1][0] = (((((dp[i-1][1][0] + dp[i-1][1][1])%MOD + dp[i-1][1][2])%MOD + dp[i-1][0][0])%MOD + dp[i-1][0][1])%MOD + dp[i-1][0][2]) % MOD;
        dp[i][0][1] = dp[i-1][0][0] % MOD;
        dp[i][0][2] = dp[i-1][0][1] % MOD;
        dp[i][1][1] = dp[i-1][1][0] % MOD;
        dp[i][1][2] = dp[i-1][1][1] % MOD;
    }
    return (((((dp[n][0][0] + dp[n][1][0])%MOD + dp[n][0][1])%MOD + dp[n][0][2])%MOD + dp[n][1][1])%MOD + dp[n][1][2]%MOD) % MOD;
}