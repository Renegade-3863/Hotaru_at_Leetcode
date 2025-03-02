#include "Solution.h"

double Leetcode601_700::Soltuion::findMaxAverage1(vector<int>& nums, int k)
{
    // 简单题，简单做，题目要我们检查，我们检查就好了
    // 滑动一个长度为 k 的窗口即可
    // double 的最小可表示值记不住哩。。
    double sum = 0, res = INT_MIN, n = nums.size();
    // 处理第一个窗口
    for(int i = 0; i < k; ++i)
    {
        sum += nums[i];
    }
    res = max(res, sum/k);
    // 之后滚动这个长度为 k 的窗口即可
    for(int i = k; i < n; ++i)
    {
        sum -= nums[i-k];
        sum += nums[i];
        res = max(res, sum/k);
    }
    return res;
}