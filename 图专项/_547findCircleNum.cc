class Solution
{
public:
    int findCircleNum(vector<vector<int>>& isConnected)
    {
        // 经典并查集
        // 我们可以自行设计一个并查集类
        // 之后使用并查集进行连通判断即可
        // 简便起见，不用实际做一个结构/类出来
        // 用一个数组模拟即可
        // 城市的总个数为 isConnected.size()
        int n = isConnected.size();
        // 声明出一个 “父节点索引数组” fathers
        vector<int> fathers(n, 0);
        // 声明出一个 "每个节点所属集合大小" 的数组，初始时，每个集合大小都是 1
        vector<int> setSizes(n, 1);
        // 初始化
        std::iota(fathers.begin(), fathers.end(), 0);
        // 定义几个 helper function
        function<int(int)> findFather = [&](int idx) -> int
        {
            // 递归查找或迭代查找均可
            // 这里用迭代进行
            int ret = idx;
            // 查找过程
            while(ret != fathers[ret])
            {
                ret = fathers[ret];
            }
            // 这里引入一下路径压缩，降低后续的查找难度
            while(idx != fathers[idx])
            {
                int tmp = fathers[idx];
                fathers[idx] = ret;
                idx = tmp;
            }
            // 返回结果
            return ret;
        };
        int res = n;
        // 遍历 isConnected 表，处理每一个连接信息
        for(int i = 0; i < n; ++i)
        {
            // 从逻辑上讲，我们只需要遍历一半即可
            for(int j = i; j < n; ++j)
            {
                // 如果 i 与 j 相连，那么尝试进行合并即可
                if(isConnected[i][j])
                {
                    // 首先检查 i 和 j 的 father 是否相同
                    int fi = findFather(i), fj = findFather(j);
                    // 只有二者所属集合不同时，才进行合并操作
                    if(fi != fj)
                    {
                        // 合并操作为：
                        // 判断两个集合哪一个更大，把更小的那个集合合并到较大的集合中即可
                        if(setSizes[fi] > setSizes[fj])
                        {
                            setSizes[fi] += setSizes[fj];
                            setSizes[fj] = setSizes[fi];
                            fathers[fj] = fi;
                        }
                        else
                        {
                            setSizes[fj] += setSizes[fi];
                            setSizes[fi] = setSizes[fj];
                            fathers[fi] = fj;
                        }
                        --res;
                    }
                }
            }
        }
        return res;
    }
};