class Solution
{
public:
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime)
    {
        // 基础的回溯类问题，可以考虑建图后遍历实现
        // 主要是对数据转储，记录 员工 - 直属下属表 方便后续查用
        unordered_map<int, vector<int>> mapping;
        for(int i = 0; i < n; ++i)
        {
            // 员工 i 对应的直属 leader 是 manager[i]
            // 如果 manager[i] = -1，说明这个员工是 leader，不记录
            mapping[manager[i]].push_back(i);
        }   
        // 之后，使用 DFS 回溯遍历整张图，尝试找出权重最大的那条到达叶节点的路径即可
        // time 记录全局结果，path 记录当前遍历的结果
        int time = 0, path = 0;
        // backtrack(id) 代表遍历员工 ID 为 id 的员工的所有下属（包括非直属下属）
        // 并在过程中更新最大所需的通知时间
        function<void(int&)> backtrack = [&](int& id) -> void
        {
            // 如果当前员工已经是基层员工了，你们我们直接更新结果即可，使用 path 中记录的信息
            // 基层员工没有直属下属表
            if(mapping.find(id) == mapping.end())
            {
                time = max(time, path);
                // 回退
                return;
            }   
            // 否则，递归调用 backtrack，进行递归和回溯
            for(auto& newId : mapping[id])
            {
                // 递归
                // 注意，newId 是被 id 员工进行通知，通知所需时间为 informTime[id]
                path += informTime[id];
                // 递归调用
                backtrack(newId);
                // 回溯
                path -= informTime[id];
            }
        };
        // 因为只有一个总负责人，所以我们从它开始调用即可
        backtrack(headID);
        return time;
    }
};