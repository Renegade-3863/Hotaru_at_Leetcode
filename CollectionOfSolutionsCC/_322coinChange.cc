#include "Solution.h"

// 第一版：暴力 DFS，不带记忆化，TLE
int Leetcode301_400::Solution::coinChange(vector<int>& coins, int amount)
{
    // 很经典的 DP 类问题，我们可以先从 自顶向下的 DFS 角度思考如何定义子问题
    // 不难定义出下面的子问题：
    // dfs(i, n) -> 使用前 i 种硬币构成出价值 n 所需的最少硬币数量
    // 那么由父问题到子问题的递归求解过程可以推断如下：
    // dfs(i, n) = min(1+dfs(i-1, n-coins[i-1]), 2+dfs(i-1, n-2*coins[i-1]), ...)
    // 意思是，我们可以选择使用1次 coins[i-1]，2次 coins[i-1]，。。。，直到不能选更多 coins[i-1] 为止
    // 哦，别忘了，还可以不选 coins[i-1]，这就是 dfs(i-1, n)
    // 那么我们的递推过程就不难检查了
    // 下面给出单纯的 DFS 代码，不带记忆化
    function<int(int, int)> dfs = [&](int i, int n)
    {
        // 先定义一个递归的结束问题
        if(i == 1)
        {
            // 我们只用前一种硬币组成结果 n
            // 那么此时必须判断：n 是否是 coins[0] 的倍数
            // 如果不是倍数，那么我们返回-1，代表没法只使用前一种硬币构成结果 n
            if(n % coins[0])
            {
                return -1;
            }
            // 否则，直接返回 n / coins[0] 即可
            return n / coins[0];
        }
        // 其它情况，根据上面的逻辑进行深入递归
        // 返回值
        int res = -1;
        for(int k = 0; k*coins[i-1] <= n; ++k)
        {
            // 先计算子问题的结果
            int lastCnt = dfs(i-1, n-k*coins[i-1]);
            // 检查是否是一个合法结果
            if(lastCnt != -1)
            {
                if(res == -1)
                {
                    res = lastCnt+k;
                }
                else
                {
                    res = min(res, lastCnt+k);
                }
            }
        }
        return res;
    };
    // 直接调用递归函数即可
    return dfs(coins.size(), amount);
}

// 第二版：暴力 DFS + 记忆化加速
int coinChange(vector<int>& coins, int amount)
{
    // 很经典的 DP 类问题，我们可以先从 自顶向下的 DFS 角度思考如何定义子问题
    // 不难定义出下面的子问题：
    // dfs(i, n) -> 使用前 i 种硬币构成出价值 n 所需的最少硬币数量
    // 那么由父问题到子问题的递归求解过程可以推断如下：
    // dfs(i, n) = min(1+dfs(i-1, n-coins[i-1]), 2+dfs(i-1, n-2*coins[i-1]), ...)
    // 意思是，我们可以选择使用1次 coins[i-1]，2次 coins[i-1]，。。。，直到不能选更多 coins[i-1] 为止
    // 哦，别忘了，还可以不选 coins[i-1]，这就是 dfs(i-1, n)
    // 那么我们的递推过程就不难检查了
    // 下面给出单纯的 DFS 代码
    // 添加记忆化数组
    int m = coins.size();
    // 一个小细节，由于题目要求我们在不合法的时候返回 -1，所以这里我们对于 "未记录" 的定义不应该也用 -1，那样会导致很多重复的搜索，并不能做到完美加速
    vector<vector<int>> memo(m, vector<int>(amount+1, -2));
    function<int(int, int)> dfs = [&](int i, int n)
    {
        if(memo[i-1][n] != -2)
        {
            return memo[i-1][n];
        }
        // 先定义一个递归的结束问题
        if(i == 1)
        {
            // 我们只用前一种硬币组成结果 n
            // 那么此时必须判断：n 是否是 coins[0] 的倍数
            // 如果不是倍数，那么我们返回-1，代表没法只使用前一种硬币构成结果 n
            if(n % coins[0])
            {
                memo[0][n] = -1;
                return -1;
            }
            // 否则，直接返回 n / coins[0] 即可
            memo[0][n] = n / coins[0];
            return memo[0][n];
        }
        // 其它情况，根据上面的逻辑进行深入递归
        // 返回值
        int res = -1;
        for(int k = 0; k*coins[i-1] <= n; ++k)
        {
            // 先计算子问题的结果
            int lastCnt = dfs(i-1, n-k*coins[i-1]);
            // 检查是否是一个合法结果
            if(lastCnt != -1)
            {
                if(res == -1)
                {
                    res = lastCnt+k;
                }
                else
                {
                    res = min(res, lastCnt+k);
                }
            }
        }
        memo[i-1][n] = res;
        return res;
    };
    // 直接调用递归函数即可
    return dfs(m, amount);
}

