#include "Solution.h"

// DFS 解法
int Leetcode101_200::Solution::numIslands(vector<vector<char>>& grid)
{
    // 本题是一道经典的图论题目
    // 我们可以使用 DFS 方法简单实现
    // 不过在 DFS 的过程中，我们还需要一种机制来实现对已经访问过格子的记忆，即我们不能两次访问同一个岛屿
    // 这样会导致重复计算同一个岛屿
    // 可以通 DFS 过程中把检查过的格子标记为 '2' 来实现
    // 写一个 DFS 函数
    // 这个函数会修改全局的 "岛屿数量变量" res
    int res = 0;
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int m = grid.size(), n = grid[0].size();
    // 返回值代表 (i, j) 这个下标是否合法
    function<bool(int, int)> isValid = [&](int i, int j)
    {
        // 需要检查的就是这个下标是不是在 grid 的矩阵范围内
        return i >= 0 && i < m && j >= 0 && j < n;
    };
    function<void(int, int)> dfs = [&](int i, int j)
    {
        // 四个方向深入之前，为了防止后续的深搜回头到这个格子出现无限递归，需要先标记这个格子为 "已检查"
        grid[i][j] = '2';
        // 尝试分别向四个方向深入
        for(int k = 0; k < 4; ++k)
        {
            int nexti = i+dirs[k][0], nextj = j+dirs[k][1];
            // 需要一个函数来检查这个下一步格子是否合法
            // 我们在上面定义一下
            // 只有当这个下一跳格子是范围合法，并且格子代表的是还未被检查过的陆地的时候，我们才对其进行 DFS 访问
            if(isValid(nexti, nextj) && grid[nexti][nextj] == '1')
            {
                dfs(nexti, nextj);
            }
        }
    };
    // 遍历整张图进行访问即可
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(grid[i][j] == '1')
            {
                dfs(i, j);
                // 别忘了递增岛屿的个数
                ++res;
            }
        }
    }
    return res;
}

// 尝试 BFS 解法
int numIslands(vector<vector<char>>& grid)
{
    // 使用 DFS 进行联通岛检查的方案很直观，而我们现在需要做的是尝试使用 BFS 再实现一遍这张图的检查
    // BFS 方案显然是需要队列实现的
    // 队列存储的是一个表示点坐标的结构题
    // 先定义一个结构体
    struct point {
    public:
        point(int _x, int _y) : x(_x), y(_y) {}
        int x;
        int y;
    };
    int res = 0;
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int m = grid.size(), n = grid[0].size();
    // BFS 使用的队列
    queue<point> q;
    // 返回值代表 (i, j) 这个下标是否合法
    function<bool(int, int)> isValid = [&](int i, int j)
    {
        // 需要检查的就是这个下标是不是在 grid 的矩阵范围内
        return i >= 0 && i < m && j >= 0 && j < n;
    };
    // 写一个从具体的格子开始进行 BFS 的函数
    // 注意到，我们实际上不需要给这个 BFS 函数传入任何参数
    function<void()> bfs = [&]() 
    {
        while(!q.empty())
        {
            // 每次弹出一个格子进行四个方向的检查
            // 注意，这里不能添加引用符号，如果添加了，就要把 q.pop() 这一步调到使用参数 x 和 y 之后，不然会出现引用失效问题
            const auto [x, y] = q.front();
            // cout << x << ", " << y << endl;
            // 检查下一跳坐标合法性的函数和上面 DFS 是一样的
            for(int k = 0; k < 4; ++k)
            {
                int nextx = x+dirs[k][0], nexty = y+dirs[k][1];
                // 需要一个函数来检查这个下一步格子是否合法
                // 我们在上面定义一下
                // 只有当这个下一跳格子是范围合法，并且格子代表的是还未被检查过的陆地的时候，我们才把它添加到 BFS 队列中
                if(isValid(nextx, nexty) && grid[nextx][nexty] == '1')
                {   
                    // 注意一个很关键的细节问题，BFS 中，标记 "已访问" 这一步实际上应该挪到 for 循环内部，否则会出现不同的格子遍历时都添加了一个它们共同的临接格子的问题，这样会引起很多重复检查，我们需要避免这一问题
                    grid[nextx][nexty] = '2';
                    q.push(point(nextx, nexty));
                }
            }
            // 别忘了弹出这个结点
            q.pop();
        }
    };
    // 一样的遍历，过程中记录岛屿数量即可
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(grid[i][j] == '1')
            {
                grid[i][j] = '2';
                // 先添加队列，再执行 BFS
                q.push(point(i, j));
                bfs();
                // 递增岛屿数量
                ++res;
            }
        }
    }
    return res;
}