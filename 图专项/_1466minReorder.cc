class Solution
{
public:
    int minReorder(int n, vector<vector<int>>& connections)
    {
        // 读题，发现这是一个树的问题，而不是广义图的问题
        // 换句话说，如果要实现题目中的保证，实际上有下面的隐含条件：
        // 整张图是连通的，且两个节点之间至多只有一条边（方向不定）
        // 我们可以做出下面的判断：
        // 在这样的条件下，每个节点都必须有一条指向 ”与节点 0 连通“ 的节点
        // 因此，我们可以直接用类似 BFS 的方式来处理这道题
        // 具体为：
        // 取出 ”当前最外层的，与节点 0 连通的节点“，之后探查它们 ”指向“ 的其它节点
        // 把这些 ”指向“ 边变为 ”汇聚“ 边
        // 通过这样的方式，我们就能实现最少次数的修改
        // 上述方案基于一个这样的事实：
        // 树中不会存在任何一个在无向边意义下的连通回路
        // 所以这种 ”指向“ 的其它节点，不可能有其它边 ”汇聚“ 回 0 节点
        // 因为如果存在这样的路径，那么原有向图就不可能是 ”树“ 形结构
        // 所以我们用一个 BFS 进行遍历即可
        unordered_map<int, vector<int>> mapping;
        unordered_map<int, vector<int>> remapping;
        unordered_set<int> memo;
        for(const auto& connection : connections)
        {
            // 对每个 connection，记录对应的 “指向” 关系
            mapping[connection[0]].push_back(connection[1]);
            // 同时记录 "汇聚" 关系
            remapping[connection[1]].push_back(connection[0]);
        }
        // 执行 BFS，记录结果
        int time = 0;
        queue<int> q;
        q.push(0);
        memo.insert(0);
        while(!q.empty())
        {
            int n = q.size();
            for(int i = 0; i < n; ++i)
            {
                int cur = q.front();
                q.pop();
                // 检索 cur 所有的 “指向" 边，加入队列中，同时记录一次修改次数
                for(const auto& connection : mapping[cur])
                {
                    if(memo.find(connection) != memo.end())
                    {
                        continue;
                    }
                    ++time;
                    q.push(connection);
                    memo.insert(connection);
                }
                // 把所有指向来 cur 的节点也都加入到队列中，注意防止已经连通到节点 0 的节点被重新添加
                for(const auto& connection : remapping[cur])
                {
                    if(memo.find(connection) == memo.end())
                    {
                        q.push(connection);
                        memo.insert(connection);
                    }
                }
            }
        }
        return time;
    }
};