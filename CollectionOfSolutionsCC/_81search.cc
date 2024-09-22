#include "Solution.h"

bool search(vector<int>& nums, int target)
{
    // 本题是进阶版的旋转排序数组上的二分查找问题，由于这里说数组不再是严格的升序排列而是非降序排列
    // 我们需要在这样一个数组上寻找目标值 target
    // 分析角度依然是二分
    // 假设当前有可能存在 target 的区间是 [left, right]
    // 这个区间的中点值维护在 mid = ((right-left)>>1)+left 上
    // 当前的中点值和 nums[left] (n 为 nums 的长度) 的关系有两种情况
    // 1. nums[left] <= nums[mid]
    // 此时说明 mid 左侧一定是一个非降序排列的子数组
    // 2. nums[left] > nums[mid]
    // 此时说明 mid 右侧一定是一个非降序排列的子数组
    // 下面随着代码编写一步步进行条件分析
    int left = 0, right = nums.size()-1;
    while(left <= right)
    {
        // 取中点
        int mid = ((right-left)>>1)+left;
        // 先按最外层的条件进行分类
        // 情况1.
        if(nums[left] <= nums[mid])
        {
            // 本题和不带重复元素的原题的区别就在于，可能会出现
            // nums[0] == nums[mid] == nums[n-1] 的情况
            // 此时我们无法确定哪一侧才是一个有序的序列，因而也就无法进行直接进行二分
            // 对于这种情况，我们只能选择同时将 left 和 right 的值靠近1
            if(nums[left] == nums[mid] && nums[right] == nums[mid])
            {
                ++left; --right;
                if(nums[mid] == target)
                {
                    return true;
                }
                continue;
            }
            // 进一步分析 nums[mid] 和 target 的关系
            // 子情况1.
            // 此时 target 只可能在 mid 下标左侧
            if(nums[mid] < target)
            {
                left = mid+1;
            }
            // 子情况2.
            // 此时仍然无法明确 target 可能会在哪一侧，需要合并 nums[0] 进一步判断
            else if(nums[mid] > target)
            {
                // 此时 target 只可能存在于 mid 左侧
                if(nums[left] < target)
                {
                    right = mid-1;
                }
                // 找到了相等的元素，直接返回即可
                else if(nums[left] == target)
                {
                    return true;
                }
                // 此时 target 只可能存在于 mid 右侧
                else
                {
                    left = mid+1;
                }
            }
            // 子情况3.
            // 我们直接找到了 target，返回 true 即可
            else
            {
                return true;
            }
        }
        // 情况2.
        else
        {
            // 进一步分析 nums[mid] 与 target 的关系
            // 子情况1.
            // 此时 target 只可能存在于 mid 左侧
            // nums[left] > nums[mid] > target
            if(nums[mid] > target)
            {
                right = mid-1;
            }
            // 子情况2.
            // 此时仍然无法明确 target 可能会在哪一侧，需要合并 nums[0] 进一步判断
            // nums[mid] < nums[left] && nums[mid] < target
            else if(nums[mid] < target)
            {   
                // 此时 target 只可能在 mid 左侧
                if(nums[left] < target)
                {
                    right = mid-1;
                }
                // 直接找到了结果，那么就直接返回即可
                else if(nums[left] == target)
                {
                    return true;
                }
                // nums[0] > target > nums[mid]
                // 此时 target 只可能在 mid 右侧
                else
                {
                    left = mid+1;
                }
            }
            // 我们直接找到了 target, 返回 true 即可
            else
            {
                return true;
            }
        }
    }
    // 如果能走到这一步，说明一定不存在 target，直接返回 false 即可
    return false;
}