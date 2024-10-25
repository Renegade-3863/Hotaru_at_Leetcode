#include "Solution.h"

bool Leetcode201_300::Solution::validTree(int n, vector<vector<int>>& edges)
{
    // 基本的拓扑排序问题，我们只需要对这个无向图进行拓扑排序，检查是否可以完整地拿出 n 个结点即可
    // 用一个数组存储这个图中所有结点的度信息
    // 注意：n 个结点的树有一个最基本的性质：必须有 n-1 条边，因而我们可以先通过这个图中的边个数来预先判断它是否有可能是一棵树
    if(edges.size() != n-1) 
    {
        return false;
    }
    vector<int> indegree(n, 0);
    unordered_map<int, vector<int>> adjList;
    int m = edges.size();
    for(int i = 0; i < m; ++i)
    {
        // 对每条边连接的两个结点的度都加2(一个入度一个出度)
        indegree[edges[i][0]] += 2;
        indegree[edges[i][1]] += 2;
        // 记录邻接关系
        adjList[edges[i][0]].push_back(edges[i][1]);
        adjList[edges[i][1]].push_back(edges[i][0]);
    }
    // 使用一个队列进行拓扑排序
    queue<int> q;
    // 从数组中找出所有度为2度结点添加到队列中
    for(int i = 0; i < n; ++i)
    {
        if(indegree[i] == 2)
        {
            q.push(i);
        }
    }
    int cnt = 0;
    // 进行拓扑排序
    while(!q.empty())
    {
        // 弹出一个度为2的结点，这个结点是一个边缘结点
        int cur = q.front();
        ++cnt;
        q.pop();
        // 遍历它的所有相邻结点，对它们的度进行减2处理
        for(int i = 0; i < adjList[cur].size(); ++i)
        {
            indegree[adjList[cur][i]] -= 2;
            if(indegree[adjList[cur][i]] == 2)
            {
                q.push(adjList[cur][i]);
            }
        }
    }
    // 循环结束后，我们只需要判断 cnt 是否等于 n 即可
    // 注意，只有一个结点的图本身也是一棵树，我们需要特判
    return cnt == n || n == 1;
}