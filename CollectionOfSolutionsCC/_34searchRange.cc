#include "Solution.h"

vector<int> Leetcode1_100::Solution::searchRange(vector<int>& nums, int target)
{
    // 本题是非常经典的二分查找类题目
    // 我们要做的是分开进行两次二分查找，如果能找到 target 的开始位置，那么我们可以继续进行第二次查找
    // 否则不用进行第二次查找了，那么就可以直接返回 [-1, -1] 了
    int left = 0, right = nums.size()-1;
    int res = -1;
    vector<int> ans(2, -1);
    while(left <= right)
    {
        int mid = ((right-left)>>1)+left;
        // 如果这个中点小于 target 值，那么显然 mid 值不可能是开始位置，右移 left 值
        if(nums[mid] < target)
        {
            left = mid+1;
        }
        // 否则，这个 mid 值可以是答案的备选值
        else
        {
            res = mid;
            // 继续向左检查可能的下标值
            right = mid-1;
        }
    }
    // 还需要额外检查一下 nums[res] 和 target 是否相等
    // 没找到对应值，直接返回 {-1, -1} 即可
    if(res == -1 || nums[res] != target)
    {
        return ans;
    }
    // 否则，可以把对应值留下，作为开始下标
    ans[0] = res;
    res = -1;
    // 再找结束位置
    left = 0, right = nums.size()-1;
    while(left <= right)
    {
        int mid = ((right-left)>>1)+left;
        if(nums[mid] <= target)
        {
            res = mid;
            left = mid+1;
        }
        else
        {
            right = mid-1;
        }
    }
    ans[1] = res;
    return ans;
}