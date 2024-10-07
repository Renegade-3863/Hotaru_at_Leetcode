#include "Solution.h"

// 第一版：不带记忆化的纯 DFS，可以预见的超时
int Leetcode101_200::Solution::calculateMinimumHP(vector<vector<int>>& dungeon)
{
    int m = dungeon.size(), n = dungeon[0].size();
    // 本题又是一道要求求出最优解的问题，这种题其实应该第一时间反应到是 DFS 或者 DP 方案
    // 我们需要考虑的是如何定义递归的子问题
    // 我们可以这样定义子问题的格式：
    // 从下标 (i, j) 到最终救到公主，所需的最低初始健康点数
    // 定义为：int dfs(i, j)
    // 那么很显然边界问题是：dfs(m-1, n-1) = dungeon[m-1][n-1] > 0 ? 0 : -dungeon[m-1][n-1]+1
    // 之后考虑问题如何向更大的情况递推
    // 假设我们想求解这个问题：dfs(i, j)
    // 那么它显然和后续的两个格子有关(如果它们是有效的格子：dfs(i+1, j) 与 dfs(i, j+1)
    // 我们可以考虑这样的递推关系：
    // dfs(i, j) = min(dfs(i+1, j), dfs(i, j+1)) + (-dungeon[i][j] < 0 ? 0 : (-dungeon[i][j])+1)
    // 基本含义是：当前格子到最终救到公主所需的最低初始健康点数，等于两个下一步格子到最终救到公主所需的最低初始健康点数更小的那一个，加上当前空格可能需要的已有血量
    // 注意：如果当前格子是补充格，我们可以只保证到达当前点位只剩最少的 1 格血
    // 问题：如果我们当前格子可以进行补给，那么会影响我们后面子问题的结果正确性吗？
    // 从定义上说，这并不矛盾
    // 明确了基本的子问题定义和递推关系，写代码的时候再处理一下细节问题了
    // 还要明确一点： dfs(i, j) 必须总是至少为1，因而 dfs(i, j)-1 一定是一个非负数，这是很重要的一个性质，可以简化我们后面的讨论
    function<int(int, int)> dfs = [&](int i, int j) -> int 
    {
        // 基本情况
        if(i == m-1 && j == n-1)
        {
            return dungeon[i][j] > 0 ? 1 : -dungeon[i][j]+1;
        }
        // 处理其它边界情况
        // i == m-1 && j != n-1
        if(i == m-1)
        {
            // 无非两种情况
            // 1. dungeon[i][j] >= dfs(i, j+1)-1
            // 此时必须有 dungeon >= 0
            // 此时我们不需要额外的血量，因为补给完之后完全可以成功救到公主
            // 因而我们只需要能够到达当前格子即可，即只剩1滴血即可
            // 2. dungeon[i][j] < dfs(i, j+1)-1
            // 此时我们需要额外的血量，因为在当前格子，即使能够补给，也不够
            // 那么我们需要多少额外血量？
            // 应该是 -dungeon[i][j] + dfs(i, j+1)
            // -dungeon[i][j] 是当前格子可以补给的量，如果当前格子是要消耗血量的，那么这个值就是正数，也是正确的
            // +dfs(i, j+1) 代表后续格子需要的量
            // 因为有这样的关系：
            // -dungeon[i][j]+dfs(i, j+1) > 1，所以这个所需的值一定是可以活着到达的，不需要再加1了
            return dungeon[i][j] >= dfs(i, j+1)-1 ? 1 : dfs(i, j+1)-dungeon[i][j]; 
        }
        // i != m-1 && j == n-1
        if(j == n-1)
        {   
            // 和上面是类似的
            return dungeon[i][j] >= dfs(i+1, j)-1 ? 1 : dfs(i+1, j)-dungeon[i][j];
        }
        // 否则，我们需要的量就是上面两种下一步情况中需要量更小的那一侧的结果
        // 先计算向下走所需的量
        int down = dungeon[i][j] >= dfs(i+1, j)-1 ? 1 : dfs(i+1, j)-dungeon[i][j];
        int right = dungeon[i][j] >= dfs(i, j+1)-1 ? 1 : dfs(i, j+1)-dungeon[i][j];
        return min(down, right);
    };
    // 调用即可
    return dfs(0, 0);
}

