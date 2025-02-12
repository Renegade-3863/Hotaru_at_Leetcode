#include "Solution.h"

// 第一版：暴力 DFS，被 n == 1000，k == 3 轻松卡爆 TLE
int Leetcode601_700::Soltuion::kInversePairs(int n, int k)
{
    const int MOD = 1e9+7;
    // 这题如果做的题够多了，应该是能一眼看出来是个 DP 类问题的。。
    // 而且是一道很明显的二维状态递推类问题
    // 我们定义下面的关系式：
    // dfs(i, j) 代表从 1 到 i，且恰好拥有 j 个逆序对的不同数组的个数
    // 那么我们要求的问题就变成了：
    // dfs(n, k)
    // 我们思考如何进行递推：
    // 首先，有个隐含条件：
    // dfs(i, j) 的情况下，代表我们现在持有的是一个 [1, i-1] 的元素组成的序列，现在需要做的是把 i 这个元素添加到前面这个序列中
    // 构成一个新的序列 (由 [1, i] 中的所有元素构成)
    // 那么我们只需要考虑当前这个 i 元素放到前面这个序列的哪一个位置 (注意，无论这个值插入前面序列中的哪一个位置，只要不是接到 [1, i-1] 的序列尾部，就会形成新的逆序对)
    // 那么可以对 j 进行遍历，模拟把 i 这个元素插到前面 i-1 个元素中的 i 个空位来达成 j 个逆序对中的一部分
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 考虑基本情况
        // j == 0，否则，如果 j == 0，那么代表我们只有 [1, i] 顺序序列这一种结果
        // 无论 i 为何值
        // j < 0 的情况是不合法的，我们需要返回 0
        if(j < 0)
        {
            return 0;
        }
        if(j == 0)
        {
            return 1;
        }
        // 否则，k > 0，此时如果 i == 1
        if(i == 1)
        {
            // 我们只用了第一个元素，也就是 1，那么此时没法构造出任何逆序对，无论 j 为何值
            return 0;
        }
        // 其它情况下，我们可以根据 i 和 j 执行 for 循环进行子问题计算
        // 我们最多可以在本次构造出 min(i, j) 个逆序对
        // 最少可以构造出 0 个逆序对
        // 算上 i，是因为前 i-1 个元素构成的序列只有 i 个空位可以添数字
        // 算上 j，是因为我们的子问题只计算到目前为止有 j 个逆序对的情况
        int res = 0;
        for(int k = 0; k < i; ++k)
        {
            // 0, 2, 1, 3 <- 4
            res = (res+dfs(i-1, j-(i-1-k)))%MOD;
        }
        // 返回 res 即可
        return res;
    };
    // 我们直接调用 dfs 即可
    return dfs(n, k);
}

// 第二版：暴力 DFS + 记忆化
// 被 n == 1000，k == 1000 轻松卡爆 TLE
int kInversePairs(int n, int k)
{
    const int MOD = 1e9+7;
    // 记忆化数组 memo
    vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
    // 下面这部分和第一版是一样的，只是添加了一些记忆化的步骤
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 考虑基本情况
        // j == 0，否则，如果 j == 0，那么代表我们只有 [1, i] 顺序序列这一种结果
        // 无论 i 为何值
        // j < 0 的情况是不合法的，我们需要返回 0
        if(j < 0)
        {
            return 0;
        }
        if(j == 0)
        {
            return 1;
        }
        // 否则，k > 0，此时如果 i == 1
        if(i == 1)
        {
            // 我们只用了第一个元素，也就是 1，那么此时没法构造出任何逆序对，无论 j 为何值
            return 0;
        }
        if(memo[i][j] != -1)
        {
            return memo[i][j];
        }
        // 其它情况下，我们可以根据 i 和 j 执行 for 循环进行子问题计算
        // 我们最多可以在本次构造出 min(i, j) 个逆序对
        // 最少可以构造出 0 个逆序对
        // 算上 i，是因为前 i-1 个元素构成的序列只有 i 个空位可以添数字
        // 算上 j，是因为我们的子问题只计算到目前为止有 j 个逆序对的情况
        int res = 0;
        for(int k = 0; k < i; ++k)
        {
            // 0, 2, 1, 3 <- 4
            res = (res+dfs(i-1, j-(i-1-k)))%MOD;
        }
        // 返回 res 即可
        memo[i][j] = res;
        return res;
    };
    // 我们直接调用 dfs 即可
    return dfs(n, k);
}

// 第三版：转换为自底向上的 DP 方法
// 依然被 n == 1000，k == 1000 卡爆 TLE
// 注意到，这个方法的时间复杂度是 O(n^2k) 级别，所以很容易被这个 n 的大数值卡爆
// 我们需要考虑如何优化 n 的这个平方项
int kInversePairs(int n, int k)
{
    const int MOD = 1e9+7;
    vector<vector<int>> dp(n+1, vector<int>(k+1, 0));
    // 对 dp 的边界情况进行初始化
    // 所有 k == 0 的情况，结果均为 1，只要 i >= 1
    for(int i = 1; i <= n; ++i)
    {
        dp[i][0] = 1;
    }
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= k; ++j)
        {
            // 把上面的循环递推关系式写过来即可
            for(int k = 0; k < i; ++k)
            {
                if(i-k-1 <= j)
                {
                    dp[i][j] = (dp[i][j]+dp[i-1][j-(i-k-1)])%MOD;
                }
            }
        }
    }
    // 返回最终结果即可
    return dp[n][k]%MOD;
}

// 第四版：尝试把平方项优化成一次项
int kInversePairs(int n, int k)
{
    /*
        把第三版的代码拿过来看一下
        我们最想优化的应该就是最内层的这个按 k 进行的循环
        因为我们之前见过类似的结构
        我们列几个式子就懂了：
        dp[i][j] = dp[i-1][j]+dp[i-1][j-1]+dp[i-1][j-2]+...+dp[i-1][j-i+1] 
        dp[i][j-1] = dp[i-1][j-1]+dp[i-1][j-2]+dp[i-1][j-3]+...+dp[i-1][j-i+1]+dp[i-1][j-i] 
        那么会发现：dp[i][j] = dp[i][j-1]-dp[i-1][j-i]+dp[i-1][j]
    */
    const int MOD = 1e9+7;
    vector<vector<int>> dp(n+1, vector<int>(k+1, 0));
    // 对 dp 的边界情况进行初始化
    // 所有 k == 0 的情况，结果均为 1，只要 i >= 1
    for(int i = 1; i <= n; ++i)
    {
        dp[i][0] = 1;
    }
    for(int i = 2; i <= n; ++i)
    {
        for(int j = 1; j <= k; ++j)
        {
            // // 把上面的循环递推关系式写过来即可
            // for(int k = 0; k < i; ++k)
            // {
            //     if(i-k-1 <= j)
            //     {
            //         dp[i][j] = (dp[i][j]+dp[i-1][j-(i-k-1)])%MOD;
            //     }
            // }
            // 上面的部分就可以按照我们刚刚发现的递推关系进行优化
            // 多加一个 MOD 是用来防止前面的计算结果出现负数，导致结果也是负数
            dp[i][j] = ((dp[i][j-1]+dp[i-1][j])%MOD-(j >= i ? dp[i-1][j-i] : 0)+MOD)%MOD;
        }
    }
    // 返回最终结果即可
    return dp[n][k];
}