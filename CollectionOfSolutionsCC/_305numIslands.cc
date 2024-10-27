#include "Solution.h"

vector<int> Leetcode301_400::Solution::numIslands2(int m, int n, vector<vector<int>>& positions)
{
    // 假设当前要考察的变换结点坐标为 (i, j) 
    // 那么我们在把 graph[i][j] 变成 1 之外，还需要检查一点：这个位置上、下、左、右是否存在相邻的 1
    // 存在的情况也需要进行分类讨论：
    // 1. 只存在一个相邻的1，那么很明显岛屿总数不会变
    // 2. 存在多于一个相邻的1，那么我们需要检查这些位置上的1一共属于多少个不同岛屿
    // 假设这些 1 属于 k 个不同的岛屿，那么合并后，总的岛屿数变为 n-k+1 (n 为原本的总岛屿数)
    // 3. 不存在相邻的1，那么很明显岛屿总数会加1
    // 具体有两个难点：
    // 1) 如何确定四周的1属于几个岛屿？ 这可以通过并查集来实现
    // 2) 如何实现题目要求的 O(klog(mn)) 复杂度？
    // 实际的要求就应该是：如何在 O(log(mn)) 的复杂度内确认一个点属于哪个集合？
    // 最暴力的方法是，先默认新添加的这个结点属于一个新的岛屿(集合)
    // 之后，检查当前坐标 (i, j) 和其它所有相邻的为 1 的结点是否属于同一个集合，如果不是，就把总岛屿个数减1
    // 简单说明一下上面做法的正确性：
    // 如果四周有一个1，那么上面的操作会把最开始添加的那一个岛屿删掉
    // 后续再有1，因为新添加的这个1已经被合并到了一个岛屿中，那么如果这个1和再有的这个1不属于同一个岛屿，那么我们相当于又链接了两个原本不相连的岛屿，我们也应该把总岛屿个数减1
    // 以此类推即可
    // 最后剩下的问题就是如何设计并查集结构了
    // 其实最简单的并查集实现只需要一个数组
    // 下面结合代码解释一下
    // 注意，这里为了简便起见，我们把二维的坐标压缩成一维的整数进行表示，方法是个人都应该知道了吧。。。
    // parent 记录每个结点属于哪一个点代表的集合
    // 最开始每个结点都属于自己代表的集合
    vector<int> parent;    
    // 初始化并查集的函数，我们对 parent 数组进行操作，标记每个结点属于他们自己代表的那个集合
    // 一个全局变量，动态记录当前的岛屿个数
    int count = 0;
    // 并查集的初始化函数
    function<void()> initUnionSet = [&]()
    {
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                parent.push_back(i*n+j);
            }
        }
    };
    // 用于检查一个结点所属集合的代表结点符号
    function<int(int)> find = [&](int node)
    {
        if(parent[node] != node)
        {
            return find(parent[node]);
        }
        return node;
    };
    // 判断两个结点是否属于同一个集合
    function<bool(int, int)> sameSet = [&](int i, int j) -> bool
    {
        // 只需要判断他们两个是否属于同一个结点代表的集合即可
        return find(i) == find(j);
    };
    // 四个方向的方向向量
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    // 之后的操作按上面的逻辑进行就可以了
    // 第一步，先初始化这个并查集
    initUnionSet();
    // 之后对每个修改点进行遍历
    int k = positions.size();
    // 我们不用存一整张网格图，只需要保存那些变为了1的位置即可
    unordered_set<int> memo;
    // 存储 k 次操作的最终结果
    vector<int> res;
    for(const auto& position : positions)
    {
        // 针对拿到的每个位置，第一步先判断它是否是一个 1，如果本身就是一个 1，那么就不用再修改了
        // 修改过了，直接跳过即可
        int cur = position[0]*n+position[1];
        if(memo.find(cur) != memo.end())
        {
            res.push_back(count);
            continue;
        }
        // 否则，没修改过，先对其进行修改
        memo.insert(cur);
        // 添加一个全局的集合(岛屿)个数
        ++count;
        // 之后向四个方向进行深入检查
        for(int i = 0; i < 4; ++i)
        {
            // 获取对应的邻居结点横纵坐标
            int nexti = position[0]+dirs[i][0], nextj = position[1]+dirs[i][1];
            // 检查合法性
            // 合法的一个点，并且是被标记成了1的点
            if(nexti >= 0 && nexti < m && nextj >= 0 && nextj < n && memo.find(nexti*n+nextj) != memo.end())
            {
                // 判断其与当前结点是否属于同一个集合
                // 不属于同一个集合，那么我们需要把它们合并，并减少一个总的集合个数
                int root1 = find(position[0]*n+position[1]);
                int root2 = find(nexti*n+nextj);
                if(root1 != root2)
                {
                    // 把它俩的代表结点的数据进行统一
                    parent[root1] = root2;
                    --count;
                }
            }
            // 否则，什么都不做
        }
        // 向 res 数组中添加当前操作的结果
        res.push_back(count);
    }
    // 操作全部结束，返回结果数组
    return res;
}