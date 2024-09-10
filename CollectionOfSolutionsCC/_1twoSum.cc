#include "Solution.h"

vector<int> Leetcode1_100::Solution::twoSum(vector<int> &nums, int target)
{
    unordered_map<int, int> memo;
    int n = nums.size();
    for (int i = 0; i < n; ++i)
    {
        if (memo.find(target - nums[i]) != memo.end())
        {
            return {memo[target - nums[i]], i};
        }
        memo[nums[i]] = i;
    }
    return {-1, -1};
}