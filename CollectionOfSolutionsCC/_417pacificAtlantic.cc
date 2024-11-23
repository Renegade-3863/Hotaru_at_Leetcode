#include "Solution.h"

vector<vector<int>> Leetcode401_500::Solution::pacificAtlantic(vector<vector<int>>& heights)
{
    // 经典的 DFS 和 BFS 类问题
    // 本题有一种很奇怪的反向解法，我们让 "水往高处流"
    // 从所有入海处判断太平洋或大西洋的水最远能流到哪里
    // 处理完成后，根据 "可流到结果" 判断所有能同时到达两个海洋的格子坐标即可
    // 我们只需要实现对应的 BFS 调用函数即可
    int m = heights.size(), n = heights[0].size();
    vector<vector<int>> pacific(m, vector<int>(n, false));
    vector<vector<int>> atlantic(m, vector<int>(n, false));
    int level = 0;
    // 记录上下左右四个方向
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    function<void(int, int, vector<vector<int>>&)> bfs = [&](int i, int j, vector<vector<int>>& ocean) 
    {
        // 进一步优化：如果当前结点已经被之前的某次 BFS 访问过并标记为 true 了，那么所有和它相连的结点一定都被标记过了，所以我们没必要进一步检查了
        if(ocean[i][j])
        {
            return;
        }
        // 维护一个队列，这个队列保存的是所有水可以反向流到的格子位置
        queue<pair<int, int>> q;
        q.emplace(i, j);
        while(!q.empty())
        {
            // 取出当前格子的两个方向坐标
            auto [x, y] = q.front();
            ocean[x][y] = true;
            q.pop();
            // 对于每个坐标，我们尝试往上下左右四个方向流动，同时避免回头
            // 这可以通过维护一个动态的 "层数图" 来实现
            // 遍历方向数组，决定下一个格子坐标
            for(int i = 0; i < 4; ++i)
            {
                int nxtx = x+dirs[i][0], nxty = y+dirs[i][1];
                // 判断新坐标是否合法，并且可以流到，且没有被访问过
                // 1. 坐标要合法
                // 2. 没访问过
                // 3. 水可以爬上去，而不是降下去
                if(nxtx >= 0 && nxtx < m && nxty >= 0 && nxty < n && heights[nxtx][nxty] >= heights[x][y] && !ocean[nxtx][nxty])
                {
                    // 我们把这个下一跳格子设为 "可达"
                    // 添加下一跳到队列中
                    q.emplace(nxtx, nxty);
                    ocean[nxtx][nxty] = true;
                }
            }
        }
    };
    // 对每一个边界上的格子运行一次上面的 BFS 流程即可
    for(int i = 0; i < m; ++i)
    {
        bfs(i, 0, pacific);
    }
    for(int j = 0; j < n; ++j)
    {
        bfs(0, j, pacific);
    }
    for(int i = 0; i < m; ++i)
    {
        bfs(i, n-1, atlantic);
    }
    for(int j = 0; j < n; ++j)
    {
        bfs(m-1, j, atlantic);
    }
    vector<vector<int>> res;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(pacific[i][j] && atlantic[i][j])
            {
                res.push_back({i, j});
            }
        }
    }
    return res;
}