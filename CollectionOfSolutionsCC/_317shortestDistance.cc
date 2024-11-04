#include "Solution.h"

// 最容易理解的暴力 BFS，TLE 了。。。
int Leetcode301_400::Solution::shortestDistance2(vector<vector<int>>& grid)
{
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    // 本题只能想到最暴力的解法，选出每一个可能的备选格子，从这些格子向外不断 BFS 遍历，直到触到所有的房子，每碰到一间房子，我们累计一次对于该结点，需要的最少总步数
    // 直到我们检查完所有可行结点，比较这些格子的最优值即可找出最终结果
    // 不用多说了，写代码即可
    int m = grid.size(), n = grid[0].size();
    // 记录一个全局的最小值结果
    int res = INT_MAX;
    // 预处理一遍整张图，检查一共有多少栋房屋
    int cnts = 0;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(grid[i][j] == 1)
            {
                ++cnts;
            }
        }
    }
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            // 外层遍历网格图中的所有格子
            // 先检查当前格子是不是一块合法的 "空地"
            // 只有空地我们才需要检查
            if(grid[i][j] == 0)
            {
                // 重置一个当前 BFS 遍历已经访问过的建筑个数
                int visited = 0;
                // 准备开始针对当前格子的 BFS 遍历过程
                // 初始化一个队列，用于当前次的 BFS
                queue<pair<int, int>> q;
                // 先把最开始的这个结点添加到队列中
                q.emplace(i, j);
                // 记录一个 BFS 的步骤数
                int steps = 0;
                int curRes = 0;
                // 记录 BFS 已经访问过的结点，防止重复遍历导致死循环
                unordered_set<int> memo;
                memo.insert(i*n+j);
                // 最外层的循环结束条件就是正常的 BFS 退出条件，不过我们内部可以做剪枝
                while(!q.empty())
                {
                    // 一个已经知道的退出条件是：我们已经找到了从当前起点到所有其它房屋的最短距离
                    // 为了实现这一点，我们需要记录当前图中一共有几栋房屋
                    // 在前面预处理一下
                    // 不过退出条件不应该在每一层循环开始的时候检查，我们可以在内部就进行退出操作
                    // 对当前层所有格子进行处理
                    int counts = q.size();
                    for(int k = 0; k < counts; ++k)
                    {
                        // 弹出一个当前层结点
                        const auto& cur = q.front();
                        // 检查它是个什么东西
                        // 1. 是一块空地
                        if(grid[cur.first][cur.second] == 0)
                        {
                            // 那么我们在修改 steps 前，需要继续从这个结点向四个方向扩散，不过要注意记录访问过的结点，防止重复遍历导致死循环
                            for(int t = 0; t < 4; ++t)
                            {
                                int nxtx = cur.first+dirs[t][0], nxty = cur.second+dirs[t][1];
                                // 检查合法性
                                if(nxtx >= 0 && nxtx < m && nxty >= 0 && nxty < n && memo.find(nxtx*n+nxty) == memo.end())
                                {
                                    memo.insert(nxtx*n+nxty);
                                    q.push(make_pair<int&, int&>(nxtx, nxty));
                                }
                            }
                        }
                        // 2、3. 是一栋建筑/障碍物，注意，题目要求是建筑也不能通过，只能作为终点，所以我们把它的处理逻辑和障碍物进行合并
                        else if(grid[cur.first][cur.second] == 1)
                        {
                            // 此时，如果本身是一栋建筑，那么我们需要更新 curRes
                            curRes += steps;
                            // 内层退出条件
                            if(++visited == cnts)
                            {
                                break;
                            }
                        }
                        // 记录当前格子已经访问过了，防止重复访问
                        // 否则，是一个障碍物，那么我们什么也做不了，只能简单地把这个结点丢掉
                        q.pop();
                    }
                    // 外层退出条件
                    if(visited == cnts)
                    {
                        break;
                    }
                    // 多走一步
                    ++steps;
                }
                // 更新全局的最小结果
                // 注意：只有当我们成功访问了所有房屋的时候，才能对最终结果进行更新
                res = visited == cnts ? min(res, curRes) : res;
            }
        }
    }
    return res == INT_MAX ? -1 : res;
}


