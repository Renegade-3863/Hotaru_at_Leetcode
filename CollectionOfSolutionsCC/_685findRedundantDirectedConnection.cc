#include "Solution.h"

vector<int> Leetcode601_700::Soltuion::findRedundantDirectedConnection(vector<vector<int>>& edges)
{
    // 本质上是在一个有向图中找环的题目
    // 我们依然可以用并查集来完成这道题
    int n = edges.size();
    vector<int> fathers(n, 0);
    // 初始化
    for(int i = 0; i < n; ++i)
    {
        fathers[i] = i;
    }
    function<int(int)> represent = [&](int i) -> int
    {
        int res = i;
        while(fathers[res] != res)
        {
            res = fathers[res];
        }
        return res;
    };
    function<bool(int, int)> sameSet = [&](int i, int j) -> bool
    {
        return represent(i) == represent(j);
    };
    // 本题是有向图，所以我们规定 j 是被指向的结点，i 是指出的结点
    function<void(int, int)> update = [&](int i, int j) -> void
    {
        int ri = represent(i), rj = represent(j);
        fathers[rj] = ri; 
    };
    for(const auto& edge : edges)
    {
        if(sameSet(edge[0]-1, edge[1]-1))
        {
            // 找到了可以删除的边，我们把它删了即可
            return edge;
        }
        update(edge[0]-1, edge[1]-1);
    }
    // make the compiler happy
    return {};
}

// 别急，上面的解法单纯使用了和 684 完全一样的解法，其实是不正确的
// 有一个样例很好地击败了上面这种企图偷懒的解法：
// edges = [[2, 1], [3, 1], [4, 2], [1, 4]]
// 在纸上稍微画一下这个边集，我们就不难发现，按上面和 684 无向图一样的解法，我们只能找出 [1, 4] 这个最后一个完成 [2, 1, 4, 2] 这个环的边
// 而实际上，如果我们删去了这条边，那么我们整张图就不再是连通的了！
// 问题出在哪？
// 稍加分析，会发现：
// 给定有向图的情况下，最后一条补完一个环的边不一定是我们可以删除的边，它可能反而连接了某对原本不可达的结点
// 在上面这个例子中，[2, 1] 才是构成环了，并且需要被删除的那条边
// 进一步分析，[2, 1] 和 [3, 1] 这两条边都指向了结点 1
// 换句话说，在有环的情况下，如果这个环中没有任何一条边指向一个原本入度为1 (加上这个环中的边，该结点入度变为 2) 的结点，那么我们删除环中任何一条边都是可以的
// 不信的话，你试试把 edges 中的 [3, 1] 改成 [1, 3]，再分别尝试删除 [2, 1], [4, 2], [1, 4] 三条边中的任何一个
// 此时无论删除哪一条边，最后都是一棵合法的树
// 所以，我们可以有一个暂时的推论：
// 如果多加的那条边构造出了一个环，并且这个环中有一个入度为 2 的点，那么我们只能删除环中使得这个点入度变成 2 的那条边
// 否则，删除环中任何一条边都是可以的
// 至此，思路逐渐明确，写代码也就行云流水了
vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges)
{
    // 实际实现中，发现只记录结点的入度在找边的过程中会有一些信息缺失
    // 所以我们改成多加一个数组 parent，记录每个结点的父结点 (有向关系中的上一个结点)
    // 我们对上一版代码进行一些修改，以实现我们的目标
    int n = edges.size();
    vector<int> parent(n, 0);
    vector<int> fathers(n, 0);
    // 初始化
    for(int i = 0; i < n; ++i)
    {
        fathers[i] = i;
        // 初始，每个结点都是自己的父结点，我们还没有找到任何有效的连通路径
        parent[i] = i;
    }
    function<int(int)> represent = [&](int i) -> int
    {
        int res = i;
        while(fathers[res] != res)
        {
            res = fathers[res];
        }
        return res;
    };
    function<bool(int, int)> sameSet = [&](int i, int j) -> bool
    {
        return represent(i) == represent(j);
    };
    // 本题是有向图，所以我们规定 j 是被指向的结点，i 是指出的结点
    function<void(int, int)> update = [&](int i, int j) -> void
    {
        int ri = represent(i), rj = represent(j);
        fathers[rj] = ri; 
    };
    // tmp1 和 tmp2 用于记录可能的两个备选答案
    vector<int> tmp1(2, -1);
    vector<int> tmp2(2, -1);
    // tmp3 用于记录可能的环路边
    vector<int> tmp3(2, -1);
    for(const auto& edge : edges)
    {
        if(parent[edge[1]-1] == edge[1]-1)
        {
            // 此时 edge[1] 这个结点还没有父结点，那么记录这个关系
            parent[edge[1]-1] = edge[0]-1;
        }
        // 否则，parent[edge[1]-1] != edge[1]-1，那么说明前面已经记录过 edge[1] 这个结点的一个父结点了
        // 它的入度为 2，那么最后这两条边一定需要删除一个
        // 我们记录原先的那条边和这条边
        else
        {
            tmp1[0] = parent[edge[1]-1]+1;
            tmp1[1] = edge[1];
            tmp2[0] = edge[0];
            tmp2[1] = edge[1];
            continue;
        }
        // 我们这里没法完全确认 edge 就是可以删除的，有可能先成环，再出现入度为 2 的结点
        if(sameSet(edge[0]-1, edge[1]-1))
        {
            // 不过我们知道 edge 这条边构造出了环路，我们同样记录这条边
            tmp3[0] = edge[0];
            tmp3[1] = edge[1];
            continue;
        }
        update(edge[0]-1, edge[1]-1);
    }
    // 没有冲突边，我们直接返回 tmp3 即可
    if(tmp2[0] == -1)
    {
        return tmp3;
    }
    // 有冲突边，那么我们需要检查是否存在导致环路的边，如果有这样的边，那么它一定不是导致冲突的边，这是我们上面的逻辑确定的
    // 在某条边导致了冲突的时候，我们只会记录它导致了冲突，而如果它导致了环路，我们并不会记录它导致了环路
    // 所以，如果并没有记录到导致冲突的边，那么一定会有一条边导致了环路，我们返回这条导致环路的边即可
    // 而如果记录到了导致冲突的边，并且没有记录到导致环路的边
    // 那么一定是这条导致冲突的边造成了环路，我们返回这条冲突边即可
    // 反之，如果记录到了导致环路的边，那么一定不是这条冲突边造成的环路，而一定是另一条冲突边造成的环路
    // 而只有一条冲突边有可能在我们发现的这条环路中
    if(tmp3[0] != -1)
    {
        return tmp1;
    }
    return tmp2;
}