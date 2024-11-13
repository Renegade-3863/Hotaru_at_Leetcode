#include "Solution.h"

void Leetcode301_400::Solution::reverseString(vector<char>& s)
{
    // 简单题简单做，我们直接用位运算就可以完成数组元素的反转
    // 遍历只需要遍历前半部分
    int n = s.size();
    for(int i = 0; i < n/2; ++i)
    {
        s[i] ^= s[n-1-i];
        s[n-1-i] ^= s[i];
        s[i] ^= s[n-1-i];
    }   
}