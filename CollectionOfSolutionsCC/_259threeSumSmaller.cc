#include "Solution.h"

int Leetcode201_300::Solution::threeSumSmaller(vector<int>& nums, int target)
{
    // 依然是类似之前的三数之和问题，我们依然可以通过双指针来进行检查
    // 首先对整个 nums 数组进行排序
    sort(nums.begin(), nums.end());
    // 之后，我们可以通过这样的循环不变式，来进行三元组的检查
    // 最外层的循环进行遍历
    int n = nums.size();
    int res = 0;
    for(int first = 0; first < n-2; ++first)
    {
        // 每一轮循环，我们要找出的是：三元组中，以 nums[i] 作为第一个元素的情况下，所有满足 num1 + num2 + num3 < target 的三元组
        // 同时，考虑到可能出现的重复问题，我们第二第三个元素的选择范围，只能限定到 nums[i] 后面的范围
        // 这是基于下面的论断：
        // 在我们把后面的元素 nums[i] 放到三元组的首位时，如果我们把 nums 中处于 nums[i] 前面的元素放到三元组的第二位/第三位，我们肯定已经在前面的循环中
        // 检查过了把这个前面的元素放到第一位的情况，此时就会出现重复，因而我们不能再尝试前面的这个元素
        // 考虑完成，思考对后半部分的双指针遍历问题
        // 由于 nums[i] 后面的部分是有序的，因而我们可以进行这样的遍历
        // 定义 [left, right] 区间为可能满足 nums[i] + num2 + num3 < target 的区间
        // 此时我们可以先看最外侧的两个元素: nums[i] + nums[left] + nums[right] 的值
        // 1. nums[i] + nums[left] + nums[right] >= target
        // 那么很明显 right 这个位置上的元素就不可能再和 left 以及它右侧的任何元素组合出 nums[i] + nums[left] + nums[right] < target 了
        // 我们此时可以把 right 减1
        // 2. nums[i] + nums[left] + nums[right] < target
        // 那么很明显我们找到了一个结果，此时可以先记录一次结果个数，然后把 left 向右移动
        // 记录结果个数这里需要注意一些问题：
        // 我们要记录多少个结果？
        // 不是一个，因为 nums[i] + nums[left] + nums[right] < target，那么很明显
        // 下标位于 [left, right] 中的除了 left，right 之外的其它所有元素和 nums[i], nums[left] 组合都是小于 target 的
        // 那么就应该记录 right-left 个！(即：left+1, left+2, ..., right)
        // 之后把 left 加1即可
        // 基本思路明确了，写代码就很简单了
        // 关于去重问题，本题要我们找出的是下标三元组，因而不存在三元组值重复的情况，因而这里不需要进行和之前题目类似的去重操作。。。
        int second = first+1, third = n-1;
        // 这里，我们依旧可以进行一步循环前的检查
        // 如果 nums[first]+nums[first+1]+nums[first+2] 本身就已经是不小于 target 的了，那么其实后面所有的元素都不可能再有和小于 target 都三元组了
        if(nums[first]+nums[first+1]+nums[first+2] >= target)
        {
            return res;
        }
        // 如果 nums[first]+nums[third-1]+nums[third] 本身就是小于 target 的，那么我们实际上也没必要进行下面的循环，我们只需要记录所有可行的组合到 res 中即可
        if(nums[first]+nums[third-1]+nums[third] < target)
        {
            // C(third-second+1, 2) = (third-second+1)*(third-second)/2
            res += (third-second+1)*(third-second)/2;
            continue;
        }
        while(second < third)
        {
            if(nums[first]+nums[second]+nums[third] >= target)
            {
                --third;
            }
            else 
            {
                // 记录三元组个数
                res += third-second;
                ++second;
            }
        }
    }
    return res;
}