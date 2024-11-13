#include "Solution.h"

char Leetcode301_400::Solution::findDifference(string s, string t)
{
    // 一般这种能用哈希表的题，都会有更简便的算法，我们进行一些思考
    // 考虑位运算：
    // a ^ b ^ c ^ d ^ e 
    // 异或运算具有交换律，所以我们可以随意修改这个运算序列，结果不会收到影响
    // 所以，不难看出 a ^ a ^ b ^ b ^ c ^ c ^ d ^ d ^ e ^ d == a ^ d ^ a ^ c ^ e ^ d ^ c ^ e ^ b ^ b
    // 所以，我们直接将这两个字符串中的每一个字符进行异或运算，最后的结果就是我们要的那个多出来的字符
    int res = 0;
    for(const char& c : s)
    {
        res ^= c;
    }
    for(const char& c : t)
    {
        res ^= c;
    }
    return (char)res;
}