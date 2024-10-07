#include "Solution.h"

vector<int> Leetcode101_200::Solution::twoSum2(vector<int>& numbers, int target)
{
    // 本题要求我们不用额外空间来找出满足两数之和等于给定 target 的数对
    // 已知这个数组是一个有序的数组
    // 那么我们就可以枚举每个数值作为数对中的第二个元素值，并对它前面的所有元素做一次二分查找，搜索 target - numbers[i] 值
    // 代码写起来很简单
    // 这是一个 O(nlogn) 的结果，而题目的最优解法是 O(n) 的，我们需要考虑是否能够优化方案成 O(n) 时间 + O(1) 空间
    int n = numbers.size();
    for(int i = 0; i < n; ++i)
    {
        int left = 0, right = i-1;
        while(left <= right)
        {
            int mid = ((right-left)>>1)+left;
            if(numbers[mid] > target-numbers[i])
            {
                right = mid-1;
            }
            else if(numbers[mid] == target-numbers[i])
            {
                return {mid+1, i+1};
            }
            else
            {
                left = mid+1;
            }
        }
    }
    // 按题意，不会执行到这一步
    return {-1, -1};
}

vector<int> twoSum(vector<int>& numbers, int target)
{
    // 考虑类似三数之和/四数之和问题的解法，我们可以考虑使用双指针
    // 规定 [left, right] 是当前还可能存在和为 target 的数对的区间
    // 我们每次检查这个区间两端的数值，看它们的和是多少
    // 1. numbers[left] + numbers[right] == target -> 我们找到了结果
    // 2. numbers[left] + numbers[right] < target -> 我们可以丢弃 numbers[left]，这个值和 numbers[left] 右侧的所有值求和都不再可能是 target 了
    // 3. numbers[left] + numbers[right] > target -> 我们可以丢弃 numbers[right]，这个值和 numbers[right] 左侧的所有值求和都不再可能是 target 了
    int left = 0, right = numbers.size()-1;
    while(left < right)
    {
        if(numbers[left]+numbers[right] < target)
        {
            ++left;
        }
        else if(numbers[left]+numbers[right] == target)
        {
            return {left+1, right+1};
        }
        else
        {
            --right;
        }
    }
    // 不会执行到这一行
    return {-1, -1};
}