#include "Solution.h"

int Leetcode401_500::Soltuion::findMaxConsecutiveOnes(vector<int>& nums)
{
    // 简单题简单做，我们按照题目的要求来执行相关操作即可完成对二进制数组中最大连续1个数的计数
    // 最后的答案值
    // cur 用于表示当前连续 1 的个数记录
    int res = 0, cur = 0;
    for(const int& num : nums)
    {
        // 遇 0 则重置 cur，不用更新 res
        // 遇 1 则更新 cur，同时更新 res
        // 这样做可以避免最后一组连续的 1 持续到数组结尾的问题
        if(num == 0)
        {
            cur = 0;
        }
        else
        {
            res = max(res, ++cur);
        }
    }
    return res;
}