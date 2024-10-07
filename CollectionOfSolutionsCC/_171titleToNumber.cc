#include "Solution.h"

int Leetcode101_200::Solution::titleToNumber(string columnTitle)
{
    // 本题是168题的反问题，要求我们在已知字母表达的情况下，计算出原原始的数字形式
    // 可以看作是26进制转10进制的问题
    // 我们只需要使用类似正常的二进制数转十进制数的过程即可
    // 从后向前逐步进行转化即可
    int exp = 1, res = 0;
    for(int i = columnTitle.size()-1; i >= 0; --i)
    {
        res += exp * (columnTitle[i]-'A'+1);
        if(exp <= INT_MAX / 26)
        {
            exp *= 26;
        }
    }
    return res;
}