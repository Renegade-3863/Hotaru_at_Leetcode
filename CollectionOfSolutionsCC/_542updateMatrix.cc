#include "Solution.h"

vector<vector<int>> Leetcode501_600::Soltuion::updateMatrix(vector<vector<int>>& mat)
{
    // 暴力单源 BFS，会 TLE (37/50)
    // 因为对于每一 1，都会整体遍历一遍图，所以效率很低
    // 以每一个 '1' 为起点，开始 BFS 扩散，扩散过程状态记录每一个起点，每次遇到了 '0' 就结束这个状态的后续扩散，直到所有状态都扩散完成为止
    // 同时，应该注意到下面的事实：
    // 如果单纯地按照 BFS 暴力遍历，那么显然会检查很多重复的问题
    // 这里就可以引入 DP 记忆化的方法了
    // 我们考虑修改一下题目的问法：
    // 检查每一个格子到最近的 '0' 的距离 (如果本身就是 '0'，那么这个距离就定义为 0)
    // 但是我们只把那些原来为 '1' 的格子的距离作为输出结果
    // 基于这个想法，我们可以联用 BFS 和 DP
    // 记录一个额外的数组，定义为
    // dp[i][j]: mat[i][j] 到最近的 '0' 的距离
    int m = mat.size(), n = mat[0].size();
    // 初始化为全 0
    vector<vector<int>> dp(m, vector<int>(n, 0x3f3f3f3f));
    // 不用可以把所有初始值为 '0' 的 dp 值记录为 0，我们在 BFS 过程中用 mat[i][j] 的值就可以剪枝
    // 定义四个方向数组
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    // 遍历整个矩阵，遇到 '1' 就开始 BFS 遍历
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            // 如果 mat[i][j] 是 '1'，那么把坐标压入 q 队列，开始 BFS
            if(mat[i][j] == 1)
            {
                // 队列 q 用于 BFS 扩散
                queue<pair<int, int>> q;
                // 记录已经走过的步数
                int step = 0;
                q.emplace(i, j);
                // 新建一个矩阵，记录哪些坐标在本轮 BFS 中已经访问过了
                vector<vector<int>> visited(m, vector<int>(n, 0));
                visited[i][j] = true;
                while(!q.empty())
                {
                    // 多走一步
                    ++step;
                    int len = q.size();
                    bool found = false;
                    for(int k = 0; k < len && !found; ++k)
                    {
                        // 取出队头的一个坐标，进行最短距离检查
                        auto& p = q.front();
                        // 遍历四个方向
                        for(int t = 0; t < 4; ++t)
                        {
                            int nxtx = p.first+dirs[t][0], nxty = p.second+dirs[t][1];
                            // 这个新坐标必须是合法的！
                            if(nxtx < 0 || nxtx >= m || nxty < 0 || nxty >= n || visited[nxtx][nxty])
                            {
                                continue;
                            }
                            visited[nxtx][nxty] = true;
                            // 可以预先剪枝
                            if(dp[nxtx][nxty] != 0x3f3f3f3f)
                            {
                                dp[i][j] = min(dp[nxtx][nxty]+step, dp[i][j]);
                                continue; 
                            }
                            q.emplace(nxtx, nxty);
                            // 合法，更新最优距离
                            if(mat[nxtx][nxty] == 0)
                            {
                                // 遇到了第一个 0，此时我们就可以直接退出了
                                // 注意，由于上面的剪枝，这里有可能跳过最优的路径，所以我们依然要用 min 来限制一下求解
                                dp[i][j] = min(step, dp[i][j]);
                                found = true;
                                break;
                            }
                        }
                        // 弹出刚刚检查完的结果
                        q.pop();
                    }
                    // 已经找到了结果，那么退出循环即可
                    if(found)
                    {
                        break;
                    }
                }
            }
            else
            {
                dp[i][j] = 0;
            }
        }
    }
    return dp;
}

// 第二版，考虑优化成多源 BFS，提高运行效率
// 通常来讲，单纯的 "从开头找结尾" 的方法，总是时间效率很高，我们可以考虑使用反向的方法
// 从所有的 '0' 坐标处开始向外扩散，遇到一个 '1'，就把对应位置的 '最短距离' 设定为当前走的步数 (这个步数一定是最短路径长度)
vector<vector<int>> updateMatrix(vector<vector<int>>& mat)
{
    // 考虑这样的多源 BFS 方法
    // 我们把所有坐标上的值为 '0' 的坐标存入初始的队列中
    // 之后根据这个队列开始进行遍历
    queue<pair<int, int>> q;
    int m = mat.size(), n = mat[0].size();
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(mat[i][j] == 0)
            {
                q.emplace(i, j);
            }
        }
    }   
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    vector<vector<int>> res(m, vector<int>(n, 0));
    // 现在所有初始值为 '0' 的坐标都已经存储到了 BFS 队列中，我们可以开始进行多源 BFS 遍历了
    // step 变量记录当前层从各自的出发点 (一定是一个原始为 0 的点)，已经往外走了多少格
    int step = 0;
    while(!q.empty())
    {
        // 按层对坐标进行遍历
        int len = q.size();
        // 走出一步
        ++step;
        for(int i = 0; i < len; ++i)
        {
            // 取出当前的可扩散点
            auto& p = q.front();
            // 检查它的四个相邻位置
            for(int j = 0; j < 4; ++j)
            {
                int nxtx = p.first+dirs[j][0], nxty = p.second+dirs[j][1];
                // 但是，(nxtx, nxty) 这个坐标必须是在矩阵范围内的，并且是 "之前没有访问过的"
                // 对于这个 "没有访问过" 的检查，我们应用一种很精妙的技巧
                // 注意到这样的事实：任何的 '0'，要么不与任何 '1' 相邻，要么与至少一个 '1' 相邻
                // 所以我们可以遵循这样的逻辑来进行更新
                // 如果当前的 '0' 四周有相邻的 '1'，那么这个 '1' 到最近的 '0' 的距离就是 1
                // 这个新的 '1' 可以作为当前这个 '0' 的延伸，换句话说，既然距离这个 '1' 最近的 '0' 我们已经知道了
                // 那么其它可能存在一条通过这个 '1' 到达的最近的 '0' 也是当前的这个 '0' 
                // 这里就有些类似 DP 算法了
                if(nxtx >= 0 && nxtx < m && nxty >= 0 && nxty < n && mat[nxtx][nxty] == 1)
                {
                    res[nxtx][nxty] = step;
                    mat[nxtx][nxty] = 0;
                    q.emplace(nxtx, nxty);
                }
            }
            q.pop();
        }
    }
    return res;
} 
