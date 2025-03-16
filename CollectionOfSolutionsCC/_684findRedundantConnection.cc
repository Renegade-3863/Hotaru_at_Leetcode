#include "Solution.h"

vector<int> Leetcode601_700::Soltuion::findRedundantConnection(vector<vector<int>>& edges)
{
    // 我们判断连通块总有一种很有趣，也很高效的解法：
    // 并查集
    // 这个数据结构允许我们通过任意一对边的关系来完成一个 "有关集合" 的填充
    // 并查集的数组链接形式已经足够完成这道题了
    // 首先，创建一个并查集数组 fathers，记录 n 个结点直接相连的父结点序号 
    int n = edges.size();
    vector<int> fathers(n, 0);
    // 初始状态下，每个结点的 father 都是它自己，代表每个结点都属于自己代表的集合
    for(int i = 0; i < n; ++i)
    {
        fathers[i] = i;
    }
    // 设计一个根据结点数据判断它所在集合的代表元素的函数
    function<int(int)> represent = [&](int i) -> int
    {
        int res = i;
        while(res != fathers[res])
        {
            res = fathers[res];
        }
        return res;
    };
    // 设计一个检查 i 和 j 两个结点是否属于同一个集合的函数
    // 如果 i 和 j 属于同一个集合，那么返回 true，否则，返回 false
    function<bool(int, int)> sameSet = [&](int i, int j) -> bool
    {
        return represent(i) == represent(j);
    };
    // 设计一个根据两个结点的相连关系修改 fathers 元素的函数
    // 这个函数我们设定一个先验条件：i 和 j 不属于同一个集合
    function<void(int, int)> update = [&](int i, int j) -> void
    {
        // 我们这里默认把 j 结点归到 i 结点所在的集合中
        int ri = represent(i);
        // 把 fathers[represent(j)] 改成 ri 即可
        int rj = represent(j);
        fathers[rj] = ri;
    };  
    // 之后，遍历 edges 集合，根据每一条 edge 对 fathers 数组进行修改
    for(auto& edge : edges)
    {
        if(sameSet(edge[0]-1, edge[1]-1))
        {
            return {edge[0], edge[1]};
        }
        // 不属于同一个集合，那么调用 update 函数更新即可
        update(edge[0]-1, edge[1]-1);
    }
    // make the compiler happy
    return {};
}