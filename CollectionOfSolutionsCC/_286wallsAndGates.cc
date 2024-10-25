#include "Solution.h"

void Leetcode201_300::Solution::wallsAndGates(vector<vector<int>>& rooms)
{
    // 经典的 BFS 算法问题
    // 我们考虑这样的方案：
    // 首先，距离从0开始递增，我们把所有一开始距离就是0的个子坐标添加到 BFS 队列中，之后按照正常的 BFS 策略进行一步步的递推即可
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int steps = 0;
    queue<pair<int, int>> q;
    // 对 rooms 数组进行遍历，把所有当前为 0 的格子添加到队列中
    int m = rooms.size(), n = rooms[0].size();
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(rooms[i][j] == 0)
            {
                // 添加这个为零的起点坐标到队列中
                q.push(make_pair<int&, int&>(i, j));
            }
        }
    }
    // 根据队列进行扩散
    while(!q.empty())
    {
        // 取出一个可扩散点
        // 走一步
        ++steps;
        // 使用引用，减少不必要的拷贝
        int cnt = q.size();
        for(int i = 0; i < cnt; ++i)
        {
            pair<int, int>& cur = q.front();
            // 对于拿到的这个格子，我们需要对它的上下左右四个方向进行探查
            for(int k = 0; k < 4; ++k)
            {
                // 拿出这个方向上的邻居格子
                int nexti = cur.first+dirs[k][0], nextj = cur.second+dirs[k][1];
                // 检查是否是一个合法的格子
                // 如果是一个合法的格子，那么同时还需要检查这个格子是不是一个障碍物格
                // 如果是一个障碍物格，那么它显然也不能进行任何扩散
                if(nexti >= 0 && nexti < m && nextj >= 0 && nextj < n && rooms[nexti][nextj] != -1)
                {
                    // 是一个合法的格子，也不是一面墙，那么我们可以进行更新
                    // 提问：是否有其它的情况可以判断这个邻居格子不用进一步扩散？
                    // 论断：
                    // 如果当前格子已知的 "最近距离" 值已经不大于我们当前的步数了，那么就可以不将其加入队列中进行后续更新了
                    // 是否正确？
                    // 考虑下面的逻辑
                    // 因为我们执行的是一个 BFS 过程
                    // 那么如果出现：从某个源头访问这个格子，所需的最少步数甚至不大于它已知的到达最少步数，那么从这个到达需要步数最少的源头到达当前这个格子，再往四周扩散，周围的所有格子所需的最少步数
                    // 都不可能比我们从现在这个源头出发的步数多了
                    // 换句话说，我们继续从当前的源头到达这个邻居格子，再往外进行扩散，都不会再有任何更优的信息可以获得了
                    // 那么显然也就没必要在这一邻居上进一步往外扩散了
                    // 明确了这个论断，我们要写代码就不难了
                    if(rooms[nexti][nextj] > steps)
                    { 
                        // 根据上面的论断，更新邻居结点，并把邻居压入队列中
                        rooms[nexti][nextj] = steps;
                        q.push(make_pair<int&, int&>(nexti, nextj));
                    }
                    // 否则，什么都不做
                }
            }
            // 结束处理后，再把当前队列头部的这个格子退出去
            q.pop();
        }
    }
    // 全部处理完成后，就可以返回了
    return;
}