class Solution
{
public:
    void solve(vector<vector<char>>& board)
    {
        // 依然是 BFS 类问题
        // 本题多了一个条件：要求 'O' 并不与边界接壤
        // 所以正向的 "判断"+"处理" 的原始逻辑时间复杂度较大
        // 所以我们可以反向来进行处理
        // 把所有与边界接壤的 'O' 岛保留下来（例如标记成其它值）
        // 之后把剩下所有值仍为 'O' 的区域标记成 'X'
        int m = board.size(), n = board[0].size();
        // 我们先用 BFS 对边界上所有的 'O' 进行重新标记
        const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        // q 记录所有需要进行标记的坐标值
        queue<pair<int, int>> q;
        function<void()> bfs = [&]() -> void
        {
            while(!q.empty())
            {
                pair<int, int> pa = q.front();
                for(int k = 0; k < 4; ++k)
                {
                    int nxtx = pa.first+dirs[k][0], nxty = pa.second+dirs[k][1];
                    if(nxtx >= m || nxtx < 0 || nxty >= n || nxty < 0)
                    {
                        continue;
                    }
                    if(board[nxtx][nxty] != 'O')
                    {
                        continue;
                    }
                    // 对 grid[nxtx][nxty] 进行处理，修改成其它字符，例如 'S'
                    board[nxtx][nxty] = 'S';
                    q.emplace(nxtx, nxty);
                } 
                q.pop();
            }
        };
        // 我们检查四条边上所有的 'O' 进行处理
        // 左右边
        for(int i = 0; i < m; ++i)
        {
            if(board[i][0] == 'O')
            {
                q.emplace(i, 0);
                board[i][0] = 'S';
                bfs();
            }
            if(board[i][n-1] == 'O')
            {
                q.emplace(i, n-1);
                board[i][n-1] = 'S';
                bfs();
            }
        }        
        // 上下边
        for(int j = 0; j < n; ++j)
        {
            if(board[0][j] == 'O')
            {
                q.emplace(0, j);
                board[0][j] = 'S';
                bfs();
            }
            if(board[m-1][j] == 'O')
            {
                q.emplace(m-1, j);
                board[m-1][j] = 'S';
                bfs();
            }
        }
        // 处理完成，之后对所有剩下的 'O' 进行修改，然后把 'S' 改回 'O'
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(board[i][j] == 'O')
                {
                    board[i][j] = 'X';
                }
                if(board[i][j] == 'S')
                {
                    board[i][j] = 'O';
                }
            }
        }
        return;
    }
};