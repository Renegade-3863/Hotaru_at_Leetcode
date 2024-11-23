#include "Solution.h"

// 第一版：暴力 DFS，不带记忆化
int Leetcode401_500::Solution::splitArray(vector<int>& nums, int k)
{
    // 类似背包问题的一道题
    // 我们用下面的方法来定义子问题：
    // dfs(i, j) 代表把 nums 的前 i 个元素，分组成 j 组的条件下，所能拿到的 j 组和最大值最小的那种结果
    // 那么我们对于原问题的分解，可以变为：
    // dfs(i, j) = for all k in 0 to i-2 min(dfs(k, j-1), sum of nums[k+1] to nums[i-1])
    // 翻译一下就是：我们考虑最后一组子数组要拆多长，之后处理左边子数组为基础的子问题，判断这样构成的更大子问题的结果即可
    // 对于这个 sum 处理，我们可以用前缀和来加速计算
    int n = nums.size();
    vector<int> preSum(n, 0);
    preSum[0] = nums[0];
    for(int i = 1; i < n; ++i)
    {
        preSum[i] = preSum[i-1]+nums[i];
    }
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 考虑最小子问题定义
        // 如果 i == 1，那么结果就是 nums[i] 本身
        // 而 j == 1，那么结果就是 preSum[i] 本身
        if(i == 1)
        {
            return nums[0];
        }
        if(j == 1)
        {
            return preSum[i-1];
        }
        // 之后是一般情况
        // 我们枚举最后一个子数组的长度
        int res = 0x0f0f0f0f;
        for(int k = 0; k < i-1; ++k)
        {
            res = min(res, max(dfs(k+1, j-1), preSum[i-1]-preSum[k]));
        }
        return res;
    };
    return dfs(n, k);
}

// 第二版：DFS + 记忆化
int splitArray(vector<int>& nums, int k)
{
    // 类似背包问题的一道题
    // 我们用下面的方法来定义子问题：
    // dfs(i, j) 代表把 nums 的前 i 个元素，分组成 j 组的条件下，所能拿到的 j 组和最大值最小的那种结果
    // 那么我们对于原问题的分解，可以变为：
    // dfs(i, j) = for all k in 0 to i-2 min(dfs(k, j-1), sum of nums[k+1] to nums[i-1])
    // 翻译一下就是：我们考虑最后一组子数组要拆多长，之后处理左边子数组为基础的子问题，判断这样构成的更大子问题的结果即可
    // 对于这个 sum 处理，我们可以用前缀和来加速计算
    int n = nums.size();
    vector<int> preSum(n, 0);
    preSum[0] = nums[0];
    for(int i = 1; i < n; ++i)
    {
        preSum[i] = preSum[i-1]+nums[i];
    }
    // 添加一个记忆化数组
    vector<vector<int>> memo(n, vector<int>(k, -1));
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 考虑最小子问题定义
        // 如果 i == 1，那么结果就是 nums[i] 本身
        // 而 j == 1，那么结果就是 preSum[i] 本身
        if(i == 1)
        {
            return nums[0];
        }
        if(j == 1)
        {
            return preSum[i-1];
        }
        if(memo[i-1][j-1] != -1)
        {
            return memo[i-1][j-1];
        }
        // 之后是一般情况
        // 我们枚举最后一个子数组的长度
        int res = 0x0f0f0f0f;
        for(int k = 0; k < i-1; ++k)
        {
            res = min(res, max(dfs(k+1, j-1), preSum[i-1]-preSum[k]));
        }
        memo[i-1][j-1] = res;
        return res;
    };
    return dfs(n, k);
}

// 第三版：把记忆化 DFS 转换成自底向上的 DP
int splitArray(vector<int>& nums, int k)
{
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(k, 0));
    vector<int> preSum(n, 0);
    preSum[0] = nums[0];
    for(int i = 1; i < n; ++i)
    {
        preSum[i] = preSum[i-1]+nums[i];
    }
    // 设定边界情况
    for(int j = 0; j < k; ++j)
    {
        dp[0][j] = nums[0];
    }
    for(int i = 0; i < n; ++i)
    {
        dp[i][0] = preSum[i];
    }
    // 开始递推
    for(int i = 2; i <= n; ++i)
    {
        for(int j = 2; j <= k; ++j)
        {
            int res = 0x0f0f0f0f;
            for(int t = 0; t < i-1; ++t)
            {
                res = min(res, max(dp[t][j-2], preSum[i-1]-preSum[t]));
            }
            dp[i-1][j-1] = res;
        }
    }
    return dp[n-1][k-1];
}