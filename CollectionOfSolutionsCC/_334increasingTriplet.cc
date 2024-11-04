#include "Solution.h"

bool Leetcode301_400::Solution::increasingTriplet(vector<int>& nums)
{
    // 三元递增子序列的存在性问题
    // 实际上可以用求递增子序列的类似问题来求解
    // 我们只需要用和 300 题类似的方法，不过截取到 dp 数组长度达到 3 就返回即可
    // 回顾 300 题我们的定义：这个数组中存储的是：dp[i] 代表的是目前已知的，长度为 i+1 的递增子序列中，结尾值最小的那一个序列的结尾值
    vector<int> dp;
    int n = nums.size();
    for(int i = 0; i < n && dp.size() < 3; ++i)
    {
        // 对于每个元素，我们获取 dp 数组的长度，之后可以通过二分查找，定位出 dp 中第一个不小于 nums[i] 的元素，把它替换成 nums[i] 即可
        int left = 0, right = dp.size()-1;
        int idx = dp.size();
        // 二分即可
        while(left <= right)
        {
            int mid = ((right-left)>>1)+left;
            if(dp[mid] >= nums[i])
            {
                idx = mid;
                right = mid-1;
            }
            else
            {
                left = mid+1;
            }
        }
        // 如果 idx 不是 dp.size() 那么我们只需要进行替换即可
        if(idx == dp.size())
        {
            dp.push_back(nums[i]);
        }
        else
        {
            dp[idx] = nums[i];
        }
    }
    return dp.size() == 3;
}