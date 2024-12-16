#include "Solution.h"

int Leetcode301_400::Solution::getSum(int a, int b)
{
    // 要求 "不用加法进行加法计算"
    // 这种要求，不是位运算，就是位运算。。。
    // 我们考虑如何使用模2运算求出两个数的和
    // 首先，模2运算得出的结果是不带进位的加法结果
    // 我们需要做的是给这个结果加上进位
    // 举个例子：
    // 0010(2) + 0011(3) -> 模2运算：0001(1)
    // 对二者取按位与：0010，注意，这是一个进位，我们需要把它左移一位才能拿到正确的进位值
    // << 1 -> 0100
    // 之后把上面模2运算的结果再和这个进位做加法即可
    // 这就找到了一个递归过程
    // 直到我们的进位数变成全0，我们就可以退出计算了
    // 我们可以用 b 来存储每次加法的进位值，因为求过一次模2运算后，b 就没用了
    while(b)
    {
        // 第一步：先保存进位
        int tmp = a & b;
        // 模2运算
        a ^= b;
        b = (tmp << 1);
    }
    // 用 a 来存储最后的加法结果
    return a;
}