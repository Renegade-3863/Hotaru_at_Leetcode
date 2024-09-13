#include "Solution.h"

int Leetcode1_100::Solution::removeElement(vector<int>& nums, int val)
{
    // 本题和移除非递减数组中的重复元素的基本思路是一致的，我们可以简单地使用双指针法来完成本题
    // slow 记录最靠右的连续的不等于 val 的子数组的下标
    int slow = -1, n = nums.size();
    for(int fast = 0; fast < n; ++fast)
    {
        // 如果 nums[fast] != val，那么就把这个元素换到 slow+1 下标处，并更新 slow 值
        if(nums[fast] != val)
        {
            swap(nums[++slow], nums[fast]);
        }
        // 否则，找到了一个重复元素，没必要对它做任何修改
    }
    // 最后，slow+1 就是不等于 val 对元素总数
    return slow+1;
}