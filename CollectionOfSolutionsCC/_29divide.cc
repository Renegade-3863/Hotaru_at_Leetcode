#include "Solution.h"

int Leetcode1_100::Solution::divide(int dividend, int divisor)
{
    // 不使用乘除法和取余运算实现两数相除
    // 最朴素的方式是使用持续减，不过这种方法显然很傻，我们考虑有没有别的解决方案
    // 如果学过快速乘和快速幂的人应该会较快的反应出相关的处理方法
    // 基本的思路是这样的：
    // 观察一个除法式子：dividend / divisor = quotient ... remainder
    // 前面两个我们可以先不管，观察这个 quotient
    // 它是一个整数
    // 而一个整数可以用任何二进制串表示出来！
    // 因而我们就引出了快速除的方案
    // dividend / divisor = quotient ... remainder = (x1*2^m + x2*2^(m-1) + x3*2^(m-2) + ...) ... remainder
    // 我们要计算的无非就是这里的这些 (x1, x2, x3, ...) 向量
    // 如何计算？
    // 我们可以不断地计算 2 的任何次幂乘 divisor，直到这个值大于了 dividend，之后我们就可以逐步计算上面那个向量了
    // 注意我们并不会实际用到乘法，乘二可以通过编程语言内置的移位运算符来实现
    // 明确了思路，代码上无非就是一些细节问题了
    // 先考虑最简单的两个正整数相除
    // 符号不相同的，我们可以把它们转换成同号进行处理即可

    // 获取两个数字的符号
    int sign1 = dividend >> 31;
    int sign2 = divisor >> 31;
    // 根据二者是否同号决定最终结果符号
    // 如果取异或是1，说明二者异号，否则二者同号
    int sign = sign1 ^ sign2 ? -1 : 1;
    // 直接计算一些特殊情况
    // 被除数是 INT_MIN 的情况
    if (dividend == INT_MIN)
    {
        if (divisor == INT_MIN)
        {
            return 1;
        }
        if (divisor == 1)
        {
            return INT_MIN;
        }
        if (divisor == -1)
        {
            return INT_MAX;
        }
    }
    // 是否还有其他边界情况需要特殊处理？
    if (divisor == INT_MIN)
    {
        // 当除数是 INT_MIN 时，只有被除数也是 INT_MIN 才返回1，否则结果一定是0
        return dividend == INT_MIN;
    }
    if (dividend == -1)
    {
        if (divisor == -1 || divisor == 1)
        {
            return ~divisor + 1;
        }
        return 0;
    }
    // 其它情况下，只需要把除数转换成和被除数同号即可
    if (sign == -1)
    {
        divisor = ~divisor + 1;
    }
    // 之后就按被除数的符号进行后续计算即可
    // 先持续对 divisor 乘2
    // 循环结束条件为：divisor * 2^m 超过了 dividend，或者 divisor * 2^m 超过了对应的上限值
    // C/C++ 的右移运算符是符号移位，所以不用担心会把负数移成正数
    // 反向计算，避免 divisor 的计算溢出
    int rec = divisor;
    int power = 1;
    while ((dividend >= 0 && (dividend >> 1) >= divisor) || (dividend < 0 && (dividend >> 1) <= divisor))
    {
        power <<= 1;
        divisor <<= 1;
    }
    // 循环结束后 divisor 的值是满足 divisor * 2^m 这样的形式的绝对值最大的值
    // 持续对 dividend 进行减少运算
    int res = 0;
    // dividend == 0 的时候需要直接退出循环，不然会引起死循环
    while ((dividend > 0 && dividend >= rec) || (dividend < 0 && dividend <= rec))
    {
        if ((dividend >= 0 && dividend >= divisor) || (dividend < 0 && dividend <= divisor))
        {
            res += power;
            dividend -= divisor;
        }
        power >>= 1;
        divisor >>= 1;
    }
    // 循环结束后，res 中的值乘以 sign就是最后的结果
    return sign == 1 ? res : ~res + 1;
}