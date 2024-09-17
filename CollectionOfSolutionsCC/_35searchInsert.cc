#include "Solution.h"

int Leetcode1_100::Solution::searchInsert(vector<int>& nums, int target)
{
    // 简单的二分查找问题
    // 不再赘述
    int left = 0, right = nums.size()-1;
    int res = 0;
    while(left <= right)
    {
        int mid = ((right-left)>>1)+left;
        // 如果 nums[mid] >= target，那么 mid 的位置可能是插入 target 的位置
        // 更新 res 值
        if(nums[mid] >= target)
        {
            res = mid;
            right = mid-1;
        }
        else
        {
            left = mid+1;
        }
    }
    return res;
}