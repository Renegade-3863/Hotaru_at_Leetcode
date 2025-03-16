#include "Solution.h"

int Leetcode601_700::Soltuion::findLengthOfLCIS(vector<int>& nums)
{
    // 依然是经典的 DP 类型问题
    function<int(int)> dfs = [&](int i) -> int 
    {
        // 最小子问题：i == 0，只有一个元素，只能是自成一个子序列了
        if(i == 0)
        {
            return 1;
        }
        // 其余为一般情况
        // 默认结果为 1，后续循环可能会更新
        // 题目要求的是子数组。。那你为什么还要写子序列这个词。。
        // 那就更简单了，直接检查 dfs(i-1) 即可
        if(nums[i-1] < nums[i])
        {
            return dfs(i-1)+1;
        }
        // 如果 nums[i-1] >= nums[i]，那么一定没法拿到更长的子序列，直接返回 1 即可
        return 1;
    };
    int n = nums.size(), ans = 0;
    for(int i = 0; i < n; ++i)
    {
        ans = max(ans, dfs(i));
    }
    return ans;
}

// dp 形式的代码就不写了。。这题还可以对数组进行压缩，也很简单，也不写了吧。。