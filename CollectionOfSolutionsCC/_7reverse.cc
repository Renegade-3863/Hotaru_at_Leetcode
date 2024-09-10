#include "Solution.h"

int Leetcode1_100::Solution::reverse(int x)
{
    deque<int> digits;
    // 如果是负数，则 sign 赋值为-1，否则赋值为1
    int sign = x & (1 << 31) ? -1 : 1;
    // 把负数转成正数
    // 边界情况：x == -2147483648，特殊处理即可
    if (x == INT_MIN)
    {
        return 0;
    }
    x *= sign;
    while (x)
    {
        digits.push_front(x % 10);
        x /= 10;
    }
    // 循环结束后，digits 中存储了 x 中每一位上的值
    // 按中间值为界左右交换之后输出结果即可，是一个 O(1) 的方法(空间时间都是)
    int n = digits.size();
    // 0, 1, 2, 3, 4    5
    for (int i = 0; i < n/2; ++i)
    {
        // 位运算形式的数字交换
        digits[i] ^= digits[n - i - 1];
        digits[n - i - 1] ^= digits[i];
        digits[i] ^= digits[n - i - 1];
    }
    // 注意输出时的溢出问题，要提前一位进行判断
    int res = 0;
    for (int i = 0; i < n; ++i)
    {
        // res * 10 + digits[i] > INT_MAX;
        // 负数和正数的判断条件不一样，也要进行区分
        if (sign == 1 && res > (INT_MAX - digits[i]) / 10)
        {
            return 0;
        }
        // res * 10 + sign * digits[i] < INT_MIN;
        if (sign == -1 && res < (INT_MIN - sign * digits[i]) / 10)
        {
            return 0;
        }
        res = res * 10 + sign * digits[i];
    }
    return res;
}