#include "Solution.h"

// 暴力 DFS，不加记忆化
int Leetcode601_700::Soltuion::maxA(int n)
{
    // 本题最关键的点在于如何设计递推关系式：
    // 定义下面的子问题：
    // dfs(i) 代表 "执行 i 步，能拿到的最多 'A' 的个数"
    // 那么我们可以这样对子问题进行递推：
    // 1. 最后一步是直接打印一个 'A'
    // dfs(i) = max(dfs(i), dfs(i-1)+1)
    // 2. 最后一步是粘贴前面某一步复制的全屏的 'A'
    // 我们假设从 j 步开始，到第 i 步结束都在复制
    // 那么我们可以得出下面的递推式
    // dfs(i) = for all j from 3 to i-1 max(dfs(i), dfs(j-2)*(i-j+1))
    // 之所以用 dfs(j-2)，是因为需要两步对全屏的 'A' 进行复制，而一共会复制 (i-j) 次，加上原有的一份，一共 (i-j+1) 次
    // 至于最后一步是选中屏幕/复制选中区域这两种情况
    // 我们不难想到，这种不会产生任何新字符的操作一定不会是最后一步，因为我们就算是复制一轮已有的字符，都会比只复制要强
    function<int(int)> dfs = [&](int i) -> int
    {
        if(i == 0)
        {
            // 基本情况，不执行任何操作的话，我们没法拿到任何的 'A'
            return 0;
        }
        // 其它情况下，我们按上面的思路进行递推即可
        // 情况 1.
        int res = 0;
        res = max(res, dfs(i-1)+1);
        // 情况2.
        for(int j = 3; j < i; ++j)
        {
            res = max(res, dfs(j-2)*(i-j+1));
        }
        return res;
    };
    // 我们返回 dfs(n) 即可
    return dfs(n);
}

// 第二版：添加记忆化加速
int maxA(int n)
{
    vector<int> memo(n+1, -1);
    memo[0] = 0;
    function<int(int)> dfs = [&](int i) -> int
    {
        if(i == 0)
        {
            // 基本情况，不执行任何操作的话，我们没法拿到任何的 'A'
            return 0;
        }
        if(memo[i] != -1)
        {
            return memo[i];
        }
        // 其它情况下，我们按上面的思路进行递推即可
        // 情况 1.
        int res = 0;
        res = max(res, dfs(i-1)+1);
        // 情况2.
        for(int j = 3; j < i; ++j)
        {
            res = max(res, dfs(j-2)*(i-j+1));
        }
        memo[i] = res;
        return res;
    };
    // 我们返回 dfs(n) 即可
    return dfs(n);
}

// 第三版：转换成自底向上的 DP 方法
int maxA(int n)
{
    vector<int> dp(n+1, 0);
    for(int i = 1; i <= n; ++i)
    {
        dp[i] = max(dp[i], dp[i-1]+1);
        for(int j = 3; j < i; ++j)
        {
            dp[i] = max(dp[j-2]*(i-j+1), dp[i]);
        }
    }
    return dp[n];
}