#include "Solution.h"

// 暴力算法，O(n^2)，超时，需要优化
int Leetcode1_100::Solution::subarraySum(vector<int>& nums, int k)
{
    // 给定一个数组，要求我们找出这个数组中和为 k 的子数组的个数
    // 首先，最容易想到的其实是前缀和，因为本题不涉及修改数组中的元素，所以用不到线段树这么高级的结构
    int n = nums.size();
    vector<int> preSum(n, 0);
    preSum[0] = nums[0];
    // 预计算前缀数组
    for(int i = 1; i < n; ++i)
    {
        preSum[i] = preSum[i-1]+nums[i];
    }
    // 之后要做的就是枚举所有可能的子数组
    int cnt = 0;
    for(int i = 0; i < n; ++i)
    {
        for(int j = i; j < n; ++j)
        {
            int left = i > 0 ? preSum[i-1] : 0;
            if(preSum[j]-left == k)
            {
                ++cnt;
            }
        }
    }
    return cnt;
}

// 如何进行优化？
// 观察上面的两层循环，我们之所以达到了平方的复杂度数量级，其实就是因为在计算的时候是一个一个的去递增 cnt 的值的
// 那么如何进行优化呢？
// 考虑能不能一次记录某个下标 j 之前的所有信息，比如子数组和等于 preSum[j]-k 这个值的子数组在 j 前面出现了多少次？
// 显然是可以的！
// 利用散列表可以很简单地实现这一点
int subarraySumOpt(vector<int>& nums, int k)
{
    // 一次优化的版本
    int n = nums.size();
    vector<int> preSum(n, 0);
    preSum[0] = nums[0];
    for(int i = 1; i < n; ++i)
    {
        preSum[i] = preSum[i-1]+nums[i];
    }
    unordered_map<int, int> cnts;
    cnts[0] = 1;
    int res = 0;
    for(int j = 0; j < n; ++j)
    {
        res += cnts[preSum[j]-k];
        ++cnts[preSum[j]];
    }
    return res;
}

// 最后，考虑这个前缀和数组，它是不是还可以更优化一些？
// 上面我们是先计算出这个前缀和数组的结果，再去使用它，这是两轮循环，是否可以捏到一轮循环中？
// 同时是否有必要记录整个前缀和数组？随用随算可不可以？
// 上面两个问题的答案都是肯定的
// 因而就有了下面的最终优化结果
int subarraySumOptimal(vector<int>& nums, int k)
{
    // 二次优化的版本
    int n = nums.size();
    int preSum = 0;
    unordered_map<int, int> cnts;
    cnts[0] = 1;
    int res = 0;
    for(int j = 0; j < n; ++j)
    {
        // 随算前缀和
        preSum += nums[j];
        if(cnts.find(preSum-k) != cnts.end())
        {
            res += cnts[preSum-k];
        }
        ++cnts[preSum];
    }
    return res;
}