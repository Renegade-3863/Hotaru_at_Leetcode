#include "Solution.h"

int Leetcode401_500::Soltuion::islandPerimeter(vector<vector<int>>& grid)
{
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    // 本题不用 DFS/BFS，只需要对整个矩阵遍历一轮，找出每个岛屿格和周围的非岛屿格之间的交界个数即可找到答案
    int m = grid.size(), n = grid[0].size();
    int res = 0;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            // 如果是一个海水格，那么我们不用做任何事，跳过即可
            // 如果是一个陆地格，那么我们需要向上下左右各探一格，如果遇到了海水/边界，那么给总的边界数+1即可
            if(grid[i][j] == 1)
            {
                // 四个方向遍历
                for(int k = 0; k < 4; ++k)
                {
                    int nxti = i+dirs[k][0], nxtj = j+dirs[k][1];
                    // 如果 (nxti, nxtj) 是边界/是海水格，那么对 res + 1
                    if(nxti < 0 || nxti >= m || nxtj < 0 || nxtj >= n || grid[nxti][nxtj] == 0)
                    {
                        ++res;
                    }
                }
            }
        }
    }
    return res;
}