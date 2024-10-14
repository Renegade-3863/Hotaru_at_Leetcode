#include "Solution.h"

bool Leetcode201_300::Solution::containDuplicate(vector<int>& nums)
{
    // 简单使用哈希表即可
    unordered_set<int> exist;
    int n = nums.size();
    for(int i = 0; i < n; ++i)
    {
        if(exist.find(nums[i]) != exist.end())
        {
            return true;
        }
        exist.insert(nums[i]);
    }
    return false;
}   