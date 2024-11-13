#include "Solution.h"

int Leetcode301_400::Solution::maxKilledEnemies(vector<vector<char>>& grid)
{
    // 很简单的模拟类问题，我们只需要对 grid 网格图进行一下预处理即可
    // 首先定义这样一个子问题：对于每一个格子 (i, j)
    // 它右侧不碰墙壁可以炸到的最多人数我们可以定义为 availRight[i][j]
    // 同理，可以定义处出其它三种数组：
    // availLeft[i][j], availUp[i][j] 和 availDown[i][j]
    // 那么很明显，每个格子的结果就是 sum({availRight[i][j], availLeft[i][j], availUp[i][j], availDown[i][j]})
    // 所以我们只需要预处理出这四个数组即可
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> availRight(m, vector<int>(n, 0));
    vector<vector<int>> availLeft(m, vector<int>(n, 0));
    vector<vector<int>> availUp(m, vector<int>(n, 0));
    vector<vector<int>> availDown(m, vector<int>(n, 0));
    // 分开求四个信息数组即可
    for(int i = 0; i < m; ++i)
    {
        if(grid[i][n-1] == 'E')
        {
            availRight[i][n-1] = 1;
        }
        if(grid[i][0] == 'E')
        {
            availLeft[i][0] = 1;
        }
    }
    for(int j = 0; j < n; ++j)
    {
        if(grid[m-1][j] == 'E')
        {
            availDown[m-1][j] = 1;
        }
        if(grid[0][j] == 'E')
        {
            availUp[0][j] = 1;
        }
    }
    for(int j = n-2; j >= 0; --j)
    {
        for(int i = 0; i < m; ++i)
        {
            // 检查当前格子本身的信息
            // 如果当前格子是一个 "墙壁"，那么我们不用做任何处理
            // 这个格子的信息就是零
            if(grid[i][j] == 'W')
            {
                continue;
            }
            // 否则，如果这个格子处是一个敌人，我们给结果加1，否则不加
            availRight[i][j] = availRight[i][j+1] + (grid[i][j] == 'E');
        }
    }
    for(int j = 1; j < n; ++j)
    {
        for(int i = 0; i < m; ++i)
        {
            if(grid[i][j] == 'W')
            {
                continue;
            }
            availLeft[i][j] = availLeft[i][j-1] + (grid[i][j] == 'E');
        }
    }
    for(int i = 1; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(grid[i][j] == 'W')
            {
                continue;
            }
            availUp[i][j] = availUp[i-1][j] + (grid[i][j] == 'E');
        }
    }
    for(int i = m-2; i >= 0; --i)
    {
        for(int j = 0; j < n; ++j)  
        {
            if(grid[i][j] == 'W')
            {
                continue;
            }
            availDown[i][j] = availDown[i+1][j] + (grid[i][j] == 'E');
        }
    }
    // 最后遍历一遍整个图，计算出最终结果即可
    int res = 0;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            // 注意，只有空格位能放炸弹
            if(grid[i][j] == '0')
            {
                res = max(res, availUp[i][j]+availRight[i][j]+availDown[i][j]+availLeft[i][j]);
            }
        }
    }
    return res;
}