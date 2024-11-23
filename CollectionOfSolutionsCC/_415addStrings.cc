#include "Solution.h"

string Leetcode401_500::Solution::addStrings(string num1, string num2)
{
    // 大数加法，简单模拟即可
    string res;
    int m = num1.size(), n = num2.size();
    vector<int> board(max(m, n)+1, 0);
    int len = board.size();
    int i = 0;
    while(i < m || i < n)
    {
        int add1 = i < m ? num1[m-i-1]-'0' : 0;
        int add2 = i < n ? num2[n-i-1]-'0' : 0; 
        board[len-i-1] = add1 + add2;
        ++i;
    }
    // 之后处理进位，从后往前处理
    // 记录进位值
    int carry = 0;
    for(int i = len-1; i > 0; --i)
    {
        board[i-1] += board[i]/10;
        board[i] %= 10;
    }
    // 进行输出，注意处理开头位置，如果开头是零，那么我们不能输出开头的零
    for(int i = board[0] == 0 ? 1 : 0; i < len; ++i)
    {
        res.push_back(board[i]+'0');
    }
    return res;
}