#include "Solution.h"

uint32_t Leetcode101_200::Solution::reverseBits(uint32_t n)
{
    // 简单题简单做，我们可以直接拿一个新的板子逐位地对 n 进行反转
    int rev = 0;
    // 注意到，如果 n 经过某次移位后变成零了，那么由于此时我们 rev 中剩下的位也都是零，所以自然不用继续反转，可以提前退出循环
    for(int i = 0; i < 32 && n > 0; ++i)
    {
        rev = rev | ((n & 1) << (31-i));
        n >>= 1;
    }
    return rev;
}