#include "Solution.h"

bool Leetcode301_400::Solution::isPowerOfFour(int n)
{
    // 本质上和是 2 的幂的判断方法类似
    // 首先明确：如果一个数是 4 的幂，那么它一定是 2 的幂
    // 所以，我们可以先判断它是不是 2 的幂
    // 而一个数在什么情况下，是 2 的幂，而不是 4 的幂呢？
    // 我们列举几个 4 的幂的例子来观察一下：
    // 000...01, 000...100, 000...10000, ...
    // 不难看出来，所有 4 的幂的二进制表示中也都只有一个1
    // 而与 2 的幂不同的是，这些二进制表示中的唯一一个1只能出现在从右(下标从1开始)开始的奇数位上
    // 所以我们只需要检查
    // 1. 这个数的二进制表示是不是只有一位1
    // 2. 这个1是不是在奇数位上
    // 即可
    // 1. 通过位运算可以简单检查
    // n-1 用于丢弃最右侧的那个1，如果原来的二进制表示中只有这一个1，那么 n & (n-1) 的结果就是0，否则，说明这最右侧的1左边肯定还有1，不满足条件1，直接返回 false 即可
    // 不过由于本身负数不可能是 4 的幂，我们遇到负数直接返回 false 即可
    if(n <= 0)
    {
        return false;
    }
    if((n & n-1) > 0)
    {
        return false;
    }
    // 2. 这个可以通过一个掩码来检查
    int mask = 0x55555555;
    return mask & n;
}