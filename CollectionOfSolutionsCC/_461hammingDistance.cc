#include "Solution.h"

int Leetcode401_500::Soltuion::hammingDistance(int x, int y)
{
    // 简单的位运算模拟题，按要求做就行了
    // 两种基本方案，第二种实现更简单
    // 1. 直接按位逐位对比 x 和 y，输出最后结果
    // 2. 先用异或运算，结果中保留了原来 x 和 y 中对应值不同的那些位为1，之后统计结果值中1的个数
    // 我们这里采用第二种算法
    // 获取异或结果
    int tmp = x ^ y;
    // 循环结束条件为 tmp == 0
    // res 记录总的 1 的个数
    int res = 0;
    while(tmp)
    {
        if(tmp%2)
        {
            ++res;
        }
        tmp >>= 1;
    }
    return res;
}