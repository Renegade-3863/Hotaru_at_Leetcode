#include "Solution.h"

// 网格图中的坐标点，包含横坐标和纵坐标两个维度的信息
struct Point
{
    int x;
    int y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

struct hashFunc
{
    bool operator() (const Point& a) const
    {
        auto hasher = hash<int>();
        return hasher(a.x) ^ hasher(a.y);
    }
}; 

struct equalFunc 
{
    bool operator() (const Point& a, const Point& b) const
    {
        return a.x == b.x && a.y == b.y;
    }
};

bool Leetcode401_500::Soltuion::hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination)
{
    int m = maze.size(), n = maze[0].size();
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    // "一条路走到黑" 函数，命名为 evaluate
    function<void(Point&, int)> evaluate = [&](Point& p, int d) 
    {
        // 根据给定的 d 方向，不断地修改 p 的相应坐标，直到撞墙
        int dx = dirs[d][0], dy = dirs[d][1];
        // 如果下一步坐标合法，并且不是墙，就走下去
        while(p.x+dx >= 0 && p.x+dx < m && p.y+dy >= 0 && p.y+dy < n && maze[p.x+dx][p.y+dy] == 0)
        {
            p.x += dx;
            p.y += dy;
        }
        // 撞墙了，结束调用
    };
    // 比较常规的图论题目，我们考虑用 BFS 来进行处理，这样找出来是否能够在目的地停下的同时，还能找出对应的最短执行路径
    // 考虑用队列存储一组球在 "当前步数" 条件下可能处于的位置坐标点
    // 之后按照题目给出的条件进行递进判断即可
    // 为了避免 BFS 过程中重复添加同一个点 (BFS 可能会多次经过同一个点，这个应该不难懂)
    // 我们需要一个哈希集合存储所有访问过的结点
    unordered_set<Point, hashFunc, equalFunc> memo;
    // step 变量用于记录 "步数" 信息，这道题用不上，不过 迷宫 II 用得上
    // int step = 0;
    queue<Point> q;
    // 压入起点
    q.emplace(start[0], start[1]);
    // 队列为空时，BFS 完成
    while(!q.empty())
    {   
        int n = q.size();
        for(int i = 0; i < n; ++i)
        {
            // 每一轮，先弹出队列头部的一个点，从这个点往所有可能的四个方向进行发散
            // 用引用，减少拷贝次数
            Point& p = q.front();
            // 注意，题目要求我们做的是：确认终点是否可达，那么我们需要做的就是在这里检查：p 是否等于 destination (坐标层级上)
            if(p.x == destination[0] && p.y == destination[1])
            {
                return true;
            } 
            Point tmp = p;
            // 遍历全部四个方向
            for(int d = 0; d < 4; ++d)
            {
                // 往这个新方向一直走，直到走不下去为止，我们可以根据这个逻辑写一个调用函数
                // 这个函数接收一个结点的引用，返回时这个结点的坐标应该是沿着对应方向走到底最远可以到达的位置
                // 我们只需要检查：
                // 1. 这个结点是不是就是 p 本身
                // 2. 这个结点是否已经被添加到 q 中过
                // 只要有任何一个条件的结果是 "是"，那么这个结点就可以被跳过了
                // 出发点还是 p 本身，我们可以利用 p 进行 evaluate 函数，但是别忘了每轮循环前重置
                Point newPoint = Point(p.x, p.y);
                evaluate(p, d);
                // 检查 p 是否等于 tmp
                if(p.x == tmp.x && p.y == tmp.y)
                {
                    // 走不下去，那么跳过压队和重置步骤
                    continue;
                }
                // 是一个新点，还要检查是不是一个已经添加过的点
                if(memo.count(p))
                {
                    // 添加过，我们不重复添加，重置并跳过
                    p = tmp;
                    continue;
                }
                // 是不同点，并且没添加过，那么我们记录并添加
                memo.insert(p);
                q.emplace(p.x, p.y);
                // 重置
                p = tmp;
            }
            // 弹出队头元素
            q.pop();
        }
    }
    // 全遍历完了，也没返回 true，说明不可达，返回 false
    return false;
}