#include "Solution.h"

bool Leetcode201_300::Solution::canFinish(int numCourses, vector<vector<int>>& prerequisites)
{
    // 很经典的拓扑排序类问题
    // 我们可以考虑使用 BFS 或者 DFS 的方式来执行拓扑排序并检查这个图中是否存在一条合法的遍历路径
    // 先尝试一轮 BFS 的实现方式
    queue<int> q;
    // 入度表，用于记录每个结点在当前遍历状态下的入度和出度
    vector<int> indegrees(numCourses, 0);
    // 先说明一下，BFS 之所以可以拿来执行拓扑排序，是基于这样的递归定义：
    // 所有入度为0的结点一定是某种意义上的拓扑序的起点，因为它们前面没有前驱了
    // 因而我们剥掉这一层皮，就相当于拿出来了一层起点，之后，就是一层更小的子拓扑排序问题(是的，你会发现，这又是某种形式上的递归定义)
    // 因而，只要确定这样的拓扑规则能不能覆盖到整张图，我们也就结束了关于课程选择是否合理的判断
    // 不过首先，我们需要对图进行预处理，整理出第一层入度为零的结点(也就是最外层的拓扑序列起点)
    int m = prerequisites.size();
    // 用另一个表转储整个临接链表
    unordered_map<int, vector<int>> adjacentList;
    // 遍历每个结点的临接表，取出对应的边信息，构建入度信息表
    for(int i = 0; i < m; ++i)
    {
        int n = prerequisites[i].size();
        // 更新对应的入度
        ++indegrees[prerequisites[i][0]];
        adjacentList[prerequisites[i][1]].push_back(prerequisites[i][0]);
    }
    // 循环结束后，我们就拿到了所有结点的入度信息，同时也拿到了方便检查的临接链表
    // 再遍历一遍整个入度表，把所有入度为0的结点添加到 BFS 队列中
    for(int i = 0; i < numCourses; ++i)
    {
        if(indegrees[i] == 0)
        {
            q.push(i);
        }
    }
    // 开始执行 BFS 遍历
    // 注意，我们需要记录已经访问过了几个结点
    // 判断是否能够完成所有课程学习的标准是：BFS 结束后是否已经访问了 numCourses 个结点
    int cnt = 0;
    while(!q.empty())
    {
        // 取出一个入度为零的结点
        int cur = q.front();
        ++cnt;
        q.pop();
        // 把它标记为已访问，不能再返回
        indegrees[cur] = -1;
        // 通过临接表遍历所有当前结点发出的边
        for(int i = 0; i < adjacentList[cur].size(); ++i)
        {
            if(--indegrees[adjacentList[cur][i]] == 0)
            {
                // 如果对应的后继结点的入度变成了零，就把它添加到队列中
                q.push(adjacentList[cur][i]);
            }
        }
    }
    return cnt == numCourses;
}

bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
{
    // 我们尝试改用 DFS 实现一遍拓扑排序
    int m = prerequisites.size();
    vector<vector<int>> adjacentList(numCourses, vector<int>());
    // 注意到拓扑排序的基本特征是，在整张图中，所有处在 "同一层" 上的结点应该是挨在一起的
    // 层与层之间的关系是根据它们距离选定的起点结点之间的距离决定的
    // 根据这个特性，我们可以结合 DFS 的性质总结出下面的方案
    // 定义一个深搜的过程函数，这个函数完成下面的工作：
    // dfs(u) 判断从结点 u 出发是否存在一个合法的拓扑序列
    // 预处理邻接表
    for(int i = 0; i < m; ++i)
    {
        int n = prerequisites[i].size();
        adjacentList[prerequisites[i][1]].push_back(prerequisites[i][0]);
    }
    // 由于 DFS 的独特性质，我们需要记录一个所有结点的当前状态数组，这个数组用于判别两个结点是否同在一条深搜路径上，如果出现两个结点在同一个深搜路径上，而后加入的结点却有指向这个统一路径上前驱结点的情况
    // 那么我们就可以断定原图上存在至少一个环，而有环的图是不可能存在任何有效的拓扑序列的
    // 记忆化变量，记录根据当前的信息，能否推断原图中是否有环
    bool noCycle = true;
    // 存储所有结点的状态信息，初始为全零，代表它们全都 "未访问"
    vector<int> status(numCourses, 0);
    stack<int> stk;
    function<void(int)> dfs = [&](int u)
    {
        // 边界情况需要用到邻接表信息，我们在上面做一些预处理  
        // 更新当前这个结点的状态信息，说明它 "正在被访问"，状态值为1
        status[u] = 1;
        // 对其所有邻接结点进行访问
        for(const int& v : adjacentList[u])
        {
            if(status[v] == 0)
            {
                // 一个未访问过的新结点，就对它进行访问
                dfs(v);
                // 如果访问结束后发现原图中有环，可以提前退出，结束 DFS，因为没必要再检查了
                if(!noCycle)
                {
                    return;
                }
            }
            else if(status[v] == 1)
            {
                // 发现一个和当前结点同处某一条深搜路径上的结点也有指向自己的边，这就说明了一个环的存在，我们可以记录到 noCycle 变量中进行记忆化
                noCycle = false;
                return;
            }
        }
        // 否则，已经成功检查了当前结点的所有可行后继结点，并且没有发现任何环，我们明白这个结点已经访问完成了，标记它的状态为 "已访问"
        status[u] = 2;
        // 注意到当前结点已经可以添加到栈中，作为隐式的 "当前层" 的结点之一
        stk.push(u); 
    };
    // 进行函数调用即可
    for(int i = 0; i < numCourses && noCycle; ++i)
    {
        if(status[i] == 0)
        {
            dfs(i);
        }
    }
    // 检查 noCycle 变量，看循环是不是因为有环彩退出的
    if(!noCycle)
    {
        return false;
    }
    // 否则，这个有效的拓扑序列就记录在了 stk 中，可以直接返回 true
    return true;
}