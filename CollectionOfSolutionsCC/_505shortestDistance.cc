#include "Solution.h"

struct status
{
    int x; 
    int y;
    // dist 存储一个 "当前状态下球已经运动过的距离" 值
    int dist;
    status(int _x, int _y, int _dist) : x(_x), y(_y), dist(_dist) {}
};

int Leetcode501_600::Soltuion::shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination)
{
    // 本质上依然是 Dijkstra 算法
    // 这里总结一下 Dijkstra 算法的本质
    // 从拆分实现细节的角度来分析，可以说：Dijkstra 算法就是带 DP 记忆化的 BFS 算法
    // 我们从 DP 的角度来理解 "最短路问题"
    // 定义下面的 DP 数组：
    // dp[point i] 为从出发点 (假设为 s) 到达 point i 的最短距离
    // 那么我们可以这样来进行递推：
    // 按 BFS 的逻辑，从出发点开始，逐层向外探查所有可能达到的点，并动态修改对应点到出发点 s 的 "最短距离记录"，也就是 dp[point k]
    // 不过这并不是说，Dijkstra 算法就是 DP 算法，毕竟 DP 算法的本质是：由确定最优解的子问题，一步到位推算出母问题的结果
    // 而 Dijkstra 算法的本质是按照 BFS 的顺序完整遍历所有可能的结果来保证最终计算出所需要的距离结果
    // 根据这个思路，我们给出基本的算法实现
    // 定义一个 "到 start 点最短距离值" 数组，命名为 dp
    int m = maze.size(), n = maze[0].size();
    // 一开始，所有点的距离都初始化为 -1，代表 "不可达"
    vector<vector<int>> dp(m, vector<int>(n, -1));
    // 注意本题的实际要求，我们需要实际能停止在 destination 的最短距离，所以我们需要额外使用一个变量对这个结果进行跟踪
    int res = -1;
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    // 定义一个 "移动函数"，代表从一个状态往某个方向走到黑
    function<void(status&, int)> moveDir = [&](status& st, int dir)
    {
        // 我们对 st 进行修改，沿着 dir 方向移动
        // 运动，直到：
        // 1. 下一个位置超出边界
        // 2. 撞墙了
        // 初始化 "下一步" 坐标，定义为 nxtx 和 nxty
        int nxtx = st.x+dirs[dir][0], nxty = st.y+dirs[dir][1];
        while(nxtx >= 0 && nxtx < m && nxty >= 0 && nxty < n && maze[nxtx][nxty] != 1)
        {
            // 记录 "多移动了一步"
            ++st.dist;
            // 检查同方向上下一个格子是否可以到达
            nxtx += dirs[dir][0]; nxty += dirs[dir][1];
        }
        // 移动到头了，我们结束移动返回即可
        // 别忘了，回退最后一步不合法的移动
        st.x = nxtx-dirs[dir][0]; st.y = nxty-dirs[dir][1];
        // 注意，使用引用，此时 st 就存储了新的状态信息
    };
    // 之后就是使用传统的 BFS 对所有球可以处于的 "状态" 进行遍历了
    // 我们需要一个能代表球所处状态的 "状态" 结构变量，定义一下
    queue<status> q;
    dp[start[0]][start[1]] = 0;
    // 初始化第一个状态，并压入队列中
    q.emplace(start[0], start[1], 0);
    while(!q.empty())
    {
        // 按层逐层向外扩散
        int n = q.size();
        for(int i = 0; i < n; ++i)
        {
            status& st = q.front();
            status tmp = st;
            // 进行扩散
            for(int i = 0; i < 4; ++i)
            {
                moveDir(st, i);
                // 扩散完成，如果 "新状态" 不等于旧状态，我们就进行入队操作
                if((st.x != tmp.x || st.y != tmp.y || st.dist != tmp.dist) && (dp[st.x][st.y] == -1 || dp[st.x][st.y] > st.dist))
                {
                    dp[st.x][st.y] = st.dist;
                    q.push(st);
                }
                st = tmp;
            }
        }  
        // 弹出刚刚检查过的状态 
        q.pop();
    }
    // res 存储的就是最终结果
    return dp[destination[0]][destination[1]];
}