class Solution
{
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph)
    {
        // 感觉是经典的 DFS 类问题
        // 基本思路很简单，定义这样的一个函数
        // dfs(i) 判断节点 i 是否是一个安全节点
        // 判断思路也很简单：检查所有与 i 相连的节点
        // 如果所有节点都是安全的，那么 i 本身也是安全的
        // 注意：终端节点本身也是安全节点
        // 注意，由于本题 dfs 的子问题性质，我们可以用类似 dp 的方式来优化
        unordered_map<int, bool> memo;
        // 记录递归的路径，如果一条路径上出现了重复的元素，那么这个重复元素代表的节点一定不是安全的，把它标记为 false，不再进一步 dfs，否则会死循环
        unordered_set<int> path;
        function<bool(int)> dfs = [&](int i) -> bool
        {
            // 检查 memo 是否有记录，有记录就不再重复判断
            if(memo.find(i) != memo.end())
            {
                return memo[i];
            }
            // cout << i << endl;
            // 否则，遍历 graph[i]，检查每一个相邻节点
            for(const auto& next : graph[i])
            {
                if(path.find(next) != path.end())
                {
                    // 发现了重复节点，标记 i 节点为 false，直接回退
                    memo[i] = false;
                    return false;
                }
                // cout << next << " ";
                path.insert(next);
                if(!dfs(next))
                {
                    // 只要有一个不是安全节点，就返回 false
                    memo[i] = false;
                    return false;
                }
                path.erase(next);
            }
            // cout << endl;
            // 当前节点是安全的，记录并返回
            memo[i] = true;
            return true;
        };
        // 遍历每个节点进行检查即可
        vector<int> res;
        for(int i = 0; i < graph.size(); ++i)
        {
            if(dfs(i))
            {
                res.push_back(i);
            }
        }
        return res;
    }
};