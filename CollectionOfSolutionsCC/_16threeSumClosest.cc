#include "Solution.h"

int Leetcode1_100::Solution::threeSumClosest(vector<int>& nums, int target)
{
    // 本题要求寻找的是一个和给定的 target 值最接近的三数之和，可以看作是相等的三数之和的一个小变种，本质想法没有变，都是尝试对 target 进行逼近
    // 我们依然可以沿用对于三数之和的双指针思想，只是这次根据和与 target 的大小关系，可能需要不同的变换方式
    // 本题我们还需要额外设置一个差值记录，记录当前找到的和 target 差距最小的和的差距
    int diff = 0x3f3f3f3f;
    // 基本思路和三数之和一样
    // 先排序
    sort(nums.begin(), nums.end());
    int res = 0, n = nums.size();
    for(int first = 0; first < n-2; ++first)
    {
        // 别忘了去重
        if(first > 0 && nums[first-1] == nums[first])
        {
            continue;
        }
        int second = first+1, third = n-1;
        while(second < third)
        {
            if(second > first+1 && nums[second-1] == nums[second])
            {
                ++second;
                continue;
            }
            int sum = nums[first]+nums[second]+nums[third];
            if(abs(sum-target) < diff)
            {
                diff = abs(sum-target);
                res = sum;
            }
            // 如果找到了一个相等值，那么直接返回 target 即可，无需任何其它检查
            if(sum == target)
            {
                return target;
            }
            else if(sum > target)
            {
                // 同理，为了逼近 target，需要左移 third 指针
                --third;
            }
            else
            {
                // 为了逼近 target，需要右移 second 指针
                ++second;
            }
        }
    }
    // 整体循环结束后，找到的就是距离 target 差值最小的那个三数之和
    return res;
}