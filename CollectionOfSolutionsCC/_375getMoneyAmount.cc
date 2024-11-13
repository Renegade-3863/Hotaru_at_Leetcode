#include "Solution.h"

// 第一版：暴力 DFS，不带记忆化
int Leetcode301_400::Solution::getMoneyAmount(int n)
{
    // 很经典的区间 DP 类问题，我们从自顶向下的 DFS 角度就不难想明白这个问题的解法
    // 首先，我们看最大的这个子问题：
    // dfs(i, j) 代表猜想出 [i, j] 中的一个数字，保证猜对的最少现金数
    // 考虑子问题：
    // 我们应该做最坏的打算，因为我们要的是最少可以保证的金额
    // 我们假设这次猜错了，那么我们就会被告知自己猜大了还是猜小了
    // 那么如果我们猜大了，那么下一步是向左猜，如果我们猜小了，那么下一步是向右猜，我们需要保证的是所有下一步策略中所需成本最低的那一步
    // 也就是说，dfs(i, j) = k + min(max(dfs(i, k-1). dfs(k+1, j)))
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 递归基本情况：如果 i >= j，我们只需要返回0，因为我们一次一定能猜中
        if(i >= j)
        {
            return 0;
        }
        // 否则，我们需要遍历 [i, j] 之间的所有 k 值，深入检查子问题的最少所需开销
        int res = INT_MAX;
        for(int k = i; k <= j; ++k)
        {
            res = min(res, k+max(dfs(i, k-1), dfs(k+1, j)));
        }
        return res;
    };
    // 调用函数即可
    return dfs(1, n);
}

// 第二版：DFS + 记忆化加速
int getMoneyAmount(int n)
{
    // 很经典的区间 DP 类问题，我们从自顶向下的 DFS 角度就不难想明白这个问题的解法
    // 首先，我们看最大的这个子问题：
    // dfs(i, j) 代表猜想出 [i, j] 中的一个数字，保证猜对的最少现金数
    // 考虑子问题：
    // 我们应该做最坏的打算，因为我们要的是最少可以保证的金额
    // 我们假设这次猜错了，那么我们就会被告知自己猜大了还是猜小了
    // 那么如果我们猜大了，那么下一步是向左猜，如果我们猜小了，那么下一步是向右猜，我们需要保证的是所有下一步策略中所需成本最低的那一步
    // 也就是说，dfs(i, j) = k + min(max(dfs(i, k-1). dfs(k+1, j)))
    // 添加一个记忆化数组
    vector<vector<int>> memo(n, vector<int>(n, -1));
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 递归基本情况：如果 i >= j，我们只需要返回0，因为我们一次一定能猜中
        if(i >= j)
        {
            return 0;
        }
        if(memo[i-1][j-1] != -1)
        {
            return memo[i-1][j-1];
        }
        // 否则，我们需要遍历 [i, j] 之间的所有 k 值，深入检查子问题的最少所需开销
        int res = INT_MAX;
        for(int k = i; k <= j; ++k)
        {
            res = min(res, k+max(dfs(i, k-1), dfs(k+1, j)));
        }
        memo[i-1][j-1] = res;
        return res;
    };
    // 调用函数即可
    return dfs(1, n);
}

// 第三版：转换为自底向上的 DP 方法
int getMoneyAmount(int n)
{
    vector<vector<int>> dp(n+2, vector<int>(n+2, 0));
    // 边界情况已经完成初始化，我们剩下要做的就是根据区间长度进行递推了
    for(int len = 2; len <= n; ++len)
    {
        // 枚举区间起点
        // n-2, n-1
        for(int i = 1; i <= n-len+1; ++i)
        {
            // 算出区间另一端点的值
            int j = i+len-1;
            // 枚举中间值，和上面的 DFS 是完全一样的
            int res = INT_MAX;
            for(int k = i; k <= j; ++k)
            {
                res = min(res, k+max(dp[i][k-1], dp[k+1][j]));
            }
            dp[i][j] = res;
        }
    }
    return dp[1][n];
}