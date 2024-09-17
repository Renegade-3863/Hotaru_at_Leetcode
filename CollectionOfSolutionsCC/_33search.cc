#include "Solution.h"

int Leetcode1_100::Solution::search(vector<int>& nums, int target)
{
    // 给定一个经过旋转的有序数组，要求在这个数组中找出目标值 target
    // 这种题应该能够一眼看出来最优解就是二分
    // 问题在于，二分优化的本质在于，通过对中点处信息的判定，我们能够明确丢弃掉一部分不可能为可能结果的数据
    // 这里如何实现这种判断呢？
    // 我们知道 nums 数组有这样的结构：
    // [递增序列] [一个逆序对] [递增序列]
    // 同时这个逆序对中，小的那个值是整个数组中的最小值
    // 我们假设拿到了一个中间值 nums[mid]
    // 那么这个值有两种可能性：
    // 1. nums[mid] >= nums[0]
    // 2. nums[mid] < nums[0]
    // 分析了一通，还是代码写一遍更加简洁
    int left = 0, right = nums.size()-1;
    while(left <= right)
    {
        // 取中点
        int mid = ((right-left)>>1)+left;
        // 分两个大类情况讨论
        // 中点左侧是一个完整的升序序列
        if(nums[mid] >= nums[0])
        {
            if(nums[mid] > target)
            {
                // 需要进一步判断 target 和 nums[0] 的关系
                if(nums[0] > target)
                {
                    // 一定在右边了
                    left = mid+1;
                }
                else if(nums[0] == target)
                {
                    // 0 就是答案下标
                    return 0;
                }
                else
                {
                    // 一定在左边了
                    right = mid-1;
                }
            }
            else if(nums[mid] == target)
            {
                // 找到了结果
                return mid;
            }
            else
            {   
                // nums[0] <= nums[mid] < target
                // 一定在右边了
                left = mid+1;
            }
        }
        // 中点右侧是一个完整的升序序列
        else
        {
            if(nums[mid] > target)
            {
                // target 一定在左边了
                right = mid-1;
            }
            else if(nums[mid] == target)
            {
                return mid;
            }
            else
            {
                // nums[mid] < target && nums[mid] < nums[0]
                // 需要进一步判断 target 和 nums[0] 的关系
                if(nums[0] > target)
                {
                    // target 一定在右边了
                    left = mid+1;
                }
                else if(nums[0] == target)
                {
                    return 0;
                }
                else
                {
                    // 一定在左边了
                    right = mid-1;
                }
            }
        }
    }
    // 如果在循环中没有返回结果，说明就没有找到 target
    // 返回 -1 即可
    return -1;
}