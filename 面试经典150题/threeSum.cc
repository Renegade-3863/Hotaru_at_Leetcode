#include <iostream>

class Solution 
{
public:
    vector<vector<int>> threeSum(vector<int>& nums)
    {
        // 要求计算 nums 中和为 0 的三个数（下标不同）
        // 我们可以使用双指针的方法对数组进行处理
        int n = nums.size();
        vector<vector<int>> res;
        // 首先，要使用双指针算法，我们需要保证 nums 数组是有序的，没有有序性，双指针算法无法成立
        // 排为默认的递增顺序即可
        sort(nums.begin(), nums.end());
        // 枚举第一个元素的下标 first
        for(int first = 0; first < n-2; ++first)
        {
            // 如果枚举到的 first 下标上的值等于 first-1 下标上的值，那么我们可以直接跳过，否则这一轮会找出重复的三元组
            if(first > 0 && nums[first] == nums[first-1])
            {
                continue;
            }
            int second = first+1, third = n-1;
            // 开始执行双指针处理
            while(second < third)
            {
                // 注意，这里也要避免重复
                if(second > first+1 && nums[second] == nums[second-1])
                {
                    ++second;
                    continue;
                }
                // 我们可以通过检查 nums[first], nums[second], nums[third] 的和与 0 的关系，来判断下一步要如何进行
                // 如果三者的和是小于 0 的，那么我们可以断定，当前的 second 一定是较小的，我们可以舍弃它，把 second 往右移动一个格子
                if(nums[first]+nums[second]+nums[third] < 0)
                {
                    ++second;
                }
                else if(nums[first]+nums[second]+nums[third] == 0)
                {
                    // 记录一次结果
                    res.push_back({nums[first], nums[second], nums[third]});
                    ++second;
                    --third;
                }
                else
                {
                    --third;
                }
            }
        }
        // 处理完成，返回结果即可
        return res;
    }
};