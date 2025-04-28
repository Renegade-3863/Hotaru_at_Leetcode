#include "Solution.h"

int Leetcode701_800::Soltuion::dominantIndex(vector<int>& nums)
{
    // 简单题，简单做（）
    // 先遍历一遍整个 nums 数组，找出最大值，然后再遍历一遍整个数组，检查题目要求的条件即可
    int maximum = *max_element(nums.begin(), nums.end());
    int ret = -1, n = nums.size();
    for(int i = 0; i < n; ++i)
    {
        if(nums[i] == maximum)
        {
            ret = i;
            continue;
        }
        // 不等于最大值，那么我们检查条件
        if(nums[i] > (maximum>>1))
        {
            return -1;
        }
    }
    return ret;
}