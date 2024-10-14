#include "Solution.h"

int Leetcode101_200::Solution::trailingZeroes(int n)
{
    // 本题是一道数学题，我们需要计算 n! 的结果中后缀零的数量
    // 考虑一些规律性的问题：
    // 1. 阶乘结果中的后缀零的个数一定是随着 n 的值变大而逐渐递增的
    //    这是因为：一旦中间结果出现了尾随零，那么这些零再后续乘以任何数都不可能变回非零数了
    // 2. 只有10这个因子有可能增添尾随零
    //    这个比较难证明，我们考虑乘法的运算过程
    //    24
    //  x 43
    //  ------
    //  ...2
    // 注意这个新结果的末尾值，只有它才能影响到尾随零的个数，所有前面的值都不可能对尾随零的个数产生影响
    // 而这一位在乘法中又恰好不可能出现上下层的求和得零问题，故我们可以简单地明确，只能通过两个整数乘积得出新的零
    // 而两个整数的成绩要得到新的零，就只能是 2x5 / 5x2 (更大的结果：4x5 / 5x4; 6x5 / 5x6; 8x5 / 5x8; 这些从本质上说都是 2x5，只是多了一些其它的因数，而这些额外的因数不会影响尾随零的个数)
    // 所以我们只需要检查整个因子序列中 5 出现的次数
    // 如果多了一个5，由于不难看出，我们总能找出更多的2这个因子，拿出来和这些5组合，新添出新的尾随零
    // 因而我们可以直接计算 n 的所有因子中 5 这个质因子的个数之和，每一个5都一定可以拿到一个2组合成一个10，也就是尾随零的总个数
    int res = 0;
    // 枚举所有的阶乘因子
    while(n)
    {
        res += n/5;
        n /= 5;
    }
    return res;
}