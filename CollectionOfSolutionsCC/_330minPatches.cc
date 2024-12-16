#include "Solution.h"

int Leetcode301_400::Solution::minPatches(vector<int>& nums, int n)
{
    // 本质是一道数学题，不喜欢数学的这题可以跳过
    // 由于给定 nums 数组已排序，我们可以通过维护下面的循环不变式来完成本题：
    // 维护一个最大的连续 "可构成" 以1开始的序列 [1, x-1]
    // 每遇到一个值，如果它是 x，那么我们可以构造出 [x, 2x-1] 之间的所有值(挺明显的。。。)
    // 那么此时我们可以把这个 "可构成" 区间的右边界(开边界)变成 2x
    // 以此类推维护这个值，直到我们的这个右边界大于 n
    long long x = 1;
    // 记录最终需要添加的数据个数
    int res = 0;
    int len = nums.size(), i = 0;
    while(x <= n)
    {
        // 这时，把这个新元素添加到任何一个已经可以拿到的值 [1, x] 对应的集合中
        // 我们可以拿到 [1+nums[i], x+nums[i]] 这个区间中的所有元素，所以我们可以更新右界
        if(i < len && nums[i] <= x)
        {
            // 注意：这是已经有的元素，我们不用添加新元素，所以 res 不变
            x += nums[i];
            ++i;
        }
        // i >= len || nums[i] > x
        // 否则，我们的当前最小元素是一个更大的元素，或者没有新元素了，由于我们明确数组中不存在负数，所以很明显 [x, nums[i]] 中的这些元素都不可能构成出来
        // 我们需要至少添加一个 x 这个元素到数组中，这样我们可以构造出 [1+x, 2x-1] 中的所有元素，而 x 本身又可以构成 x 这个元素
        // 所以我们就可以更新 x 值为 2x
        else
        {
            x <<= 1;
            // 此时新添了一个元素，更新答案
            ++res;
        }
    }
    // 结束，条件满足，返回结果即可
    return res;
}