#include "Solution.h"

int Leetcode701_800::Soltuion::pivotIndex(vector<int>& nums)
{
    // 简单的前缀和问题
    int n = nums.size();
    vector<int> preSum(n, 0);
    int sum = accumulate(nums.begin(), nums.end(), 0);
    // cout << sum << endl;
    for(int i = 0; i < n; ++i)
    {
        preSum[i] = i == 0 ? nums[i] : preSum[i-1]+nums[i];
        int left = i == 0 ? 0 : preSum[i-1], right = i == n-1 ? 0 : sum-preSum[i];
        if(left == right)
        {
            return i;
        }
    }
    return -1;
}