// 借鉴了一下题解给出的剪枝策略，如果某次 BFS 发现当前起点没法到达所有房屋，那么我们直接标记该位置为 -1
// 在后续的遍历过程中，每当我们检查到一个被标记为 -1 了的结点，那么我们就不用费力检查这个下一跳了
int shortestDistance2(vector<vector<int>>& grid)
{
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    // 本题只能想到最暴力的解法，选出每一个可能的备选格子，从这些格子向外不断 BFS 遍历，直到触到所有的房子，每碰到一间房子，我们累计一次对于该结点，需要的最少总步数
    // 直到我们检查完所有可行结点，比较这些格子的最优值即可找出最终结果
    // 不用多说了，写代码即可
    int m = grid.size(), n = grid[0].size();
    // 记录一个全局的最小值结果
    int res = INT_MAX;
    // 预处理一遍整张图，检查一共有多少栋房屋
    int cnts = 0;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(grid[i][j] == 1)
            {
                ++cnts;
            }
        }
    }
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            // 外层遍历网格图中的所有格子
            // 先检查当前格子是不是一块合法的 "空地"
            // 只有空地我们才需要检查
            if(grid[i][j] == 0)
            {
                // 重置一个当前 BFS 遍历已经访问过的建筑个数
                int visited = 0;
                // 准备开始针对当前格子的 BFS 遍历过程
                // 初始化一个队列，用于当前次的 BFS
                queue<pair<int, int>> q;
                // 先把最开始的这个结点添加到队列中
                q.emplace(i, j);
                // 记录一个 BFS 的步骤数
                int steps = 0;
                int curRes = 0;
                // 记录 BFS 已经访问过的结点，防止重复遍历导致死循环
                unordered_set<int> memo;
                memo.insert(i*n+j);
                bool inValid = false;
                // 最外层的循环结束条件就是正常的 BFS 退出条件，不过我们内部可以做剪枝
                while(!q.empty())
                {
                    // 一个已经知道的退出条件是：我们已经找到了从当前起点到所有其它房屋的最短距离
                    // 为了实现这一点，我们需要记录当前图中一共有几栋房屋
                    // 在前面预处理一下
                    // 不过退出条件不应该在每一层循环开始的时候检查，我们可以在内部就进行退出操作
                    // 对当前层所有格子进行处理
                    int counts = q.size();
                    for(int k = 0; k < counts && !inValid; ++k)
                    {
                        // 弹出一个当前层结点
                        const auto& cur = q.front();
                        // 检查它是个什么东西
                        // 1. 是一块空地
                        if(grid[cur.first][cur.second] == 0)
                        {
                            // 那么我们在修改 steps 前，需要继续从这个结点向四个方向扩散，不过要注意记录访问过的结点，防止重复遍历导致死循环
                            for(int t = 0; t < 4; ++t)
                            {
                                int nxtx = cur.first+dirs[t][0], nxty = cur.second+dirs[t][1];
                                // 检查合法性
                                if(nxtx >= 0 && nxtx < m && nxty >= 0 && nxty < n && memo.find(nxtx*n+nxty) == memo.end())
                                {
                                    memo.insert(nxtx*n+nxty);
                                    q.push(make_pair<int&, int&>(nxtx, nxty));
                                }
                            }
                        }
                        // 2、3. 是一栋建筑/障碍物，注意，题目要求是建筑也不能通过，只能作为终点，所以我们把它的处理逻辑和障碍物进行合并
                        else if(grid[cur.first][cur.second] == 1)
                        {
                            // 此时，如果本身是一栋建筑，那么我们需要更新 curRes
                            curRes += steps;
                            // 内层退出条件
                            if(++visited == cnts)
                            {
                                break;
                            }
                        }
                        // 记录当前格子已经访问过了，防止重复访问
                        // 否则，是一个障碍物，那么我们什么也做不了，只能简单地把这个结点丢掉
                        // 注意，被标记为 -1 的结点具有 "传染性"
                        // 如果当前结点可以访问到一个被标记为 -1 的 "死结点"
                        // 那么很明显当前这个结点也没法访问到所有房屋，否则这个访问到的 -1 结点就不可能是 -1 结点了。。。
                        else if(grid[cur.first][cur.second] == -1)
                        {
                            inValid = true;
                            break;
                        }
                        q.pop();
                    }
                    // 外层退出条件
                    if(visited == cnts || inValid)
                    {
                        break;
                    }
                    // 多走一步
                    ++steps;
                }
                // 更新全局的最小结果
                // 注意：只有当我们成功访问了所有房屋的时候，才能对最终结果进行更新
                // 当前起点没法访问到所有房屋，我们把它的标记该为 -1
                if(visited < cnts)
                {
                    grid[i][j] = -1;
                }
                else
                {
                    res = min(res, curRes);
                }
                
            }
        }
    }
    return res == INT_MAX ? -1 : res;
}

