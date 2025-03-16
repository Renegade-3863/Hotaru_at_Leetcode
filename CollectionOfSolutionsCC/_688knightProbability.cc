#include "Solution.h"

// 第一版：暴力 dfs，不添加记忆化，也不改 dp
double Leetcode601_700::Soltuion::knightProbability(int n, int k, int row, int column)
{
    // 读完题，相信大家就不难想到，这时一道类似 dfs 的问题
    // 我们可以像下面这样定义递归的子问题：
    // dfs(i, j, k) 代表从单元格 (i, j, k) 开始，尝试进行 k 次移动，骑士最后在棋盘上的概率
    // 那么，假设一共八种方向
    // 第 h 种坐标为 (ih, jh)
    // 那么很明显 dfs(i, j, k) = sum for h from 1 to 8, 0.125 (因为八种可能的移动，每一种的概率都是 0.125) * dfs(ih, jh, k-1)
    // 最后，在规定递归结束条件时，别忘了优先判断 (i, j) 在不在棋盘上，之后再检查 k 值是否为 0
    // 定义八个方向的基本数组
    const int dirs[8][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};
    function<double(int, int, int)> dfs = [&](int i, int j, int k) -> double 
    {
        // 结束情况1.
        if(i >= n || j >= n || i < 0 || j < 0)
        {
            // 当前位置出界了，那么我们返回 0 即可，此时在棋盘上的概率为 0
            return 0.0;
        }
        // 结束情况2.
        // 此时我们已经确保了 (i, j) 是在棋盘上的，那么一步也不走的话，我们留在棋盘上的概率就是 100%
        if(k == 0)
        {
            return 1.0;
        }
        // 其它情况都是一般情况
        double res = 0.0;
        for(int h = 0; h < 8; ++h)
        {
            // 枚举八个方向，每个方向计算出新坐标，并使用递推函数计算概率值，累加到结果中
            int nxti = i+dirs[h][0], nxtj = j+dirs[h][1];
            res += 0.125*dfs(nxti, nxtj, k-1);
        }
        return res;
    };
    return dfs(row, column, k);
}

// 第二版：添加记忆化结构 memo
double knightProbability(int n, int k, int row, int column)
{
    // 这里添加一个记忆化 memo
    vector<vector<vector<double>>> memo(n, vector<vector<double>>(n, vector<double>(k+1, -1.0)));
    const int dirs[8][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};
    function<double(int, int, int)> dfs = [&](int i, int j, int k) -> double 
    {
        // 结束情况1.
        if(i >= n || j >= n || i < 0 || j < 0)
        {
            // 当前位置出界了，那么我们返回 0 即可，此时在棋盘上的概率为 0
            return 0.0;
        }
        // 结束情况2.
        // 此时我们已经确保了 (i, j) 是在棋盘上的，那么一步也不走的话，我们留在棋盘上的概率就是 100%
        if(k == 0)
        {
            return 1.0;
        }
        // 记忆化步骤
        if(memo[i][j][k] != -1)
        {
            return memo[i][j][k];
        }
        // 其它情况都是一般情况
        double res = 0.0;
        for(int h = 0; h < 8; ++h)
        {
            // 枚举八个方向，每个方向计算出新坐标，并使用递推函数计算概率值，累加到结果中
            int nxti = i+dirs[h][0], nxtj = j+dirs[h][1];
            res += 0.125*dfs(nxti, nxtj, k-1);
        }
        memo[i][j][k] = res;
        return res;
    };
    return dfs(row, column, k);
}

// 第三版：把 DFS 架构改成 DP 架构
double knightProbability(int n, int k, int row, int column)
{
    const int dirs[8][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};
    vector<vector<vector<double>>> dp(n, vector<vector<double>>(n, vector<double>(k+1, 0)));
    // 对 dp 进行初始化，所有 k == 0 的格子，结果均为 1.0
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            dp[i][j][0] = 1.0;
        }
    }
    // 超范围的不用初始化，你也初始化不了 ()
    // 之后是按照 k 对整张图按层遍历
    for(int l = 1; l <= k; ++l)
    {
        // 按照上面的递推关系式进行计算
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                for(int h = 0; h < 8; ++h)
                {
                    // 注意防止越界，越界的那部分我们也不用计算，因为本身留下的概率就为 0
                    int nxti = i+dirs[h][0], nxtj = j+dirs[h][1];
                    if(nxti < 0 || nxtj < 0 || nxti >= n || nxtj >= n)
                    {
                        continue;
                    }
                    dp[i][j][l] += 0.125*dp[nxti][nxtj][l-1];
                }
            }
        }
    }
    return dp[row][column][k];
}

// 第四版：基于递推逻辑，尝试对 dp 数组进行空间优化
double knightProbability(int n, int k, int row, int column)
{
    if(k == 0)
    {
        return 1.0;
    }
    const int dirs[8][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};
    // 第三维从 k 压缩到 2，两层图进行滚动
    vector<vector<vector<double>>> dp(n, vector<vector<double>>(n, vector<double>(2, 0)));
    // 对下标 0 的那一层进行初始化即可
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            dp[i][j][0] = 1.0;
        }
    }
    // 之后是滚动更新
    for(int l = 1; l <= k; ++l)
    {
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                // 别忘了重置 dp[i][j][1]
                dp[i][j][1] = 0;
                for(int h = 0; h < 8; ++h)
                {
                    // 注意防止越界，越界的那部分我们也不用计算，因为本身留下的概率就为 0
                    int nxti = i+dirs[h][0], nxtj = j+dirs[h][1];
                    if(nxti < 0 || nxtj < 0 || nxti >= n || nxtj >= n)
                    {
                        continue;
                    }
                    // 更新 dp[i][j][1]，之后复制 dp[i][j][1] 给 dp[i][j][0]
                    dp[i][j][1] += 0.125*dp[nxti][nxtj][0];
                }
            }
        }
        // dp[i][j][1] 更新完成，把 dp[i][j][1] 的元素复制给 dp[i][j][0]
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                dp[i][j][0] = dp[i][j][1];
            }
        }
    }
    return dp[row][column][1];
}