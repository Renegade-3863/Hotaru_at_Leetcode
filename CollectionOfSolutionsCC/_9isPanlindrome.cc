#include "Solution.h"

bool Leetcode1_100::Solution::isPanlindrome(int x)
{
    // 判断一个整数是不是回文数，可以说是基础题中的基础题了
    // 首先，负数一定不是回文数，可以直接返回 false
    if(x & (1 << 31))
    {
        return false;
    }
    // 是正数，则转换成数字数组用双指针判断即可，时间和空间复杂度都是 O(1)
    deque<int> digits;
    while(x)
    {
        digits.push_front(x%10);
        x /= 10;
    }
    // 循环结束后，digits 中存储了 x 每一位上的数字
    int n = digits.size();
    int left = 0, right = n-1;
    // 循环退出条件是左指针小于右指针，因为只要左指针不小于右指针，我们就可以认为整个数组已经被判断完全了
    // 两个指针相等，这两个指针指向的数字一定是一样的，无需判断了
    while(left < right)
    {
        if(digits[left] == digits[right])
        {
            ++left; --right;
        }
        else
        {
            return false;
        }
    }
    return true;
}