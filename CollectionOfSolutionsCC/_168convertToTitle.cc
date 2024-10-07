#include "Solution.h"

string Leetcode101_200::Solution::convertToTitle(int columnNumber)
{
    // 本题实际上是一个类似26进制转换的问题
    // 我们可以简单地进行模拟
    string res = "";
    // 可以使用类似求十进制数到二进制序列的转换方案进行变换
    // 不断除 26，直到结果变为0
    while(columnNumber)
    {
        // 本题中，我们要求的是把 'A' -> 'Z' 之间的字母映射到 1-26 这26个数
        // 而不是一般的 k 进制数那样映射到 0-25 这26个数
        // 所以实际上 701 这个数应该对应的是 700，这样计算才是正确的
        --columnNumber;
        res += (char)(columnNumber%26+'A');
        columnNumber /= 26;
    }
    reverse(res.begin(), res.end());
    return res;
}