#include "Solution.h"

vector<int> Leetcode301_400::Solution::lexicalOrder(int n)
{
    // 很简单的 DFS 类问题
    // 我们只需要 DFS 模版搜索整棵深搜树，并剪掉那些大于了 n 的结点即可
    // 我们从 1 开始，遍历 [0, 9] 这十个值并深入填数即可
    vector<int> res;
    // cur 代表当前的数字
    function<void(int)> dfs = [&](int cur) 
    {
        // 是一个合法值，我们进行记录
        if(cur <= n)
        {
            res.push_back(cur);
        }
        // 对于当前的 cur，我们需要尝试往 cur 后面再填入一个 [0, 9] 之间的数
        for(int i = 0; i <= 9; ++i)
        {
            // 注意防溢出
            // cur*10+i <= INT_MAX
            if(cur <= INT_MAX/10-i && cur*10+i <= n)
            {
                dfs(cur*10+i);
            }
        }
    }; 
    for(int i = 1; i <= 9; ++i)
    {
        // 根据回溯树确定开始点
        dfs(i);
    }
    return res;
}   