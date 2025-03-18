#include "Solution.h"

int Leetcode501_600::Soltuion::maxAreaOfIsland(vector<vector<int>>& grid)
{
    // 本题不需要判断岛屿的形状，而需要判断岛屿的面积，所以我们可以简单用 dfs 来处理
    // 我们定义一个 dfs 函数，用于对岛屿进行遍历
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int m = grid.size(), n = grid[0].size();
    // maxSize 记录最终的最大面积，curSize 记录某个岛屿的面积
    int maxSize = 0, curSize = 0;
    function<void(int, int)> dfs = [&](int i, int j) -> void
    {
        // 我们假设，所有被调用了 dfs 函数的格子，都是一个值为 1 的格子
        // 那么我们只需要把这个值为 1 的格子修改成 0 即可
        grid[i][j] = 0;
        ++curSize;
        // 之后，尝试往四个方向进行扩散，寻找下一个值为 1 的连通块
        for(int k = 0; k < 4; ++k)
        {
            int nxti = i+dirs[k][0], nxtj = j+dirs[k][1];
            if(nxti >= 0 && nxti < m && nxtj >= 0 && nxtj < n && grid[nxti][nxtj])
            {
                dfs(nxti, nxtj);
            }
        }
        // 四个方向遍历完成，返回即可
        return;
    };
    // 我们调用 dfs 即可
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(grid[i][j])
            {
                curSize = 0;
                dfs(i, j);
                maxSize = max(maxSize, curSize);
            }
        }
    }
    return maxSize;
}