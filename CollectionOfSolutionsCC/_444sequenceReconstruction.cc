#include "Solution.h"

bool Leetcode401_500::Solution::sequenceReconstruction(vector<int>& nums, vector<vector<int>>& sequences)
{
    // 虽然画一画图，理论上能看出来是拓扑排序类的问题，不过我还是想说，这道题如果不告诉你是拓扑排序，你真的能想到要用拓扑吗？
    // 个人认为 (马后炮)，本题适合用拓扑排序的特点在于：子序列的有序性
    // 即：超序列要包含所有的子序列，那么它必须包含所有子序列的顺序特征，这和拓扑排序的基本特质相吻合
    // 通过本题重新认识一下拓扑排序的基本作用是很不错的
    // 我们需要做的事情很简单，就是建图+拓扑遍历检出拓扑序列
    // 不过由于本题要求我们判断拓扑序列是否唯一，所以我们可能还需要写明一种机制来判断拓扑序是否唯一
    // 首先根据每个子序列内部的顺序关系建图，使用邻接表来实现即可
    unordered_map<int, unordered_set<int>> adjList;
    unordered_map<int, int> indegree;
    // 根据每一个 sequence 进行建图
    for(const auto& sequence : sequences)
    {
        // 按顺序遍历 sequence 中的每两个数字，进行关系链接
        int n = sequence.size();
        for(int i = 0; i < n-1; ++i)
        {
            if(adjList.find(sequence[i]) == adjList.end())
            {
                adjList[sequence[i]] = unordered_set<int>();
            }
            if(adjList[sequence[i]].find(sequence[i+1]) == adjList[sequence[i]].end())
            {
                // 对应入度加一
                ++indegree[sequence[i+1]];
                // cout << sequence[i+1] << ":" << indegree[sequence[i+1]] << endl;
                adjList[sequence[i]].insert(sequence[i+1]);
            }
        }
    }
    // 建图完成，我们后续根据 BFS 进行拓扑遍历，所以这里我们遍历一遍 adjList 提取出所有入度为 0 的结点
    // 并存储到一个队列中
    queue<int> q;
    for(const auto& num : nums)
    {
        if(indegree[num] == 0)
        {
            q.push(num);
        }
    }
    // 另加一个变量，用于判断拓扑排序是否完整覆盖了整个序列
    int visited = 0;
    while(!q.empty())
    {
        // cout << q.front() << endl;
        // 如果某一层的可选方向数不止一个，那么很明显这个序列的拓扑序不唯一，我们直接返回 false 即可
        if(q.size() > 1)
        {
            return false;
        }
        ++visited;
        // 否则，我们可以进一步进行拓扑排序
        // 将所有 q.front() 指向的结点的入度减1
        for(const auto& nxt : adjList[q.front()])
        {
            if(--indegree[nxt] == 0)
            {
                q.push(nxt);
            }
        }
        // 弹出刚检查完的元素
        q.pop();
    }
    return visited == adjList.size();
    }
}