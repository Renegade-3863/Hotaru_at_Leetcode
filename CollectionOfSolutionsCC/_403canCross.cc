#include "Solution.h"

// 第一版：暴力 DFS，TLE
bool Leetcode401_500::Solution::canCross(vector<int>& stones)
{
    // 经典的 DP 问题，我们还是先从 DFS 的角度入手
    // 定义 dfs(i, k) 代表上一步跳了 k 个单位，当前在下标 i 处，跳到结尾是否可行
    // 定义递归子问题
    // 转存 stones 数组
    unordered_map<int, int> remapping;
    int n = stones.size();
    for(int i = 0; i < n; ++i)
    {
        remapping[stones[i]] = i;
    }
    if(remapping.find(1) == remapping.end())
    {
        return false;
    }
    // 递归函数定义
    // dfs(i, k)，代表当前在下标 i 位置上的石头，而上一步是经过了 k 步跳过来的情况下，能否到达最后一块石头
    function<bool(int, int)> dfs = [&](int i, int k) -> bool
    {
        // 考虑基本情况：
        // i == n-1 的时候，说明我们已经到达了最后一块石头，直接返回 true 即可
        if(i == n-1)
        {
            return true;
        }
        // 其它情况下，我们需要进行递归搜索
        // 根据当前所在石头的下标，我们检索出它的位置，根据这个位置，计算出下一步可以跳到的石头位置，根据这个位置再反向检索出对应的下标，如果这个位置在数组中有下标，那么我们可以进一步递归，否则无法进一步深入
        for(int i = -1; i <= 1; ++i)
        {
            int curPos = remapping[i];
            // 计算出下一步到达的石头位置
            int nextPos = curPos + k + i;
            // 如果这个位置存在于数组中，我们就可以跳，否则不能跳
            if(remapping.find(nextPos) != remapping.end())
            {
                // 跳过去
                // 如果从下一个状态可以到达最后一块石头，我们可以返回 true
                // 否则，继续循环检查
                // 注意，这里有一个隐含的细节问题
                // 如果我们当前可行的步数中存在 0 步(k+i == 0)
                // 那么我们可能会陷入死循环，这种情况需要避免
                if(k+i == 0)
                {
                    continue;
                }
                if(dfs(remapping[nextPos], k+i))
                {
                    return true;
                }
            }
        }
        // 循环结束，没有可行解，返回 false
        return false;
    };
    return dfs(1, 1);
}

// 第二版：使用记忆化优化 DFS 算法
bool canCross(vector<int>& stones)
{
    // 经典的 DP 问题，我们还是先从 DFS 的角度入手
    // 定义 dfs(i, k) 代表上一步跳了 k 个单位，当前在下标 i 处，跳到结尾是否可行
    // 定义递归子问题
    // 转存 stones 数组
    unordered_map<int, int> remapping;
    int n = stones.size();
    for(int i = 0; i < n; ++i)
    {
        remapping[stones[i]] = i;
    }
    if(remapping.find(1) == remapping.end())
    {
        return false;
    }
    // 递归函数定义
    // dfs(i, k)，代表当前在下标 i 位置上的石头，而上一步是经过了 k 步跳过来的情况下，能否到达最后一块石头
    // 记忆化数组
    int maximum = *max_element(stones.begin(), stones.end());
    vector<vector<int>> memo(n, vector<int>(n, -1));
    function<bool(int, int)> dfs = [&](int cur, int k) -> bool
    {
        // 考虑基本情况：
        // i == n-1 的时候，说明我们已经到达了最后一块石头，直接返回 true 即可
        if(cur == n-1)
        {
            return true;
        }
        if(memo[cur][k] != -1)
        {
            return memo[cur][k];
        }
        // 其它情况下，我们需要进行递归搜索
        // 根据当前所在石头的下标，我们检索出它的位置，根据这个位置，计算出下一步可以跳到的石头位置，根据这个位置再反向检索出对应的下标，如果这个位置在数组中有下标，那么我们可以进一步递归，否则无法进一步深入
        for(int i = -1; i <= 1; ++i)
        {
            int curPos = stones[cur];
            // 计算出下一步到达的石头位置
            int nextPos = curPos + k + i;
            // 如果这个位置存在于数组中，我们就可以跳，否则不能跳
            if(remapping.find(nextPos) != remapping.end())
            {
                // 跳过去
                // 如果从下一个状态可以到达最后一块石头，我们可以返回 true
                // 否则，继续循环检查
                // 注意，这里有一个隐含的细节问题
                // 如果我们当前可行的步数中存在 0 步(k+i == 0)
                // 那么我们可能会陷入死循环，这种情况需要避免
                if(k+i == 0)
                {
                    continue;
                }
                if(dfs(remapping[nextPos], k+i))
                {
                    memo[cur][k] = 1;
                    return true;
                }
            }
        }
        // 循环结束，没有可行解，返回 false
        memo[cur][k] = 0;
        return false;
    };
    return dfs(1, 1);
}