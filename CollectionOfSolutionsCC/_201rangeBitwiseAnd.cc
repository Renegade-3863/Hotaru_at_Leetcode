#include "Solution.h"

int Leetcode201_300::Solution::rangeBitwiseAnd(int left, int right)
{
    // 本题最暴力的方案是直接遍历 [left, right] 区间中的所有值，挨个进行按位与操作
    int res = left;
    // 但是鉴于整个数值范围是 [-2147483648, 2147483647]
    // 这样的线性方案很容易就超时了
    while(++left <= right)
    {
        res &= left;
    }
    return res;
}

int rangeBitwiseAnd(int left, int right)
{
    // 考虑利用按位与这个计算的特殊性：
    // 无论多少个数位与到一起，只要这个序列中出现了一个0，那么最后的结果就总是0，
    // 想到这里，我们似乎可以考虑一位一位地组合出最后的 32 位结果
    // 这样我们的 2^32 级别的最坏复杂度就可以压缩到 稳定的 32 时间级别
    // 那么我们要解决的问题就是，如何确定某一位上的值，是否会在这个 [left, right] 序列上变成零？或者说这个位上在 left 位置就已经是 0 了
    // 注意到，我们可以利用前面见过的 n & (n-1) 操作来实现仅检查所有在 left 的二进制中本来是1的位，而直接略过那些原本就已经是 0 的位，它们在最后的结果中一定是0
    int tmp = left;
    // 标记一个全1的掩码，遍历过程中动态变化
    int res = 0;
    for(int i = 0; i < 32; ++i)
    {
        // 要确定某一位i上的值，具体的，如果是1，在 [left, right] 范围上是否会从1变成0
        // 我们关注这个位发生变化的条件
        // 应该是后面的递增过程，满足 i 右侧的值从原始值增加到了 2^i，此时这个 2^i 才会变成 2^(i+1)，也就是把这个1变成0
        // 那么我们要检查的东西就很简单了
        // 关注 left 和 right 在 i 左侧的部分，如果二者是相等的，那么显然这个位没有向前进位，也就是没有发生变化，否则，很显然这个位一定会向前做贡献，否则前面的部分不可能变大
        // 也就是，总会存在一个中间时刻使得这个位置从 1 变 0 了
        // 我们可以通过一个掩码实现上面的思路
        if((left & 1) == 0)
        {
            left >>= 1;
            right >>= 1;
            continue;
        }
        // 否则对这个位以及前面的 left 和 right 部分进行检查
        // 只有相等的时候，这个位上的1才会剩下，同时，我们会发现，由于前面的部分都相等，我们可以简单地认为前面所有的1也都会剩下，因而其实也可以退出循环了
        if(left == right)
        {
            res = res | (left << i);
            break;
        }
        left >>= 1;
        right >>= 1;
    }
    return res;
}