#include "Solution.h"

int Leetcode1_100::Solution::uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
{
    // 尽管加入了障碍物的概念，本题依然是一道非常简单基础的 DP 入门题
    // 只是递推规则中加入一些限制即可
    // dp[i][j] = (!obstacleGrid[i][j])*((!obstacleGrid[i-1][j])*dp[i-1][j] + ((!obstacleGrid[i][j-1])*dp[i][j-1]))
    // 说人话就是，如果这个格子不是障碍物，那么它的步骤数就是左边和上面非障碍物格子的路径数之和
#if 0
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = obstacleGrid[0][0] ? 0 : 1;
    // 边界情况设定
    for(int i = 1; i < m; ++i)
    {
        dp[i][0] = obstacleGrid[i][0] ? 0 : dp[i-1][0];
    }
    for(int j = 1; j < n; ++j)
    {
        dp[0][j] = obstacleGrid[0][j] ? 0 : dp[0][j-1];
    }
    // 递推过程
    for(int i = 1; i < m; ++i)
    {
        for(int j = 1; j < n; ++j)
        {
            dp[i][j] = (!obstacleGrid[i][j])*((!obstacleGrid[i-1][j])*dp[i-1][j] + ((!obstacleGrid[i][j-1])*dp[i][j-1]));
        }
    }
    return dp[m-1][n-1];
#endif
    // 尝试二维转一维
    vector<int> dp(n, 0);
    dp[0] = obstacleGrid[0][0] ? 0 : 1;
    for(int j = 1; j < n; ++j)
    {
        dp[j] = obstacleGrid[0][j] ? 0 : dp[j-1];
    }
    for(int i = 1; i < m; ++i)
    {
        for(int j = 1; j < n; ++j)
        {
            dp[j] = (!obstacleGrid[i][j])*((!obstacleGrid[i-1][j])*dp[j] + ((!obstacleGrid[i][j-1])*dp[j-1]));
        }
    }
    return dp[n-1];
}