#include "Solution.h"

int Leetcode701_800::Soltuion::networkDelayTime(vector<vector<int>>& times, int n, int k)
{
    // 比较经典的 Dijkstra 算法模版题
    // 思路是这样的：
    // 我们可以求出 times 给出的 n 个结点中，每一个结点到结点 k 的最短路径长度
    // 之后这些最短距离中最长的那一个值就是最终的结果
    // 简单回顾一下 Dijkstra 算法的原理：
    // 我们用一个优先队列来保存所有 n 个结点到源结点 k 的最短距离 d
    // 所有的最短距离 d 初始化为无穷大
    // 之后把 k 结点的最短距离 d[k] 初始化为 0
    // 之后对所有与 k 结点相邻的结点进行松弛操作，不知道松弛操作是什么的，可以去查一下 《算法导论》
    // 把松弛之后，这些与 k 相邻结点的 d 值添加到优先队列中
    // 之后我们从这个优先队列中取出距离最小的那一个结点，添加到最短路径集合中即可
    // 之后每次添加一个新的结点，我们就对它的所有相邻，且不在最短路径集合中的结点进行松弛操作
    // 直到我们的优先队列中不再剩下任何结点为止
    // 之后，我们检查是不是所有的结点都被访问过了
    // 如果不是，我们直接返回 -1，否则我们可以在上述过程中记录一个最远距离变量
    // 返回这个最远距离变量即可
    // 变量初始化：
    // 一个用于存储最终结果的变量
    int res = 0;
    // 之后是一个优先队列，用于存储目前可访问到，并且不在最短路径集合中的结点
    // 注意，我们要记录每一个结点的序号和它的最短距离，因此需要在优先队列中存储一个 pair
    // 假设我们存储的 pair 是 (d, i)，表示结点 i 的预测最短距离为 d
    struct cmp
    {
        bool operator()(const pair<int, int>& a, const pair<int, int>& b)
        {
            // 要的是一个小顶堆
            // 因此我们要把距离小的结点放在前面
            return a.first > b.first;
        }
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
    // 题目给出的存储结构并不适配 Dijkstra 算法的流程
    // 我们需要进行转储
    // 应该存储为如下结构：
    // graph[i] = {j, w} 表示结点 i 到结点 j 的距离为 w
    // 所以我们用一个哈希表来存储这个结构
    unordered_map<int, vector<pair<int, int>>> graph;
    // 之后我们遍历 times 数组，构建这个哈希表
    for(const auto& time : times)
    {
        // time[0] 到 time[1] 的距离为 time[2]
        graph[time[0]].emplace_back(time[1], time[2]);
        // cout << "time[0]: " << time[0] << endl;
    // cout << graph[time[0]][0].first << ", " << graph[time[0]][0].second << endl;
    }
    // 之后我们把和 k 结点相邻的结点的距离更新到优先队列中
    for(const auto& p : graph[k])
    {
        // 对于每一个和 k 结点相邻的结点，我们进行松弛操作
        // p.second 表示结点 p.first 到结点 k 的距离
        // p.first 表示对应的结点序号
        // 遵照上面的定义，我们像这样进行添加即可
        pq.emplace(p.second, p.first);
    }
    // 清除 graph[k]，因为它已经不再需要了
    // 至此，初始化工作完成，可以正式开始 Dijkstra 算法了
    // 额外用一个变量来记录访问过的结点个数，最后只要这个值等于 n，那么我们就可以认为所有结点可达
    // 否则我们就认为无法访问到所有结点，此时返回 -1 即可
    // 默认值为 1，因为 k 结点自身是可以访问的
    int visited = 1;
    unordered_set<int> vSet;
    vSet.insert(k);
    while(!pq.empty())
    {
        // 取出距离最小的结点
        auto [d, i] = pq.top();
        pq.pop();
        if(vSet.count(i))
        {
            continue;
        }
        // 我们遍历 graph[i]，对它的每一个相邻结点尝试进行松弛操作
        for(const auto& p : graph[i])
        {
            // 如果 vSet.count(p.first)
            pq.emplace(d + p.second, p.first);
        }
        vSet.insert(i);
        // 最后，别忘了更新 res
        res = max(res, d);
        // 无论如何，我们都多访问了一个结点，对 visited 加一    
        ++visited;
    }
    // 之后我们检查 visited 是否等于 n
    // 如果是，我们就返回 res
    // 否则我们就返回 -1
    return visited == n ? res : -1;
}