#include "Solution.h"

// 第一版：暴力 DFS，直接超时
int Leetcode401_500::Soltuion::findMaxForm(vector<string>& strs, int m, int n)
{
    // 基本的背包 DP 问题，我们依然先从 DFS 的角度入手解决
    // 思考如何定义子问题：
    // 假设 dfs(i, j) 代表：strs 子集中最多有 i 个 0 和 j 个 1 的最大子集的长度
    // 不过会发现这样去递推会很麻烦：
    // 我们需要枚举所有可能的 strs 子集，之后在它们的基础上累计 dfs(i, j) 的值
    // 所以我们需要修改 dfs 问题的定义
    // 回归背包问题的本质：
    // 我们可以这样修改定义：
    // dfs(i, j, k) 代表从 strs 的前 i 个字符串中做选择，选出最多有 j 个 0 和 k 个 1 的最大子集的长度
    // 之后我们会发现，这样定义的子问题，进行递推就不难了：
    // 我们可以从前 i-1 个字符串对应的各个结果中递推前 i 个字符串的子问题的结果
    // 对于第 i 个字符串，我们需要检查它内含的 1 和 0 的个数，分别记为 ones 和 zeroes
    // 如果 ones > j 或者 zeroes > k，那么说明我们没法把第 i 个字符串选入到结果集合中，那么也就没法进行递归计算，返回 dfs(i-1, j, k) 即可
    // 否则，我们可以比较 选 和 不选 第 i 个字符串得到的最长子集长度，比较选择更长的那一个作为本子问题的答案
    // 也就是：dfs(i, j, k) = max(dfs(i-1, j, k), dfs(i-1, j-ones, k-zeroes)+1);
    // 明确了上面的递推方法，我们写代码就很简单了
    function<int(int, int, int)> dfs = [&](int i, int j, int k) -> int
    {
        // 首先考虑递归的基本情况，这也是递归的结束条件
        if(i == 0)
        {
            // i == 0，说明我们不进行任何选择，那么直接返回 0 即可
            return 0;
        }
        // 其它情况下，我们需要进行递归计算
        // 首先统计 strs[i] 中 1 和 0 的个数
        int ones = 0, zeroes = 0;
        for(const auto& c : strs[i-1])
        {
            if(c == '1')
            {
                ++ones;
            }
            if(c == '0')
            {
                ++zeroes;
            }
        }
        // 统计完毕，可以根据值考虑如何进行实际的求解了
        if(zeroes > k || ones > j)
        {
            // strs[i] 没法计入，我们直接返回子问题的结果
            return dfs(i-1, j, k);
        }
        // 否则，可以计入，我们进行比较后返回
        return max(dfs(i-1, j, k), dfs(i-1, j-ones, k-zeroes)+1);
    };  
    // 调用函数即可，我们要求解的最终子问题是 dfs(strs.size(), n, m);
    return dfs(strs.size(), n, m);
}

