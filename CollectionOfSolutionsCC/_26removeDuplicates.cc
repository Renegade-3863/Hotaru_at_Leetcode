#include "Solution.h"

int Leetcode1_100::Solution::removeDuplicates(vector<int>& nums)
{
    // 题目要求进行 原地 删除，所以我们不能用最简单的新建数组并把所有不重复元素添加到其中的方法
    // 那么应该如何替掉重复元素呢？
    // 可以采用一种类似双指针的方法
    // 用一个慢指针标记当前已经修改好了的不重复元素构成的连续子数组的最后一个元素的下标
    // 用另一个快指针标记当前遍历到的下标
    int slow = -1, n = nums.size();
    for(int fast = 0; fast < n; ++fast)
    {
        // 采用一种简单的逻辑，检查当前 fast 下标处的元素是否和 slow 下标处的元素相等，如果相等，那么就没必要移动这个重复元素，直接后移 fast 指针即可
        // 否则，由于数组本身的非递减性质，我们一定是找到了一个新的不重复元素，可以把这个元素和下标 slow+1 处的元素交换，并更新 slow，这样就维护了二者
        // 原始的定义
        // 注意一下 slow == -1 时的边界情况检查
        if(slow == -1 || nums[fast] != nums[slow])
        {
            swap(nums[++slow], nums[fast]);
        }
    }
    // 循环结束后，slow+1 实际上就是最终的 k 值(即不重复元素的个数)
    return slow+1;
}