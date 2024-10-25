#include "Solution.h"

void Leetcode201_300::Solution::moveZeroes(vector<int>& nums)
{
    // 非常简单的循环不变式问题
    // 考虑这样的方案：
    // 我们维护两个指针
    // 一个指向从左到右第一个为零的元素的下标，另一个指向第一个指针右侧第一个非零数的下标
    int left = 0, right = 0, n = nums.size();
    // 维护 right 指针的定义
    while(right < n)
    {
        if(nums[right] != 0)
        {
            break;
        }
        ++right;
    }
    // 之后按 left 进行遍历
    // 循环的退出条件为 right == n
    // 意思是右侧已经不存在任何非零元素了
    while(right < n)
    {
        if(nums[left] == 0)
        {
            swap(nums[left], nums[right]);
            // 交换后，把 left 右移一位，right 也右移到下一个非零的数
            ++left;
            while(right < n && nums[right] == 0)
            {
                ++right;
            }
        }
        // 否则，我们只需要把 left 右移一位即可
        else
        {
            // 注意：如果 right == left，那么我们要保证 right 不小于 left
            if(left == right)
            {
                ++right;
                // 把 right 再移动到下一个不为零的数字处
                while(right < n && nums[right] == 0)
                {
                    ++right;
                }
            }
            ++left;
        }
    }
    // 移动结束，直接返回即可
    return;
}
