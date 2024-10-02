#include "Solution.h"

int Leetcode101_200::Solution::findMin2(vector<int>& nums)
{
    // 本题在 153 题的基础上放宽了数组的限制：可能存在重复元素，也即整个数组可能是一个非降序序列，而不是严格的递增序列
    // 此时我们的分类讨论就可能会比较麻烦
    // 走一步看一步
    // 依然和上一题相同的二分方案：
    // [left, right] 代表目前有可能存在最小值的区间
    int n = nums.size();
    int left = 0, right = n-1;
    // 这里把 res 初始值设置为 0 是有必要的，我们要避免一种极端情况，详见情况 2 的情况分析
    int res = 0;
    while(left <= right)
    {
        // 取出中点
        int mid = ((right-left)>>1)+left;
        // 先根据 nums[mid] 和 nums[0] 的关系进行初步分类
        if(nums[mid] > nums[0])
        {
            // 1. nums[mid] > nums[0]
            // 此时说明 mid 以及 0 组成的闭合区间之间的元素一定是一个非降序序列
            // 此时无法确定 nums[0] 是不是最终的结果，需要进一步比较 nums[0] 和 nums[n-1] 的大小关系
            if(nums[0] >= nums[n-1])
            {
                // 此时可以断定 nums[0] 不可能是结果，进而可以丢弃 nums[0] 到 nums[mid] 之间所有的值
                // 如果开头结尾的值相等
                // 那么此时我们同样可以断定答案一定在 nums[mid] 的右边，因为下面的关系：
                // nums[0] == nums[n-1] < nums[mid]
                // nums[mid] > nums[n-1] 的关系明确了，mid 右侧一定会有一个转折点，这个转折点就是最小值点
                left = mid+1;
            }
            else
            {
                // 如果 nums[0] < nums[n-1]
                // 那么我们也可以简单确定 nums[0] 就是结果
                return nums[0];
            }
        }
        else if(nums[mid] == nums[0])
        {
            // 2. nums[mid] == nums[0]
            // 此时我们无法明确指出 nums[mid] 左侧或者右侧的区间是否存在明确的非降序区间
            // 需要进一步判断 nums[left] 和 nums[right] 本身的大小关系
            // 1) nums[left] < nums[right]
            // 那么显然 nums[right] 不可能是最小值
            if(nums[left] < nums[right])
            {
                --right;
            }
            // 2) nums[left] == nums[right]
            // 此时我们只需要随机移动两端中的一个
            else if(nums[left] == nums[right])
            {
                // 我们这里移动 left 指针
                ++left;
            }
            // 3) nums[left] > nums[right]
            // 此时我们需要移动 left
            else
            {
                ++left;
            }
            // 注意，因为这里我们没有对 res 的值进行处理，而同时存在修改 left 和 right 的值的操作，因而我们完全存在一条路线
            // 完全经由这条路线完成对整个数组的遍历，从而导致 res 的值没有被设置而结束循环
            // 而这种情况是唯一的：数组中所有元素均相同的情况
            // 可以想见：此时我们就是在以步长为1不断地缩小区间，直到 left > right
            // 如果我们仍然把 res 的初始值置于 -1，那么显然我们最后得不到正确的答案
            // 而这时，我们只需要把 res 的初始值置为随机的一个下标值即可，因而我们把 res 的初始值置于0
        }
        else
        {
            // 3. nums[mid] < nums[0]
            // 此时我们可以确认 nums[mid] 和 nums[n-1] 以及它们中间的元素组成的区间是一个非降序区间
            // 后面的分析类似 153 题
            // 我们此时可以把 nums[mid] 记录为 "可能的结果"
            res = mid;
            // 并把 right 置于 mid-1
            right = mid-1;
        }
    }
    return nums[res];
}