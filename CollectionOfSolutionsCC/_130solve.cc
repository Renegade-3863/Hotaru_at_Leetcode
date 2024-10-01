#include "Solution.h"

void Leetcode101_200::Solution::solve(vector<vector<char>>& board)
{
    // 上、右、下、左
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    // 本题是比较经典的 DFS 类问题，需要我们对整个图进行 DFS 检查
    // 不过由于我们在对一个 'O' 格进行的深搜结束前，可能不会知道这个区域是否被 'X' 包围
    // 所以我们可以考虑一种反其道而行之的策略
    // 先找出矩阵中所有处在边缘的 'O'，之后再通过这些 'O' 向内进行 DFS 深入，把所有这些连接起来的 'O' 换成另一种特殊标记
    // 之后再遍历一次矩阵，把所有还被标记为 'O' 的结点之间转换成 'X'
    // 最后再把这些特殊标记的位置转换回 'O' 即可完成任务
    // 先写好深搜函数
    int m = board.size(), n = board[0].size();
    function<void(int, int)> dfs = [&](int x, int y)
    {
        // 按 "上、右、下、左" 的顺序进行检查
        for(int i = 0; i < 4; ++i)
        {
            int nextx = x+dirs[i][0], nexty = y+dirs[i][1];
            // 判断是否是一个有效的位置
            if(nextx >= 0 && nextx < m && nexty >= 0 && nexty < n)
            {
                // 对 'O' 进行标记，并深入
                if(board[nextx][nexty] == 'O')
                {
                    board[nextx][nexty] = 'A';
                    dfs(nextx, nexty);
                }
                // 如果是一个 'X'，或者 'A'，就可以不进行深入，因为不连续了
            }
        } 
    };
    // 检查四条边界上的 'O'，如果遇到了，就执行 dfs 过程
    for(int i = 0; i < m; ++i)
    {
        if(board[i][0] == 'O')
        {
            board[i][0] = 'A';
            dfs(i, 0);
        }
        if(board[i][n-1] == 'O')
        {
            board[i][n-1] = 'A';
            dfs(i, n-1);
        }
    }
    for(int j = 1; j < n-1; ++j)
    {
        if(board[0][j] == 'O')
        {
            board[0][j] = 'A';
            dfs(0, j);
        }
        if(board[m-1][j] == 'O')
        {
            board[m-1][j] = 'A';
            dfs(m-1, j);
        }
    }
    // 遍历一遍整个矩阵，把所有 'O' 换成 'X'，所有 'A' 换回 'O' 即可
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(board[i][j] == 'O')
            {
                board[i][j] = 'X';
            }
            if(board[i][j] == 'A')
            {
                board[i][j] = 'O';
            }
        }
    }
    return;
}