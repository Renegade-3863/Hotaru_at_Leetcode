#include "Solution.h"

bool Leetcode1500_1600::Solution::threeConsecutiveOdds(vector<int>& arr)
{
    // 简单题，简单做（）
    // 我们只需要遍历一遍整个数组，用一个数据记录 "从当前位置的上一个位置开始，前面已经有几个连续的奇数" 这一信息即可
    int cnt = 0;
    for(const int& num : arr)
    {
        // 如果 num 是奇数，那么对 cnt 加 1，如果加 1 后 cnt == 3
        // 那么就返回 true
        if(num & 1)
        {
            if(++cnt == 3)
            {
                return true;
            }
        }
        else
        {
            // 否则，num 是偶数，那么我们把 cnt 清零即可
            cnt = 0;
        }
    }
    // 遍历完成，没有找到满足要求的连续奇数子数组，返回 false 即可
    return false;
}