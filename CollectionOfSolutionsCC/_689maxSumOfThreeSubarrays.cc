#include "Solution.h"

vector<int> Leetcode601_700::Soltuion::maxSumOfThreeSubarrays(vector<int>& nums, int k)
{
    // 第一眼看没什么太好的思路，我们从最暴力的解法入手看看
    // 我们可以枚举第一个长度为 k 的子数组的开头下标
    // 假设某次枚举，第一个开头下标为 i
    // 之后我们可以枚举第二个长度为 k 的子数组的开头下标
    // 假设此时枚举的第二个开头下标为 j
    // 最后，枚举第三个长度为 k 的子数组的凯欧下标
    // 假设此时枚举的第三个开头下标为 h
    // 那么最后结果就是 max(nums[i, i+k-1]+nums[j, j+k-1]+nums[h, h+k-1])
    // 这样做的时间复杂度很高，为 O(n^3)
    // 不过我们可以先写出来，之后再尝试优化
    int n = nums.size();
    int res = INT_MIN;
    vector<int> ans(3, -1);
    // i 最远枚举到 n-3k
    // i, i+1, i+2, i+3, ..., i+k-1, i+k, ..., i+2k-1, i+2k, ..., i+3k-1
    // i+3k-1 = n-1
    // i = n-3k
    for(int i = 0; i <= n-3*k; ++i)
    {
        int sum1 = 0;
        for(int l = 0; l < k; ++l)
        {
            sum1 += nums[i+l];
        }
        // j 最远枚举到 n-2k
        // j, j+1, j+2, ..., j+k-1, j+k, ..., j+2k-1
        // j+2k-1 = n-1
        // j = n-2k
        for(int j = i+k; j <= n-2*k; ++j)
        {
            int sum2 = 0;
            for(int l = 0; l < k; ++l)
            {
                sum2 += nums[j+l];
            }
            for(int h = j+k; h <= n-k; ++h)
            {
                int sum3 = 0;
                for(int l = 0; l < k; ++l)
                {
                    sum3 += nums[h+l];
                }
                if(res < sum1+sum2+sum3)
                {
                    ans[0] = i; ans[1] = j; ans[2] = h;
                    res = sum1+sum2+sum3;
                }
            }
        }
    }
    return ans;
}

// 上面的 O(n^3) 算法显然无法通过，会 TLE
// 考虑如何进行优化
// 首先，我们实际上不用每一次都重新计算 sum1，sum2 和 sum3
// 我们可以使用类似滚动数组的方式来利用已经计算好的 sum1，sum2 和 sum3 值
// 这有点像滚动数组
// 同时，观察最后的结果
// 我们无非想要最大化 sum1+sum2+sum3
// 我们可以先计算 "最大的 sum1"，记为 maxSum1
// 再计算 "最大的 sum1+sum2"，记为 maxSum12
// 之后考虑 "最大的 maxSum12+sum3"，也就是 maxSum123， 作为最终的结果值
// 对于所有可能的 sum1，sum2 和 sum3， 我们可以按照固定长度的子数组进行滚动遍历的方式来同步维护上面的三个 maxSum 值
vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k)
{
    // sum1 从 [0, k-1] 开始遍历
    // sum2 从 [k, 2k-1] 开始遍历
    // sum3 从 [2k, 3k-1] 开始遍历
    int n = nums.size();
    int sum1 = 0, sum2 = 0, sum3 = 0;
    int maxSum1 = 0, maxSum12 = 0, maxSum123 = 0;
    int maxSum1Idx = 0, maxSum12Idx1 = 0, maxSum12Idx2 = 0;
    // ans 用于记录最终的结果
    vector<int> ans;
    for(int i = 2*k; i < n; ++i)
    {
        sum1 += nums[i-2*k];
        sum2 += nums[i-k];
        sum3 += nums[i];
        if(i >= 3*k-1)
        {
            // 只有在这个范围中，也就是 [3*k-1, n-1] 中
            // 我们才能保证 [i-k+1, i] 这个长度为 k 的区间是存在的
            // 否则，不满足前面至少长度为 2*k 的条件
            if(sum1 > maxSum1)
            {
                // 更新第一个数组的最大和以及对应的下标
                maxSum1 = sum1;
                // 此时第一个数组的开头元素下标为 i-3*k+1，结尾元素为 i-2*k
                maxSum1Idx = i-3*k+1;
            }
            if(maxSum1+sum2 > maxSum12)
            {
                maxSum12 = maxSum1+sum2;
                // maxSum12Idx1 代表已知满足前两个数组和最大的第一个数组的开始下标
                maxSum12Idx1 = maxSum1Idx;
                // maxSum12Idx1 代表已知满足前两个数组和最大的第二个数组的开始下标
                maxSum12Idx2 = i-2*k+1;
            }
            if(maxSum12+sum3 > maxSum123)
            {
                maxSum123 = maxSum12+sum3;
                ans = {maxSum12Idx1, maxSum12Idx2, i-k+1};
            }
            sum1 -= nums[i-3*k+1];
            sum2 -= nums[i-2*k+1];
            sum3 -= nums[i-k+1];
        }
    }
    return ans;
}