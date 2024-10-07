#include "Solution.h"

int Leetcode101_200::Solution::hammingWeight(int n)
{
    // 简单题简单做，要求算出 n 的二进制表达式中 1 的个数
    // 我们简单模拟一遍即可
    int res = 0;
    while(n)
    {
        res += n&1;
        n >>= 1;
    }
    return res;
}

// 看到答案给出的利用 n&(n-1) 的优化策略，有点小 nb 的优化策略了属于是
int hammingWeight(int n)
{
    int ret = 0;
    // n-1 的结果在二进制上，是把当前 n 的二进制位上最右侧的1变成0，它右侧的所有位(原来是0)变成1
    // 因而 n&(n-1) 就相当于把 n 的二进制位上最右侧的1变为0，前面的位保持不变
    // 通过不断对一个非零的 n 执行这个操作，我们就可以一次去掉一个1，我们只需要记录这个操作的次数即可
    while(n)
    {
        n &= n-1;
        ++ret;
    }
    return ret;
}