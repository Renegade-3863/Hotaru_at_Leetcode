#include "Solution.h"

// 一个基本的并查集数据结构，可以用一个一维数组来模拟，一维数组每一个下标对应对应序号的集合
int Leetcode501_600::Soltuion::findCircleNum(vector<vector<int>>& isConnected)
{
    // 基本的并查集类问题，我们思考一下如何设计一个标准的并查集数据结构
    // 并查集应该支持一些基本的操作方法
    // 第一：并查集需要支持判断一个元素所属的集合
    // 我们定义为 findSet(int elem)
    // 第二：并查集需要支持把一个元素合并到另一个元素所在的集合中
    // 我们定义为 union(int elem, int set)
    // 题目给出的图是以邻接矩阵的方式进行存储的
    // 我们需要从矩阵中提取取出相关信息
    int n = isConnected.size();
    vector<int> parent(n, 0);
    // 我们需要实现两个功能函数
    // 1. findSet(int elem)，用于在 unionSet 集合上找出 elem 所属集合的函数
    // 我们需要先明确：unionSet[i] 代表的是：elem 在它所在的集合中，直接相邻的 parent 元素值
    function<int(int)> findSet = [&](int elem) -> int
    {
        int cur = elem;
        // 我们根据 unionSet[cur] 的值，不断回溯，直到 unionSet[cur] == cur 本身为止
        while(cur != parent[cur])
        {
            cur = parent[cur];
        }
        return parent[cur];
    };
    // 2. unionSet(int i, int j) 合并两个元素所在的集合
    function<void(int, int, const int&, const int&)> unionSet = [&](int i, int j, const int& seti, const int& setj) -> void
    {
        // 考虑如何进行集合合并
        // 从本质上讲，我们只需要把 unionSet[seti] 改成 setj，或者把 unionSet[setj] 改成 seti 即可
        // 因为所有原来属于 seti 这个集合的元素，最后都会回归到 seti 这个值上，那么我们只要把源头修改了，就相当于把集合内所有元素都修改了
        parent[seti] = setj;
    };
    int res = n;
    // 我们初始化每一组元素
    for(int i = 0; i < n; ++i)
    {
        // 初始化，最开始，每个元素都是自己所在集合的代表元素
        parent[i] = i;
    }
    // 之后，我们遍历 isConnected 矩阵
    // 根据每一个从属关系来尝试对集合进行修改
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            // 如果 isConnected[i][j] == 1，那么说明元素 i 和元素 j 直接相连
            // 否则，说明两个元素并不直接相连
            if(isConnected[i][j])
            {
                // 我们先检查两个元素是否属于同一个集合
                // 如果已经属于同一个集合，我们不需要做任何事情
                // 否则，我们需要进行 union 合并
                int seti = findSet(i), setj = findSet(j);
                if(seti != setj)
                {
                    // 不属于同一个集合，那么我们需要进行合并
                    unionSet(i, j, seti, setj);
                    // 每合并一次，我们给 res 减 1 即可
                    // 因为合并一次，最终的总集合数会比当前集合总数减少 1
                    --res;
                }
                // 否则，已经属于同一个集合了，我们就不需要做任何事了
            }
        }
    }
    return res;
}