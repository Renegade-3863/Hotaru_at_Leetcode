#include "Solution.h"

int Leetcode701_800::Soltuion::search(vector<int>& nums, int target)
{
    // 都看到这么多题解了，这题我就不写解释了吧。。
    // 直接秒！
    int left = 0, right = nums.size()-1;
    while(left <= right)
    {
        int mid = ((right-left)>>1)+left;
        if(nums[mid] < target)
        {
            left = mid+1;
        }
        else if(nums[mid] == target)
        {
            return mid;
        }
        else
        {
            right = mid-1;
        }
    }
    // 不存在，返回 -1
    return -1;
}