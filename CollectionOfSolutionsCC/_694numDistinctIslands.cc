#include "Solution.h"

int Leetcode601_700::Soltuion::numDistinctIslands(vector<vector<int>>& grid)
{
    // 正常的 DFS 问题，不难做，思路理清即可顺利完成
    // 我们定义一个从一个值为 1 (陆地) 切入，遍历完所有与它同属于一个岛屿的陆地的函数 dfs
    function<void(int, int)> dfs = [&](int i, int j) -> void
    {
        if(grid[i][j] == 0)
        {
            // 如果当前格是一个 0，那么我们直接返回即可，不用进一步处理了
            return;
        }
        
    };
}