// 第二版：基于第一版的 DFS 添加记忆化哈希表，可以通过，但效率很低，需要进一步优化
int calculateMinimumHPMemo(vector<vector<int>>& dungeon)
{
    int m = dungeon.size(), n = dungeon[0].size();
    // 本题又是一道要求求出最优解的问题，这种题其实应该第一时间反应到是 DFS 或者 DP 方案
    // 我们需要考虑的是如何定义递归的子问题
    // 我们可以这样定义子问题的格式：
    // 从下标 (i, j) 到最终救到公主，所需的最低初始健康点数
    // 定义为：int dfs(i, j)
    // 那么很显然边界问题是：dfs(m-1, n-1) = dungeon[m-1][n-1] > 0 ? 0 : -dungeon[m-1][n-1]+1
    // 之后考虑问题如何向更大的情况递推
    // 假设我们想求解这个问题：dfs(i, j)
    // 那么它显然和后续的两个格子有关(如果它们是有效的格子：dfs(i+1, j) 与 dfs(i, j+1)
    // 我们可以考虑这样的递推关系：
    // dfs(i, j) = min(dfs(i+1, j), dfs(i, j+1)) + (-dungeon[i][j] < 0 ? 0 : (-dungeon[i][j])+1)
    // 基本含义是：当前格子到最终救到公主所需的最低初始健康点数，等于两个下一步格子到最终救到公主所需的最低初始健康点数更小的那一个，加上当前空格可能需要的已有血量
    // 注意：如果当前格子是补充格，我们可以只保证到达当前点位只剩最少的 1 格血
    // 问题：如果我们当前格子可以进行补给，那么会影响我们后面子问题的结果正确性吗？
    // 从定义上说，这并不矛盾
    // 明确了基本的子问题定义和递推关系，写代码的时候再处理一下细节问题了
    // 还要明确一点： dfs(i, j) 必须总是至少为1，因而 dfs(i, j)-1 一定是一个非负数，这是很重要的一个性质，可以简化我们后面的讨论
    // 添加一个记忆化数组
    // 0 代表这个结果我们还没计算过，基于对这道题特性的理解，我们知道只要算出来了结果，这个记忆化数组中的值必须是一个大于0的正数
    vector<vector<int>> memo(m, vector<int>(n, 0));
    function<int(int, int)> dfs = [&](int i, int j) -> int 
    {
        // 利用记忆化数组
        if(memo[i][j] > 0)
        {
            // 不再重复计算，直接返回记录的结果
            return memo[i][j];
        }
        // 基本情况
        if(i == m-1 && j == n-1)
        {
            memo[i][j] = dungeon[i][j] > 0 ? 1 : -dungeon[i][j]+1;
            return memo[i][j];
        }
        // 处理其它边界情况
        // i == m-1 && j != n-1
        if(i == m-1)
        {
            // 无非两种情况
            // 1. dungeon[i][j] >= dfs(i, j+1)-1
            // 此时必须有 dungeon >= 0
            // 此时我们不需要额外的血量，因为补给完之后完全可以成功救到公主
            // 因而我们只需要能够到达当前格子即可，即只剩1滴血即可
            // 2. dungeon[i][j] < dfs(i, j+1)-1
            // 此时我们需要额外的血量，因为在当前格子，即使能够补给，也不够
            // 那么我们需要多少额外血量？
            // 应该是 -dungeon[i][j] + dfs(i, j+1)
            // -dungeon[i][j] 是当前格子可以补给的量，如果当前格子是要消耗血量的，那么这个值就是正数，也是正确的
            // +dfs(i, j+1) 代表后续格子需要的量
            // 因为有这样的关系：
            // -dungeon[i][j]+dfs(i, j+1) > 1，所以这个所需的值一定是可以活着到达的，不需要再加1了
            memo[i][j] = dungeon[i][j] >= dfs(i, j+1)-1 ? 1 : dfs(i, j+1)-dungeon[i][j];
            return  memo[i][j];
        }
        // i != m-1 && j == n-1
        if(j == n-1)
        {   
            // 和上面是类似的
            memo[i][j] = dungeon[i][j] >= dfs(i+1, j)-1 ? 1 : dfs(i+1, j)-dungeon[i][j];
            return memo[i][j];
        }
        // 否则，我们需要的量就是上面两种下一步情况中需要量更小的那一侧的结果
        // 先计算向下走所需的量
        int down = dungeon[i][j] >= dfs(i+1, j)-1 ? 1 : dfs(i+1, j)-dungeon[i][j];
        int right = dungeon[i][j] >= dfs(i, j+1)-1 ? 1 : dfs(i, j+1)-dungeon[i][j];
        memo[i][j] = min(down, right);
        return memo[i][j];
    };
    // 调用即可
    return dfs(0, 0);
}

