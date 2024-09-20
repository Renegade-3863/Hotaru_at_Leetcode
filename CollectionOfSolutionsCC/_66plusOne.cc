#include "Solution.h"

vector<int> Leetcode1_100::Solution::plusOne(vector<int>& digits)
{
    // 对一个用数组存储的数字加1，显然可以用我们前面的简单加法逻辑
    // 只需要考虑如果出现最高位有进位，需要在 digits 前面额外添加一位1
    int n = digits.size();
    // carry 记录进位
    int carry = 1;
    for(int i = n-1; i >= 0; --i)
    {
        // 取出当前位的进位，保留余数
        digits[i] += carry;
        carry = digits[i] / 10;
        digits[i] %= 10;
    }
    // 检查最高位是否有进位
    if(carry)
    {
        digits.insert(digits.begin(), 1);
    }
    return digits;
}