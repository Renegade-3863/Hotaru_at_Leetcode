#include "Solution.h"

string Leetcode501_600::Soltuion::convertToBase7(int num)
{
    if(num == 0)
    {
        return "0";
    }
    // 整数转七进制数的函数，和转二进制没有什么本质区别
    // 首先，如果 num 是负数，那么提取出这个负号
    string res;
    int sign = num < 0 ? -1 : 1;
    // 统一成正数，-2147483648 就不管了
    num = abs(num);
    // 之后不断对 num 除 7，把余数反序即可
    while(num)
    {
        res.push_back((num%7)+'0');
        num /= 7;
    }
    reverse(res.begin(), res.end());
    if(sign == -1)
    {
        res = "-" + res;
    }
    return res;
}