#include "Solution.h"

int Leetcode701_800::Solution::countPrimeSetBits(int left, int right)
{
    // 暴力遍历即可
    // 我们可以用 __builtin_popcount 来简化获取一个数中二进制为 1 的数位个数的流程
    int res = 0;
    // 这道题来说，可能遇到的质数值只有 [0, 32] 之间的质数值
    // 所以我们只需要记录下面这些值：
    // {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}
    unordered_set<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    for(int i = left; i <= right; ++i)
    {
        int cnt = __builtin_popcount(i);
        if(primes.find(cnt) != primes.end())
        {
            ++res;
        }
    }
    return res;
}