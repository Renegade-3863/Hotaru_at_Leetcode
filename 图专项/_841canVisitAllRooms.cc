class Solution
{
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms)
    {
        // 直接进行 DFS 遍历即可
        // 定义一个这样的函数：
        // dfs(i) 代表当前在序号为 i 的房间，并且手里有 path 这些钥匙（注意，这个参数不在函数体中记录，用全局变量表示）
        // 的情况下，是否可以进入所有房间
        // rem 代表剩余的，还未进入过的房间的数量
        int rem = rooms.size();
        // visited 代表每个房间的访问状态
        // 三种状态：
        // 0 -> 无钥匙，且未访问过
        // 1 -> 有钥匙，但未访问过
        // 2 -> 有钥匙，且已访问过
        // 只有状态 1，我们才能在内部对其进行访问
        vector<int> visited(rem, 0);
        function<bool(int)> dfs = [&](int i) -> bool
        {
            // 标记当前序号的房间为 2（注意，状态码 2 代表 ”有钥匙，且已访问过“，因为我们必然是拿着钥匙，才能进的来这个房间的
            // 0 号房间没有上锁，但是这里没区别，可以合并逻辑
            visited[i] = 2;
            // 我们不会重复访问状态码为 2 的房间，这里可以安全地对 rem 减 1
            if(--rem == 0)
            {
                // 如果已经完成访问，我们直接返回 true 即可
                return true;
            }
            // 否则，我们还需要看看当前状态下，我们还能去哪里
            // 检查 rooms[i]，看都有哪些房间的钥匙
            for(const int& key : rooms[i])
            {
                // “拿上” 所有房间的钥匙
                // 注意，如果对应房间已经访问过了，我们就不用再拿对应钥匙了，重复走一次没有意义
                if(visited[key] == 0)
                {
                    visited[key] = 1;
                }
            }
            // 拿好钥匙后，我们尝试对每个房间进行访问，看能否走完全程
            for(const int& key : rooms[i])
            {
                // 如果对应房间已经访问过了，没必要再走一遍
                if(visited[key] == 2)
                {
                    continue;
                }
                if(dfs(key))
                {
                    return true;
                }
            }
            // 否则，当前情况下，所有可能的下一步都试过了，没法走完全程，返回 false 即可
            return false;
        };
        return dfs(0);
    }
};