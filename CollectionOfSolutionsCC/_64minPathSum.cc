#include "Solution.h"

int minPathSum(vector<vector<int>>& grid)
{
    // 依然是很常规的动态规划
    // 考虑 DP 的状态定义和最优子结构性质
    // 假设 dp[i][j] 代表从左上角到达格子 (i, j) 的数字总和最小的路径
    // 那么我们不难看出如下的最优子结构特征：
    // 如果到达某个格子 (i, j) 的数字总和是最小的，那么到达它的两个前驱格子((i-1, j), (i, j-1))的路径的数字总和
    // 也一定是最小的
    // 反证法：否则我们能找到一条到达 (i-1, j) 或者 (i, j-1) 的数字总和更小的路径，进而使得这个由它们延伸出来的更长路径 (到 (i, j) 的路径)
    // 的数字总和更小
    // 明确了这一点，我们就不难写出状态转换方程了
    // dp[i][j] = min(dp[i-1][j], dp[i][j-1])+grid[i][j];
    int m = grid.size(), n = grid[0].size();
#if 0
    vector<vector<int>> dp(m, vector<int>(n, 0));
    // 边界情况初始化
    dp[0][0] = grid[0][0];
    for(int i = 1; i < m; ++i)
    {
        dp[i][0] = dp[i-1][0] + grid[i][0];
    }
    for(int j = 1; j < n; ++j)
    {
        dp[0][j] = dp[0][j-1] + grid[0][j];
    }
    // 递推全过程
    for(int i = 1; i < m; ++i)
    {
        for(int j = 1; j < n; ++j)
        {
            dp[i][j] = min(dp[i-1][j], dp[i][j-1])+grid[i][j];
        }
    }
    return dp[m-1][n-1];
#endif
    // 依然是二维转一维，依然要注意边界情况是否需要额外处理
    vector<int> dp(n, 0);
    dp[0] = grid[0][0];
    for(int j = 1; j < n; ++j)
    {
        dp[j] = dp[j-1] + grid[0][j];
    }
    for(int i = 1; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(j == 0)
            {
                dp[j] += grid[i][j];
                continue;
            }
            dp[j] = min(dp[j-1], dp[j]) + grid[i][j];
        }
    }
    return dp[n-1];
}