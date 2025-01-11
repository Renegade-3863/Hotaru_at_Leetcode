#include "Solution.h"

int Leetcode501_600::Soltuion::change(int amount, vector<int>& coins)
{
    // 经典 DP 问题的改版，我们依然考虑先按照 DFS 的角度来考虑子问题：
    // dfs(i, j) 意义为：只使用 coins 排序后的前 i 种硬币值，来构成价值 j 的硬币组合数
    // 考虑如何进行子问题的递推
    // 不难想到，dfs(i, j) = dfs(i-1, j-k*coins[i-1]) k 从零开始计数
    // 换句话说，使用前 i 种硬币值来完成 j 的任务，我们可以完全不用第 i 种硬币，这就是子问题 dfs(i-1, j)
    // 或者，我们遍历 "使用一次 coins[i-1]"，"使用两次 coins[i-1]"，... 直到 k*coins[i-1] 比 j 还要大为止
    // 这是最简单的思路考量，不过基于我们之前的一些经验，这里的 k 一般都是不必要的
    // 我们考虑一下基本的简化逻辑：
    // 使用类似数学归纳法的罗列关系式方法：
    // dfs(i, j-coins[i-1]) = dfs(i-1, j-coins[i-1]) + dfs(i-1, j-2*coins[i-1]) + dfs(i-1, j-3*coins[i-1]) + ...
    // dfs(i, j) = dfs(i-1, j) + dfs(i-1, j-coins[i-1]) + dfs(i-1, j-2*coins[i-1]) + dfs(i-1, j-3*coins[i-1]) + ...
    // 我们可以很惊奇的发现，上下两个关系式，只差了一个 dfs(i-1, j) !
    // 换句话说，后面这一串：dfs(i-1, j-coins[i-1]) + dfs(i-1, j-2*coins[i-1]) + ...
    // 完全可以用 dfs(i, j-coins[i-1]) 来代替
    // 这样，我们就简化掉了这个本来需要再添一层 O(n) 的 k 值
    // 最后，递推关系式就变成了：
    // dfs(i, j) = dfs(i-1, j) + dfs(i, j-coins[i-1])
    // 明确了递推关系式，写代码就不难了
    // 定义一下子问题函数
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 定义基本情况：i == 1 或 j == 0
        // 如果 i == 0
        // 那么我们只能用 coins[0] 来凑出 j，此时我们考虑 j 是否能被 coins[0] 整除，不能的话，我们就返回 0，代表不合法即可
        if(i == 1)
        {
            return j%coins[0] == 0 ? 1 : 0;
        }
        // 其它情况都是一般情况，我们会在代码中防止 j 变成负数
        // 对于 coins[i-1]，我们只有在 coins[i-1] <= j 的时候才考虑 dfs(i, j-coins[i-1])
        if(coins[i-1] <= j)
        {
            return dfs(i-1, j) + dfs(i, j-coins[i-1]);
        }
        return dfs(i-1, j);
    };
    // 调用即可
    return dfs(coins.size(), amount);
}

// 考虑加入记忆化数组
int change(int amount, vector<int>& coins)
{
    // 一个记忆化数组，初始化为 -1，用于区分 "是否计算过"
    vector<vector<int>> memo(coins.size()+1, vector<int>(amount+1, -1));
    // 定义一下子问题函数
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 定义基本情况：i == 1 或 j == 0
        // 如果 i == 0
        // 那么我们只能用 coins[0] 来凑出 j，此时我们考虑 j 是否能被 coins[0] 整除，不能的话，我们就返回 0，代表不合法即可
        if(i == 1)
        {
            return j%coins[0] == 0 ? 1 : 0;
        }
        // 记忆化操作
        if(memo[i][j] != -1)
        {
            return memo[i][j];
        }
        // 其它情况都是一般情况，我们会在代码中防止 j 变成负数
        // 对于 coins[i-1]，我们只有在 coins[i-1] <= j 的时候才考虑 dfs(i, j-coins[i-1])
        if(coins[i-1] <= j)
        {
            memo[i][j] = dfs(i-1, j) + dfs(i, j-coins[i-1]);
            return memo[i][j];
        }
        memo[i][j] = dfs(i-1, j);
        return memo[i][j];
    };
    // 调用即可
    return dfs(coins.size(), amount);
}

// 第三版：把自顶向下的 DFS 改成自底向上的 DP 方法
int change(int amount, vector<int>& coins)
{
    int n = coins.size();
    vector<vector<int>> dp(n+1, vector<int>(amount+1, 0));
    // 初始化基本情况
    // 基本情况：
    // i == 1，根据上面的逻辑，dp[1][any j] 都可以初始化为 0 或 1
    for(int j = 0; j <= amount; ++j)
    {
        dp[1][j] = j%coins[0] == 0 ? 1 : 0;
    }
    // 之后是正常的递推过程
    // 我们分别枚举 i 和 j
    for(int i = 2; i <= n; ++i)
    {
        for(int j = 0; j <= amount; ++j)
        {
            if(coins[i-1] <= j)
            {
                // 防止溢出
                if(dp[i-1][j] < INT_MAX-dp[i][j-coins[i-1]])
                {
                    dp[i][j] = dp[i-1][j]+dp[i][j-coins[i-1]];
                }
            }
            else 
            {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][amount];
} 

// 第四版：尝试进行空间优化
int change(int amount, vector<int>& coins)
{
    int n = coins.size();
    // 注意到，dp[i][j] 只与 dp[i-1][j] 和 dp[i][j-coins[i-1]] 有关
    // 所以我们似乎可以把全表的 DP 优化成滚动 DP
    vector<int> dp(amount+1, 0);
    // 初始化
    for(int j = 0; j <= amount; ++j)
    {
        dp[j] = j%coins[0] == 0 ? 1 : 0;
    }
    for(int i = 2; i <= n; ++i)
    {
        for(int j = 0; j <= amount; ++j)
        {
            if(coins[i-1] <= j)
            {
                if(dp[j] < INT_MAX-dp[j-coins[i-1]])
                {
                    dp[j] = dp[j]+dp[j-coins[i-1]];
                }
            }
            // else
            // {
                // dp[j] = dp[j] 这里就不用写了
            // }
        }
    }
    return dp[amount];
}