// 第三版：完全优化的 DP 方案
int calculateMinimumHPDP(vector<vector<int>>& dungeon)
{
    int m = dungeon.size(), n = dungeon[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    // 根据上面的 DFS 思路，我们给出边界情况的初始化
    dp[m-1][n-1] = dungeon[m-1][n-1] > 0 ? 1 : -dungeon[m-1][n-1]+1;
    for(int j = n-2; j >= 0; --j)
    {
        dp[m-1][j] = dungeon[m-1][j] >= dp[m-1][j+1]-1 ? 1 : dp[m-1][j+1]-dungeon[m-1][j];
    }
    for(int i = m-2; i >= 0; --i)
    {
        dp[i][n-1] = dungeon[i][n-1] >= dp[i+1][n-1]-1 ? 1 : dp[i+1][n-1]-dungeon[i][n-1];
    }
    // 之后只需要正常递推即可
    for(int i = m-2; i >= 0; --i)
    {
        for(int j = n-2; j >= 0; --j)
        {
            int down = dungeon[i][j] >= dp[i+1][j]-1 ? 1 : dp[i+1][j]-dungeon[i][j];
            int right = dungeon[i][j] >= dp[i][j+1]-1 ? 1 : dp[i][j+1]-dungeon[i][j];
            dp[i][j] = min(down, right);
        }
    }
    // 返回结果即可
    return dp[0][0];
}

// 第四版：二维数组优化为一维，理论上已经是最优了...
int calculateMinimumHPDPOpt(vector<vector<int>>& dungeon)
{
    // 注意到上面的填表流程只涉及到一行一行的数据计算，我们可以进行滚动数组空间优化
    int m = dungeon.size(), n = dungeon[0].size();
    vector<int> dp(n, 0);
    // 初始值对应的是第三版的最后一行
    // 进行初始化
    dp[n-1] = dungeon[m-1][n-1] > 0 ? 1 : -dungeon[m-1][n-1]+1;
    for(int j = n-2; j >= 0; --j)
    {
        dp[j] = dungeon[m-1][j] >= dp[j+1]-1 ? 1 : dp[j+1]-dungeon[m-1][j];
    }
    // 之后，按行进行滚动
    for(int i = m-2; i >= 0; --i)
    {
        // 别忘了对当前行的最后一个位置上的值进行修改
        dp[n-1] = dungeon[i][n-1] >= dp[n-1]-1 ? 1 : dp[n-1]-dungeon[i][n-1];
        for(int j = n-2; j >= 0; --j)
        {
            int down = dungeon[i][j] >= dp[j]-1 ? 1 : dp[j]-dungeon[i][j];
            int right = dungeon[i][j] >= dp[j+1]-1 ? 1 : dp[j+1]-dungeon[i][j];
            dp[j] = min(down, right);
        }
    }
    return dp[0];
}