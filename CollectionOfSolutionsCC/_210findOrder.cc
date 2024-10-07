#include "Solution.h"

vector<int> Leetcode201_300::Solution::findOrder2(int numCourses, vector<vector<int>>& prerequisites)
{
    // 本题我们被要求返回一个合法的拓扑排序序列，这是和 207 题唯一的区别
    // 其实很简单，我们依然可以用 BFS 来实现
    int m = prerequisites.size();
    // 还是先预处理一个入度数组
    vector<int> indegrees(numCourses, 0);
    // 以及一个邻接表
    unordered_map<int, vector<int>> adjacentList;
    for(int i = 0; i < m; ++i)
    {
        // 入度+1
        ++indegrees[prerequisites[i][0]];
        // 邻接链表进行记录
        adjacentList[prerequisites[i][1]].push_back(prerequisite[i][0]);
    }
    // BFS 用的队列
    queue<int> q;
    // 记录一个 "访问过" 数组，用于标记某个结点是否已经被 BFS 访问过
    vector<bool> visited(numCourses, false);
    // 填充所有第一层的结点(一开始就是入度为0的结点)
    for(int i = 0; i < numCourses; ++i)
    {
        if(indegrees[i] == 0)
        {
            q.push(i);
        }
    }
    vector<int> res;
    while(!q.empty())
    {
        int cur = q.front();
        cout << cur << endl;
        q.pop();
        visited[cur] = true;
        // 记录当前层的当前结点
        res.push_back(cur);
        // 遍历当前结点的所有邻接结点
        for(int j = 0; j < adjacentList[cur].size(); ++j)
        {
            // 只有当这个邻接结点没有访问过的时候，我们才对其进行访问
            cout << adjacentList[cur][j] << endl;
            if(!visited[adjacentList[cur][j]])
            {
                // 处理这个邻接结点的入度
                if(--indegrees[adjacentList[cur][j]] == 0)
                {
                    // 如果去掉当前的进入结点给出的一个入度，这个邻接结点的入度变成了零，我们就把它计入下一层中
                    q.push(adjacentList[cur][j]);
                }
            }
        }
    }
    // 出现这种情况代表原图中存在环，不存在任何合法的拓扑序列，我们之间返回空数组即可
    if(res.size() < numCourses)
    {
        return {};
    }
    return res;
}