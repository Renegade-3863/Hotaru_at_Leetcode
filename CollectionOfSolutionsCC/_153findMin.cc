#include "Solution.h"

int Leetcode101_200::Solution::findMin(vector<int>& nums)
{
    // 本题要求我们从一个旋转排序了的数组中找出最小的那个元素
    // 本质上本题需要的和之前从旋转排序数组中查找某个元素的过程是一样的，都是二分算法
    // 我们需要做的就是进行细致而正确的分类讨论
    // 我们规定两个指针 left 和 right
    // [left, right] 内部是 nums 中最小元素的可能存在范围
    int n = nums.size();
    int left = 0, right = n-1;
    int res = -1;
    while(left <= right)
    {
        // 取区间中点
        int mid = ((right-left)>>1)+left;
        // 首先判断 nums[mid] 和 nums[0] 的大小关系
        // 已经给出 nums 中的元素都不同，因而可以断定 else 的条件是 nums[mid] < nums[0]
        if(nums[mid] > nums[0])
        {
            // 此时可以确定 mid 以及左侧的序列是一个完整的递增序列
            // 而无法断定 nums[0] 是不是最小的那个元素
            // 所以需要进一步将 nums[0] 和 nums[n-1] 进行比较
            // 如果 nums[0] > nums[n-1]，那么显然 nums[0] 不会是最小的元素，而我们此时又知道 nums[0] 到 nums[mid] 的闭合区间中形成的是一个递增序列
            // 因而这些元素都不可能是最终的结果，我们可以简单地丢弃它们，并更新 left 指针
            if(nums[0] > nums[n-1])
            {
                left = mid+1;
            }
            // 此时必须是 nums[0] < nums[n-1]
            else
            {
                // 那么只有一种可能，那么就是，nums[0] 就是最小值
                return nums[0];
            }
        }
        else if(nums[mid] == nums[0])
        {
            // 如果 nums[mid] == nums[0]，此时可能有下面的情况：
            // 1. nums[0] > nums[n-1]
            // 那么我们可以断定 nums[mid]，也就是 nums[0] 不可能是最终结果
            // 可以把 left 置于 mid+1
            if(nums[0] > nums[n-1])
            {
                left = mid+1;
            }
            // 2. nums[0] < nums[n-1]
            // 那么我们依然可以直接返回 nums[0]
            else
            {
                return nums[0];
            }
        }
        else
        {
            // 此时 nums[mid] < nums[0]
            // 可以断定 mid 以及其右侧的元素组成的序列是一个递增序列
            // 此时我们无法判断 nums[mid] 是不是最小的那个元素
            // 需要进一步比较 nums[mid] 与 nums[0]
            if(nums[mid] > nums[0])
            {
                // 此时 nums[mid] 不可能是最小的元素
                // 而由于 mid 右边的元素都比 nums[mid] 大，所以均不可能是最大元素，可以丢弃它们
                right = mid-1;
            }
            else
            {
                // 此时 nums[mid] 虽然小于了 nums[0]，但是我们也不能明确 nums[mid] 就是最小的元素，只能先假设它是最小的那个元素，不过它左侧依然有可能存在更小的元素
                // 因而我们先给答案下标赋上这个 mid 值，并修改 right 指针
                res = mid;
                right = mid-1;
            }
        }
    }
    // 保证循环结束后，left == right，此时我们直接返回 nums[left] 即可
    return nums[res];
}