// 第二版：尝试加入记忆化数组进行优化
int findMaxForm(vector<string>& strs, int m, int n)
{
    // 基本的背包 DP 问题，我们依然先从 DFS 的角度入手解决
    // 思考如何定义子问题：
    // 假设 dfs(i, j) 代表：strs 子集中最多有 i 个 0 和 j 个 1 的最大子集的长度
    // 不过会发现这样去递推会很麻烦：
    // 我们需要枚举所有可能的 strs 子集，之后在它们的基础上累计 dfs(i, j) 的值
    // 所以我们需要修改 dfs 问题的定义
    // 回归背包问题的本质：
    // 我们可以这样修改定义：
    // dfs(i, j, k) 代表从 strs 的前 i 个字符串中做选择，选出最多有 j 个 0 和 k 个 1 的最大子集的长度
    // 之后我们会发现，这样定义的子问题，进行递推就不难了：
    // 我们可以从前 i-1 个字符串对应的各个结果中递推前 i 个字符串的子问题的结果
    // 对于第 i 个字符串，我们需要检查它内含的 1 和 0 的个数，分别记为 ones 和 zeroes
    // 如果 ones > j 或者 zeroes > k，那么说明我们没法把第 i 个字符串选入到结果集合中，那么也就没法进行递归计算，返回 dfs(i-1, j, k) 即可
    // 否则，我们可以比较 选 和 不选 第 i 个字符串得到的最长子集长度，比较选择更长的那一个作为本子问题的答案
    // 也就是：dfs(i, j, k) = max(dfs(i-1, j, k), dfs(i-1, j-ones, k-zeroes)+1);
    // 明确了上面的递推方法，我们写代码就很简单了
    vector<vector<vector<int>>> memo(strs.size()+1, vector<vector<int>>(n+1, vector<int>(m+1, -1)));
    function<int(int, int, int)> dfs = [&](int i, int j, int k) -> int
    {
        // 首先考虑递归的基本情况，这也是递归的结束条件
        if(i == 0)
        {
            // i == 0，说明我们不进行任何选择，那么直接返回 0 即可
            return 0;
        }
        if(memo[i][j][k] != -1)
        {
            return memo[i][j][k];
        }
        // 其它情况下，我们需要进行递归计算
        // 首先统计 strs[i] 中 1 和 0 的个数
        int ones = 0, zeroes = 0;
        for(const auto& c : strs[i-1])
        {
            if(c == '1')
            {
                ++ones;
            }
            if(c == '0')
            {
                ++zeroes;
            }
        }
        // 统计完毕，可以根据值考虑如何进行实际的求解了
        if(zeroes > k || ones > j)
        {
            // strs[i] 没法计入，我们直接返回子问题的结果
            memo[i][j][k] = dfs(i-1, j, k);
            return memo[i][j][k];
        }
        // 否则，可以计入，我们进行比较后返回
        memo[i][j][k] = max(dfs(i-1, j, k), dfs(i-1, j-ones, k-zeroes)+1);
        return memo[i][j][k];
    };  
    // 调用函数即可，我们要求解的最终子问题是 dfs(strs.size(), n, m);
    return dfs(strs.size(), n, m);
}

// 第三版：自顶向下的 DFS 改成自底向上的 DP
int findMaxForm(vector<string>& strs, int m, int n)
{
    int len = strs.size();
    vector<vector<vector<int>>> dp(len+1, vector<vector<int>>(n+1, vector<int>(m+1, 0)));
    // 初始化边界情况
    // 所有 i == 0 的情况下，dp[0][j][k] 都是 0
    // 不过上面数组初始化已经把这个初始化做好了，我们直接执行 dp 逻辑即可
    for(int i = 1; i <= len; ++i)
    {
        // 这里求解 strs[i-1] 的 ones 和 zeroes 即可
        int ones = 0, zeroes = 0;
        for(const auto& c : strs[i-1])
        {
            if(c == '1')
            {
                ++ones;
            }
            if(c == '0')
            {
                ++zeroes;
            }
        }
        for(int j = 0; j <= n; ++j)
        {
            for(int k = 0; k <= m; ++k)
            {
                // 执行基本的递推逻辑即可
                dp[i][j][k] = dp[i-1][j][k];
                if(j >= ones && k >= zeroes)
                {
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-ones][k-zeroes]+1);
                }
            }
        }
    }
    // 返回答案
    return dp[len][n][m];
}

// 第四版：注意到可以进行滚动空间优化，我们尝试把三维 DP 转换成二维 DP
int findMaxForm(vector<string>& strs, int m, int n)
{
    // 只记录相邻层的元素，因为只有相邻层之间的元素有递推关系
    int len = strs.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for(int i = 1; i <= len; ++i)
    {
        // 记录 strs[i] 对应的 1 和 0 的个数
        int ones = 0, zeroes = 0;
        for(const auto& c : strs[i-1])
        {
            if(c == '1')
            {
                ++ones;
            }
            if(c == '0')
            {
                ++zeroes;
            }
        }
        // 这里需要注意，我们需要保证：大问题求解所需的所有子问题的结果在求解的时候都是有效的
        // 我们重新检查一下递推式：dp[i][j][k] = dp[i-1][j-ones][k-zeroes]，这里很明显我们只能倒序遍历第 i 层，才能保证矩阵左上角的元素在求解右下的结果的时候不会被覆盖掉
        for(int j = n; j >= ones; --j)
        {
            for(int k = m; k >= zeroes; --k)
            {
                dp[j][k] = max(dp[j][k], dp[j-ones][k-zeroes]+1);
            }
        }
    }
    // 返回结果即可
    return dp[n][m];
}