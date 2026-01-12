class Solution
{
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph)
    {
        // 可以用回溯法来找，不难做
        // path 用于记录当前的遍历路径
        int n = graph.size();
        vector<int> path;
        path.push_back(0);
        vector<vector<int>> res;
        function<void(int&)> backtrack = [&](int& node)
        {
            // 如果 node == n-1，那么说明我们已经找到来一条可以访问到 n-1 的路径，记录到结果列表中即可
            if(node == n-1)
            {   
                res.push_back(path);
                return;
            }
            // 否则，还没走到 n-1，我们需要进一步遍历 node 的后继节点
            for(auto& nxtNode : graph[node])
            {
                // 题目限定了 DAG，所以这里不用担心走出环路
                path.push_back(nxtNode);
                backtrack(nxtNode);
                // 回溯
                path.pop_back();
            }
        };
        // 调用即可
        int startNode = 0;
        backtrack(startNode);
        return res;
    }
};