#include "Solution.h"

int Leetcode301_400::Solution::maxRotateFunction(vector<int>& nums)
{
    // 本题只需要稍微写几个运算式就不难看出子问题之间的递推关系了
    // 假设 nums 的长度为 n
    // 我们可以在这里直接给出递推关系式
    // 假设移动 k 次的结果是 F(k)
    // 那么 F(k) - F(k-1) = sum(n) - n*nums[n-k] (k >= 1)
    // 我们只需要遍历算一遍 F(0) 即可
    int n = nums.size();
    // 计算 F(0) 和数组的和
    int summation = accumulate(nums.begin(), nums.end(), 0);
    int res = 0;
    for(int i = 0; i < n; ++i)
    {
        res += nums[i]*i;
    }
    // 之后就是正常的递推过程了
    int pre = res, cur = 0;
    for(int k = 1; k < n; ++k)
    {
        cur = pre + summation - n*nums[n-k];
        res = max(res, cur);
        pre = cur;
    }
    return res;
}