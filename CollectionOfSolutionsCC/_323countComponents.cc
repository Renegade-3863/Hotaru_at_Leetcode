#include "Solution.h"

int Leetcode301_400::Solution::countComponents(int n, vector<vector<int>>& edges)
{
    // 本题有很多种解决方法，我们这里考虑使用并查集的方法来实现
    // 一个经典的并查集解法并不需要额外定义一个结构体，我们实际上只需要一组函数
    // 一个数组，用来代表所有结点在这个图中所属集合中的父结点，这个结构也用在了下面的 representative 函数中
    vector<int> parent(n, 0);
    function<int(int)> representative = [&](int node) -> int
    {
        // 本题我们使用数字来代表结点，所以这里需要一个函数来搜索某个结点属于的集合的代表元素
        if(parent[node] == node)
        {
            // 如果这个结点的父结点就是它自己，那么我们就找到了这个结点所在结点的代表结点，直接返回即可
            return node;
        }
        // 否则，我们需要沿 parent 回溯
        return representative(parent[node]);
    };
    // 我们还需要一个合并两个不属于同一个集合的结点的方法
    // 由于题目要求我们返回不同集合(连通分量)的数量，所以这里引入一个返回值用于更新全局的个数
    function<bool(int, int)> combine = [&](int node1, int node2) -> bool
    {
        // 先判断两个结点是否属于同意个集合
        int root1 = representative(node1);
        int root2 = representative(node2);
        // 只有两个结点所属集合不同的时候，我们才需要进行合并操作
        if(root1 != root2)
        {
            // 因为 root1 所在集合内的所有结点最终都会回溯到 root1 这个结点，我们直接把 root1 的父结点设为 root2 即可
            parent[root1] = root2;
            return false;
        }
        // 这里可以确保 node1 和 node2 属于同一个集合 
        return true;
    };
    // 初始化并查集
    for(int i = 0; i < n; ++i)
    {
        // 初始情况，每个结点自成一个集合
        parent[i] = i;
    }
    // 鉴于本题的要求，我们不用转储 edges 数组，直接对每条边上的两个结点执行合并操作即可
    int m = edges.size();
    int res = n;
    for(int i = 0; i < m; ++i)
    {
        if(!combine(edges[i][0], edges[i][1]))
        {
            // 每次发现两个结点不属于同一个集合，并且它们之间还有边相连，那么就把全局的分量个数减1
            --res;
        }
    }
    return res;
}