// 兜兜转转按着答案思路改了半天还是超时。。。借了份能通过的答案来看，发现大致是因为去重操作的问题
// 这份能通过的答案使用了标记的方法，学到了。。。以后图的 BFS 也不用哈希表硬雷了，之前一直只会用哈希集合+搜索是否访问过的操作，现在发现一个标记变量就解决了。。。

#define FOR_EACH(i, s, e) for(size_t (i) = (size_t)(s); (i) < (size_t)(e); (i)++)
#define R_FOR_EACH(i, s, e) for(size_t i = (size_t)(s); (i) > (size_t)(e); (i)--)

#define FOR_EACH_IT(it, v) for(auto it = v.begin(); it != v.end(); it++)
#define R_FOR_EACH_IT(it, v) for(auto it = v.rcbegin(); it != v.rcend(); it++)



class Solution {
public:
    int shortestDistanceBfs(int x, int y, vector<vector<int>>& grid, vector<vector<int>>& visited, int &is_visited, int housse_count)
    {
        int sum = 0;
        queue<pair<pair<int, int>, int>> q1;
        q1.push(make_pair(make_pair(x, y), 0));
        int house_count_tmp = 0;
        int bad_node = 0;
        while (!q1.empty() && house_count_tmp < housse_count)
        {
            auto p = q1.front();
            int a, b, depth;
            depth = p.second + 1;
            pair<int, int> ps[4];
            ps[0].first = p.first.first - 1; ps[0].second = p.first.second;
            ps[1].first = p.first.first + 1; ps[1].second = p.first.second; 
            ps[2].first = p.first.first;     ps[2].second = p.first.second - 1; 
            ps[3].first = p.first.first;     ps[3].second = p.first.second + 1;
            FOR_EACH(i, 0, 4)   
            {
                a = ps[i].first ; b = ps[i].second;
                if (a >= 0 && a < grid.size() && b >= 0 && b < grid[0].size() && visited[a][b] != is_visited)
                {
                    if (visited[a][b] == -1)
                    {
                        // 说明该节点与 与那些不能到达所有房子的节点互联，则该节点也不能到达所有房子，这里直接停止bfs
                        goto err1;
                    }
                    visited[a][b] = is_visited;
                    if (grid[a][b] == 1)
                    {
                        house_count_tmp++;
                        sum += depth;
                    }
                    else if(grid[a][b] == 0)
                    {
                        q1.push(make_pair(make_pair(a, b), depth));
                    }
                }
            }
            q1.pop();
        }
    err1:
        if (house_count_tmp != housse_count)
        {
            // 说明该节点不能到达所有的房子，将其标记为-1
            visited[x][y] = -1;
            return 0;
        }
        return sum;
    }

    int shortestDistance(vector<vector<int>>& grid) {
        vector<vector<int>> visited = vector(grid.size(), vector<int>(grid[0].size(), 0));
        int visited_value = 1;

        int max_distance = INT32_MAX;

        int house_count = 0;
        FOR_EACH(i, 0, grid.size())
            FOR_EACH(j, 0, grid[0].size())
                if (grid[i][j] == 1)
                    house_count++;
                    
        FOR_EACH(i, 0, grid.size())
        {
            FOR_EACH(j, 0, grid[0].size())
            {
                if (grid[i][j] == 0)
                {
                    int distance = shortestDistanceBfs(i, j, grid, visited, visited_value, house_count);
                    visited_value += 1;
                    if (distance != 0)
                    {
                        if (distance < max_distance)
                        {
                            max_distance = distance;
                        }
                    }
                }
            }
        }
        if (max_distance == INT32_MAX) return -1;
        return max_distance;
    }
};
