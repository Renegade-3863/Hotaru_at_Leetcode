#include "Solution.h"

int Leetcode1_100::Solution::uniquePaths(int m, int n)
{
    // 尽管加入了障碍物的概念，本题依然是一道非常简单基础的 DP 入门题
    // 只是递推规则中加入一些限制即可
    // dp[i][j] = (!obstacleGrid[i][j])*((!obstacleGrid[i-1][j])*dp[i-1][j] + ((!obstacleGrid[i][j-1])*dp[i][j-1]))
    // 说人话就是，如果这个格子不是障碍物，那么它的步骤数就是左边和上面非障碍物格子的路径数之和
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
#if 0
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
    // 注意，本题要转一维的话会有一个小坑
    // 观察我们的转换方案
    // 我们其实没有在下面的循环中修改过 dp[0]
    /*
    for(int i = 1; i < m; ++i)
    {
        for(int j = 1; j < n; ++j)
        {
            dp[j] = (!obstacleGrid[i][j])*((!obstacleGrid[i-1][j])*dp[j] + ((!obstacleGrid[i][j-1])*dp[j-1]));
        }
    }
    */
    // 这在前面一题(不带障碍物)的情况下是没错的
    // 但在本题，这一方法可能会出现问题，因为可能出现本行的第一个格子中是一个障碍物的情况
    // 而如果这时我们还把 dp[0] 置为 1，那显然就是有问题的
    // 换句话说，其实只要某一行的第一个格子中有无障碍物的情况和 (0, 0) 格子不同，就会出问题，所以这里我们必须把 dp[0] 的更新也考虑进来
    for(int i = 1; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(j == 0)
            {
                dp[j] = obstacleGrid[i][j] ? 0 : dp[j];
                continue;
            }
            dp[j] = (!obstacleGrid[i][j])*((!obstacleGrid[i-1][j])*dp[j] + ((!obstacleGrid[i][j-1])*dp[j-1]));
        }
    }
    return dp[n-1];
}