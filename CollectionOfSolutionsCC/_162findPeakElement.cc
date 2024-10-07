#include "Solution.h"

int Leetcode101_200::Solution::findPeakElement(vector<int>& nums)
{
    // 本题要求我们找出一组数中严格大于左右相邻值的元素
    // 基本方案还是二分法
    // 我们依然是定义：
    // [left, right] 为可能存在峰值元素的区间
    int left = 0, right = nums.size()-1;
    // 记录最终答案
    int res = 0, n = nums.size();
    while(left <= right)
    {
        // 取中点
        int mid = ((right-left)>>1)+left;
        // 判断中点和两侧值的大小关系：
        // 1. nums[mid] > nums[mid-1] && nums[mid] > nums[mid+1]
        // 此时我们就已经找到了一个峰值，可以直接返回结果
        // 2. nums[mid] > nums[mid-1] && nums[mid] < nums[mid+1]
        // 注意：本题不会出现 nums[mid] == nums[mid+1] 的情况，所以这里的情况讨论会比较简单
        // 此时我们可以明确的是，nums[mid] 绝对不会是一个合法的答案
        // 那么此时应该如何修改我们的区间？
        // 结论是：应该向右，把 left 值置于 mid+1
        // 因为 nums[mid-1] 不可能是一个合法的答案，而 nums[mid+1] 和它右侧的值目前来看是有可能存在答案的
        // 细一些分析原因：
        //  2.1 如果 nums[mid+1] 不是合法的答案，那么就是因为它右侧存在比它更大的元素，此时我们依旧可以通过上面的逻辑继续向右检查这个更大的元素
        //      所以这种方案是合理的
        //  2.2 如果 nums[mid+1] 是合法的答案，那么我们显然可以返回这个结果
        // 综上，这种二分方案是合理的，我们总能找出一个合法的答案 
        // 3. nums[mid] < nums[mid-1] && nums[mid] > nums[mid+1]
        // 此时和情况2类似，我们置 right 置于 mid-1
        // 4. nums[mid] < nums[mid-1] && nums[mid] < nums[mid+1]
        // 和 2、3 类似的分析，我们此时只需要任选一侧进行更新即可
        // 这里选择 left 进行更新
        // 情况 1.
        if((mid == 0 || nums[mid] > nums[mid-1]) && (mid == n-1 || nums[mid] > nums[mid+1]))
        {
            return mid;
        }
        // 情况 2.
        else if((mid == 0 || nums[mid] > nums[mid-1]) && (mid < n-1 && nums[mid] < nums[mid+1]))
        {
            res = mid+1;
            left = mid+1;
        }
        // 情况 3.
        else if((mid > 0 && nums[mid] < nums[mid-1]) && (mid == n-1 || nums[mid] > nums[mid+1]))
        {
            res = mid-1;
            right = mid-1;
        }
        // 情况 4.
        else
        {
            res = mid+1;
            left = mid+1;
        }
    }
    return res;
}