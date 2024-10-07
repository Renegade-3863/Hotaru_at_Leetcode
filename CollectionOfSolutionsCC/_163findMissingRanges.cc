#include "Solution.h"

// 针对 [lower, upper] 区间进行遍历，时间复杂度为 O(n)，表现超时，需要优化
vector<vector<int>> Leetcode101_200::Solution::findMissingRanges(vector<int>& nums, int lower, int upper)
{
    // 本题要求我们找出一个从小到大排序的整数数组中，所有存在于给定的大区间 [lower, upper] 中
    // 而不在 nums 中的数值的区间并集
    // 简单的想法应该就是单纯的傻瓜式遍历
    // 我们尝试进行模拟
    // 规定一个当前在寻找的数值区间 [left, right]，这个区间是我们现在找到的在 [lower, upper] 区间中而不在 nums 中的本地连续数值集合
    int left = lower, idx = 0;
    vector<vector<int>> res;
    // 由于 nums 中的元素是有序的，因而我们似乎不需要将 nums 中的数据再转存到一个哈希表中
    // 可以利用下面的关系：
    // nums 中最左侧还没被剔除的元素 val
    // 如果这个元素是大于 right 值的，那么我们不用动它，把 right 值记录到数值区间 [left, right] 中即可
    // 如果这个元素是不大于 right 值的，那么这个元素可以被剔除，因为我们后面枚举的 right 值都一定会是不小于它的
    // 注意：如果 val 是不小于 right 值的，那么我们需要先把左侧的区间添加到解集中(如果它不是一个空的区间)，并更新 left 指针
    int right = lower;
    while(right < n)
    {
        if(idx == nums.size() || right < nums[idx])
        {
            // 什么都不用做，跟着循环把 right 递增1即可
            ++right;
            continue;
        }
        // 否则一定有 right = nums[idx]
        else
        {
            if(left < right)
            {
                res.push_back({left, right-1});
            }
            ++idx;
            left = right+1;
            ++right;
        }
    }
    // 循环结束后，需要额外判断一下有没有最后一个区间还没添加
    if(left < right)
    {
        res.push_back({left, right-1});
    }
    return res;
}

vector<vector<int>> findMissingRanges(vector<int>& nums, int lower, int upper)
{
    // 前面对 [lower, upper] 区间进行遍历的方案可以很容易的被击垮，只需要把这个区间范围设置地很大即可
    // 这里我们转换思路，尝试改为对 nums 数组进行检查
    // 注意到 nums 数组中的每个值都是一个潜在的区间分割点，我们只需要额外再维护一个区间左端点 left 即可
    int left = lower;
    vector<vector<int>> res;
    // 枚举右端点，这些右端点由 nums 中的元素决定
    for(int i = 0; i < nums.size(); ++i)
    {
        if(nums[i] > left)
        {
            res.push_back({left, nums[i]-1});
        }
        // 更新下一个可能的区间左端点
        left = nums[i]+1;
    }
    // 别忘了最后一个区间
    if(upper >= left)
    {
        res.push_back({left, upper});
    }
    return res;
}