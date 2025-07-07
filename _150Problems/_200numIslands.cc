class Solution
{
public:
    int numIslands(vector<vector<char>>& grid)
    {
        const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        // 可以使用类似 BFS 的方式来进行题目解析
        // 我们可以对 grid 中每一块包含 1 的封闭区块进行 BFS 遍历
        // 为此，我们定义一个 BFS 函数
        // 代表我们正在对 (x, y) 所在的位置所属的岛屿进行遍历
        int m = grid.size(), n = grid[0].size();
        // q 中保存的是 (xi, yi)，也就是格子的坐标
        queue<pair<int, int>> q;
        function<void(int, int)> bfs = [&](int x, int y) -> void
        {
            while(!q.empty())
            {
                pair<int, int> pa = q.front();
                // 往四个方向探查，如果有相邻的 '1'，就入队
                for(int k = 0; k < 4; ++k)
                {
                    int nxtx = pa.first+dirs[k][0], nxty = pa.second+dirs[k][1];
                    // 不合法，那么我们跳过这次探查
                    if(nxtx < 0 || nxtx >= m || nxty < 0 || nxty >= n)
                    {
                        continue;
                    }
                    // 合法，但我们还需要检查是否是一个 '1' 格
                    if(grid[nxtx][nxty] == '0')
                    {
                        continue;
                    }
                    // 把 grid[nxtx], grid[nxty]) 修改为 '0'
                    grid[nxtx][nxty] = '0';
                    // 既合法，又是一个 '1' 格，那么我们把它入队
                    q.emplace(nxtx, nxty);
                }
                // pa 使用完成，我们出队
                q.pop();
            }
            // 处理结束，结束 helper function
        };
        // 完成上层逻辑
        // 双层 for 循环对数据进行处理即可
        int ret = 0;
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(grid[i][j] == '1')
                {
                    grid[i][j] = '0';
                    q.emplace(i, j);
                    bfs(i, j);
                    ++ret;
                }
            }
        }
        return ret;
    }
};