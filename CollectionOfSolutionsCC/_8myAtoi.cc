#include "Solution.h"

int Leetcode1_100::Solution::myAtoi(string s)
{
    // 目标是把一个字符串转换成一个32位的有符号整数，这道题显然是一道考察细节的题目，本身逻辑上没有难点
    // 按部就班进行转换即可
    // idx 是下标变量，代表当前最靠左的待处理下标
    // res 存储转换结果，需要在必要时进行舍入
    int idx = 0, res = 0;
    // 1. 去除前导空格
    while(s[idx] == ' ')
    {
        ++idx;
    }
    // 循环结束时 s[idx] 是一个非空格的字符
    // 2. 检查符号位是否有负号
    // 只有这个位置上有负号，才把 sign 变量设置为-1，其它('+'或者数字)都把sign设置为1
    int sign = s[idx] == '-' ? -1 : 1;
    // 如果 idx 位置是一个符号('+'/'-')，就把idx右移一位，否则不移动(C/C++可以用 true 代表1，false 代表0)
    idx += s[idx] == '-' || s[idx] == '+';
    // 3. 数值部分转化+溢出检查
    // 循环向 res 中添加数字，退出条件为遇到非数字字符或者到达了字符串结尾
    // 前置零在这个方法里其实不用管，因为 res 在遇到第一个非零数之前一直是零
    while(idx < s.size() && isdigit(s[idx]))
    {
        // 还是注意判断32位溢出的检查方法，要反向进行检查，不能正向计算
        // 同时注意，字符串是字符数组，ASCII字符和正常数字之间也要进行一步转化
        // 边界检查同样需要分 sign 的正负情况
        // res * 10 + sign*(s[idx]-'0') > INT_MAX
        // res * 10 + sign*(s[idx]-'0') < INT_MIN
        if(sign == 1 && res > (INT_MAX-sign*(s[idx]-'0'))/10)
        {
            // 按题意处理即可
            return INT_MAX;
        }
        if(sign == -1 && res < (INT_MIN-sign*(s[idx]-'0'))/10)
        {
            return INT_MIN;
        }
        res = res * 10 + sign*(s[idx]-'0');
        ++idx;
    }
    // 正常退出，返回 res 即可
    return res;
}