#include "Solution.h"

int Leetcode401_500::Solution::trapRainWater(vector<vector<int>>& heightMap)
{
    // 学习一下官方的优先队列解法
    // 本质思想和 接雨水 I 是类似的，都是从本质上解决问题：
    // 每个格子上面可以接到的雨水量和它四周的邻接格子中的最短板高度有关
    // 我们按思路来做即可
    // 首先，有一件事是可以明确的：
    // 原矩形四条边上的所有格子都不可能存到水
    // 我们把这些板子高度存到一个优先队列中，这个优先队列是小顶堆
    if(heightMap.size() <= 2 || heightMap[0].size() <= 2)
    {
        return 0;
    }
    int m = heightMap.size();
    int n = heightMap[0].size();
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<vector<bool>> visit(m, vector<bool>(n, false));
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(i == 0 || i == m-1 || j == 0 || j == n-1)
            {
                pq.emplace(heightMap[i][j], i * n + j);
                visit[i][j] = true;
            }
        }
    }
    int res = 0;
    int dirs[] = {-1, 0, 1, 0, -1};
    while(!pq.empty())
    {
        pair<int, int> curr = pq.top();
        pq.pop();
        for(int k = 0; k < 4; ++k)
        {
            int nx = curr.second / n + dirs[k];
            int ny = curr.second % n + dirs[k+1];
            if(nx >= 0 && nx < m && ny >= 0 && ny < n && !visit[nx][ny])
            {
                if(heightMap[nx][ny] < curr.first)
                {
                    res += curr.first - heightMap[nx][ny];
                }
                visit[nx][ny] = true;
                pq.emplace(max(heightMap[nx][ny], curr.first), nx*n+ny);
            }
        }
    }
    return res;
}