#include "Solution.h"

string Leetcode1_100::Solution::addBinary(string a, string b)
{
    // 可以说本题就是一道简单版(二进制版)的大数相加问题
    int m = a.size(), n = b.size();
    int i = m-1, j = n-1;
    // 记录进位
    int carry = 0;
    string res = "";
    while(i >= 0 || j >= 0)
    {
        int x = i >= 0 ? a[i]-'0' : 0, y = j >= 0 ? b[j]-'0' : 0;
        int tmp = x+y+carry;
        carry = tmp>>1;
        tmp %= 2;
        res += char(tmp+'0');
    }
    // 别忘了最高位的进位，如果有的话，填上一个进位即可
    if(carry)
    {
        res += '1';
    }
    reverse(res.begin(), res.end());
    return res;
}