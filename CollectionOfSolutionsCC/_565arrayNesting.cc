#include "Solution.h"

int Leetcode501_600::Soltuion::arrayNesting(vector<int>& nums)
{
    // 本质上是 DFS 类问题
    // 基于环的本质特征，我们可以在 DFS 过程中，每访问过一个元素，就把它置为 -1
    // 直到 DFS 遍历遇到一个 -1，就更新最长环的结果
    // 定义 DFS 函数
    int res = 0, n = nums.size();
    function<void(int&, int)> dfs = [&](int& len, int idx) -> void
    {
        // 定义递归的结束条件：nums[idx] 为 -1
        if(nums[idx] == -1)
        {
            res = max(res, len);
            len = 0;
            return;
        }
        // 仍然可以往前走，我们把 nums[idx] 置为 -1
        int tmp = nums[idx];
        ++len;
        nums[idx] = -1;
        dfs(len, tmp);
        return;
    };
    // 我们遍历整个数组，如果 nums[i] 不为 -1，我们就调用 dfs 进行检查
    int len = 0;
    for(int i = 0; i < n; ++i)
    {
        if(nums[i] != -1)
        {
            dfs(len, i);
        }
        // 多加一个剪枝
        if(res > (n>>1))
        {
            return res;
        }
    }
    return res;
}