// 第三版：把 DFS 换成自底向上的 DP
int coinChange(vector<int>& coins, int amount)
{
    // 一样的流程，只是写法换成了以数组为基础
    int m = coins.size();
    vector<vector<int>> dp(m, vector<int>(amount+1, -1));
    // 边界情况设定
    for(int j = 0; j <= amount; ++j)
    {
        if(j%coins[0] == 0)
        {
            dp[0][j] = j/coins[0];
        }
    }
    // 实际的递推过程
    for(int i = 1; i < m; ++i)
    {
        for(int j = 0; j <= amount; ++j)
        {
            for(int k = 0; k*coins[i-1]<=j; ++k)
            {
                dp[i][j] = max(dp[i][j], k+dp[i-1][j-k*coins[i-1]]);
            }
        }
    }
    // 返回结果
    return dp[m-1][amount];
}

// 第四版：DP 子问题定义方式的优化：基于背包问题模版
int coinChange(vector<int>& coins, int amount)
{
    // 一样的流程，只是写法换成了以数组为基础
    int m = coins.size();
    vector<vector<int>> dp(m, vector<int>(amount+1, -1));
    // 边界情况设定
    for(int j = 0; j <= amount; ++j)
    {
        if(j%coins[0] == 0)
        {
            dp[0][j] = j/coins[0];
        }
    }
    // 实际的递推过程
    for(int i = 1; i < m; ++i)
    {
        for(int j = 0; j <= amount; ++j)
        {
            // 关于最后的内层循环
            // 我们原来的定义是：使用前 i 种硬币组成价值 n
            // 而背包问题有一种很新的递推方式，可以优化掉这个内层循环
            // 我们改成两种递推来源：
            // 1. 不使用第 i 种硬币，而构成价值 n，需要的最少硬币个数：dp[i-1][n]
            // 2. 仍然使用第 i 种硬币，而最后一次添加一个第 i 种硬币：dp[i][n-coins[i]]
            dp[i][j] = dp[i-1][j];
            if(j >= coins[i])
            {
                if(dp[i][j-coins[i]] != -1)
                {
                    if(dp[i][j] == -1)
                    {
                        dp[i][j] = 1+dp[i][j-coins[i]];   
                    }
                    else
                    {
                        dp[i][j] = min(dp[i][j], 1+dp[i][j-coins[i]]);
                    }
                }
            }
        }
    }
    // 返回结果
    return dp[m-1][amount];
}

// 进行一些总结，前面的解释没看懂的直接看这里就行了
// 对于动态规划的递推关系，我们有时可以通过画 "图" 的方式来简化思维模型
// 注意，这个 "图" 不是只说你要画简单的图像
// 它是我们在图论里面用到的那种有边关系的图
// 比如本题的递推关系
// 我们一开始规划的递推模式是：从使用 k 次硬币 coins[i-1] 来递推当前的 dp[j][n]
// 我们以类似二维数组的方式画出这个递推关系
// 多累加几次前驱结点的递推关系，我们不难发现下面的关系：
// dp[i][j] = min(dp[i-1][j-k*coins[i-1]])
// dp[i][j-coins[i-1]] = min(dp[i-1][j-k*coins[i-1]])
// 把这两个式子展开，你很容易发现 dp[i][j-coins[i-1]] 这个式子可以简单的替代所有的 dp[i-1][j-k*coins[i-1]] (k > 0)
// 这就是我们给出上面优化的根本。当然，要理解这种数学表达式总是很困难，这里还是建议画出拓扑图进行理解

// 第五版：基于第四版的递推关系进行空间优化
int coinChange(vector<int>& coins, int amount)
{
    int m = coins.size();
    // 换成滚动数组进行优化
    vector<int> dp(amount+1, -1);
    // 边界情况设定
    for(int j = 0; j <= amount; ++j)
    {
        if(j%coins[0] == 0)
        {
            dp[j] = j/coins[0];
        }
    }
    // 之后一样的逻辑进行递推，只是换用滚动数组的形式
    for(int i = 1; i < m; ++i)
    {
        for(int j = 0; j <= amount; ++j)
        {
            if(j >= coins[i])
            {
                if(dp[j-coins[i]] != -1)
                {
                    if(dp[j] == -1)
                    {
                        dp[j] = 1+dp[j-coins[i]];
                    }
                    else
                    {
                        dp[j] = min(dp[j], 1+dp[j-coins[i]]);
                    }
                }
            }
        }
    }
    return dp[amount];
}