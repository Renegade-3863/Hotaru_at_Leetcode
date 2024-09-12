#include "Solution.h"

string Leetcode1_100::Solution::intToRoman(int num)
{
    // 简答至极的模拟题，打一张表之后按贪心思想进行计算即可
    // 建一张整数和对应的罗马数字表示的映射关系即可
    const pair<int, string> valueSymbols[] = {
        {1000, "M"},
        {900, "CM"},
        {500, "D"},
        {400, "CD"},
        {100, "C"},
        {90, "XC"},
        {50, "L"},
        {40, "XL"},
        {10, "X"},
        {9, "IX"},
        {5, "V"},
        {4, "IV"},
        {1, "I"},
    };
    string res = "";
    // 从大到小试数，如果当前值能从 num 中减去，就减，否则，跳到下一个更小的数尝试做减法
    for(const auto& [value, symbol] : valueSymbols)
    {
        while(num >= value)
        {
            res += symbol;
            num -= value;
        }
        if(num == 0)
        {
            break;
        }
    }
    return res;
}
