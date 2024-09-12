#include "Solution.h"

int Leetcode1_100::Solution::romanToInt(string s)
{
    // 本题是一道个人认为类似智力题，并且没有多大考察意义的题目，只有一个 key point，如果能 get 到这个点，就可以做出来了
    // 在转换回整数的过程中，如果遇到一个字符，它表示的数字是小于它后面紧邻的字符的，那说明我们遇到了一个连续两个字符表示的罗马数字
    // 而这样的罗马数字表示的值就是对应的后面单字符表示的数字减去前面单字符表示的数字的结果
    // 其它情况只需要简单地加上当前单字符的数字即可
    unordered_map<char, int> symbolValues = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000},
    };
    int res = 0, n = s.size();
    for(int i = 0; i < n; ++i)
    {
        if(i < n-1 && symbolValues[s[i]] < symbolValues[s[i+1]])
        {
            res -= symbolValues[s[i]];
        }
        else
        {
            res += symbolValues[s[i]];
        }
    }
    return res;
}