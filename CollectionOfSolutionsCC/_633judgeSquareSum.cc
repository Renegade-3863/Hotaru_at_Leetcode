#include "Solution.h"

bool Leetcode601_700::Soltuion::judgeSquareSum(int c)
{
    // 我们把问题换一种说法：
    // 在有序序列：[1, 4, 9, 16, 25, ...] 中
    // 寻找两数之和等于 c 
    // 这就是第一题：两数之和了
    // 所以我们只需要进行一步预处理：
    // 哪些完全平方数是小于 c 的
    // 记录到一个数组中
    // 之后应用两数之和的相向双指针算法即可
    vector<int> nums;
    // 0 也是个完全平方数
    nums.push_back(0);
    int base = 1;
    // base * base < c && base * base <= INT_MAX
    while(base <= INT_MAX / base && base * base <= c)
    {
        nums.push_back(base*base);
        ++base;
    }
    // 处理完成，对 nums 应用 c 的两数之和
    int left = 0, right = nums.size()-1;
    // 相向双指针
    while(left <= right)
    {
        // 注意防溢出
        if(nums[left] > INT_MAX-nums[right] || nums[left]+nums[right] > c)
        {
            // 尝试的大值+小值的和大于 c
            // 那么很明显当前的 right 和它左边直到 left 为止的所有元素求和，都不可能等于 c 了
            // 我们直接把 right 丢弃即可
            --right;
        }
        else if(nums[left]+nums[right] == c)
        {
            // 尝试的大值+小值的和等于 c
            // 这就是答案了，返回 true
            return true;
        }
        else
        {
            // 和小于 c
            // 那么很明显当前的 left 和它右边直到 right 为止的所有元素求和，都不可能等于 c 了
            // 直接把 left 丢弃即可
            ++left;
        }
    }
    // 遍历完了，没有找到结果，返回 false 即可
    return false;
}