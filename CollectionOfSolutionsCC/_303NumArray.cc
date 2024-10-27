#include "Solution.h"

Leetcode301_400::Solution::NumArray::NumArray(vector<int>& nums)
{
    // 预处理 preSum 数组
    int n = nums.size();
    if(n > 0)
    {
        this->preSum.resize(nums.size());
        this->preSum[0] = nums[0];
        for(int i = 1; i < n; ++i)
        {
            this->preSum[i] = this->preSum[i-1]+nums[i];
        }
    }
    // 处理完成，返回即可
}

Leetcode301_400::Solution::NumArray::sumRange(int left, int right)
{
    // 我们要计算 nums[left] - nums[right] 之间的数据和
    // 通过前缀和可以简单地得到结果
    if(left == 0)
    {
        return this->preSum[right];
    }
    return this->preSum[right]-this->preSum[left-1];
}