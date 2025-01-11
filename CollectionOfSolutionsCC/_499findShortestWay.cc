#include "Solution.h"

struct status
{
    int x;
    int y;
    string path;
    int steps;
    // 构造函数
    status(int _x, int _y, const string& _path, int _steps) : x(_x), y(_y), path(_path), steps(_steps) {}
};
struct hashFunc
{
    size_t operator() (const status& st) const 
    {
        auto hasherInt = hash<int>();
        auto hasherStr = hash<string>();
        return hasherInt(st.x) ^ hasherInt(st.y) ^ hasherStr(st.path) ^ hasherInt(st.steps);
    }
};
struct equalFunc
{
    bool operator() (const status& a, const status& b) const
    {
        return a.x == b.x && a.y == b.y && a.path == b.path && a.steps == b.steps;
    }
};
string Leetcode401_500::Soltuion::findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole)
{
    // 基本的逻辑不难，依然是使用 BFS，当然本题有一点不同，因为需要找出的是总距离最短的路径
    // 所以我们需要一种更好的 "状态" 定义
    // 考虑下面的定义方式：
    /* 
    struct
    {
        int x;
        int y;
        // path 代表的是球到达这个状态经过的所有操作
        string path;
        // 当前状态走的总步数
        int steps;
    };
    */
    // 方向数组
    // 上，右，下，左
    const int dirs[4][2] = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
    int m = maze.size(), n = maze[0].size();
    // 定义两个数组，它们具有下面的定义：
    // dist[i][j] 代表的是：从 ball[0], ball[1] 走到这个位置的最短已知路径长度
    // path[i][j] 代表的是：从 ball[0], ball[1] 走到这个位置的最短已知路径 (字符串形式)
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
    vector<vector<string>> paths(m, vector<string>(n, "impossible"));
    // res 是全局的最短路径长度
    int res = INT_MAX;
    // 最后返回的路径
    string ans = "";
    // 从 st 状态开始，按 dir 方向，走到撞墙为止
    // 函数返回后，st 的状态值存储的要要么是一个墙前的格子信息，要么是最终的 "洞口" 坐标
    function<void(status&, int)> moveDir = [&](status& st, int dir) -> void
    {
        int x = st.x, y = st.y;
        // 循环退出条件：
        // 1. 到达了边界
        // 2. 撞墙了
        // 3. 进洞了
        // 我们把外层退出条件定义为 "进洞了"
        while(x != hole[0] || y != hole[1])
        {
            // 往 dir 方向一直走，如果这条直线上可以无阻碍的到达洞口，就把 x 和 y 修改为洞口坐标
            int nextx = x+dirs[dir][0], nexty = y+dirs[dir][1];
            if(nextx < 0 || nextx >= m || nexty < 0 || nexty >= n)
            {
                // 到达地图边界了，退出
                break;
            }
            if(maze[nextx][nexty] == 1)
            {
                // 撞墙了，也要退出
                break;
            }
            // 否则，能走，就走下去
            x = nextx; y = nexty;
            // st.steps 也要修改
            ++st.steps;
        }
        // 别忘了修改 st 状态信息
        st.x = x; st.y = y; 
        // path 也要修改
        // 因为不确定这个方向是否可行，我们放到外面修改
        return;
    };
    // 使用队列模拟 BFS
    // 这个队列中存储的是所有可行的，还未到达终点 (洞) 的中间状态，当这个队列变空时，说明已经探查了所有可能的路径，我们可以返回最后的结果了
    queue<status> q;
    // 把起点坐标和初始状态做成 status 对象，放入队列中
    // 初始的 steps 值为 0，代表步数为 0，最开始的 "走法" 为空，代表还没有进行任何操作
    q.push(status(ball[0], ball[1], "", 0));
    dist[ball[0]][ball[1]] = 0;
    while(!q.empty())
    {
        // 我们按层进行 BFS 递推
        int n = q.size();
        for(int i = 0; i < n; ++i)
        {
            // 取出队头状态
            // 按引用取，减少复制开销
            status& st = q.front();
            // cout << "At: (" << st.x << ", " << st.y << ");\n"; 
            // 根据 st.x, st.y 进行下一步尝试
            for(int i = 0; i < 4; ++i)
            {
                // 题目要求的是 "一条路走到黑"
                // 所以我们定义一个 "按对应方向走到底" 的函数
                // 定义为 moveDir 函数
                status tmp = st;
                moveDir(st, i);
                // 检查更新后的 st，是否出现了变化，如果有变化，就往 q 中压入一个新状态
                if(tmp.x != st.x || tmp.y != st.y)
                {
                    switch(i)
                    {
                        case 0:
                            st.path.push_back('d');
                            break;
                        case 1:
                            st.path.push_back('l');
                            break;
                        case 2:
                            st.path.push_back('r');
                            break;
                        case 3:
                            st.path.push_back('u');
                            break;
                        // 非法情况，不会执行到
                        default:
                            return "";
                    }
                    // 这一步有点类似 DFS 的思路，我们利用已知信息来进行剪枝：
                    // 如果已知一条从 (ball[0], ball[1]) 到当前 (st.x, st.y) 的更短路径，那么我们就没必要把当前这个状态考虑进来
                    // 否则，如果这条路径长度相同，那我们只当路径本身字典序更小的时候，才把这个状态考虑进来
                    if(st.steps < dist[st.x][st.y] || (st.steps == dist[st.x][st.y] && st.path < paths[st.x][st.y]))
                    {
                        if(!(st.x == hole[0] && st.y == hole[1]))
                        {
                            q.emplace(st.x, st.y, st.path, st.steps);
                        }
                        dist[st.x][st.y] = st.steps;
                        paths[st.x][st.y] = st.path;
                    }
                }
                // 否则，这个方向走不下去了，我们没必要再记录一遍
                // 重置 st
                st = tmp;
            }
            // 使用完成，弹出队头元素
            q.pop();
        }
    }
    return paths[hole[0]][hole[1]];
}

/*
[[0,1,0,0,1,0,0,1,0,0],
[0,0,1,0,0,1,0,0,1,0],
[0,0,0,0,0,0,1,0,0,1],
[0,0,0,0,0,0,1,0,0,1],
[0,1,0,0,1,0,0,1,0,0],
[0,0,1,0,0,1,0,0,0,0],
[0,0,0,0,0,0,1,0,0,0],
[1,0,0,1,0,0,0,0,0,1],
[0,1,0,0,1,0,0,1,0,0],
[0,0,0,0,0,1,0,0,1,0]]
*/