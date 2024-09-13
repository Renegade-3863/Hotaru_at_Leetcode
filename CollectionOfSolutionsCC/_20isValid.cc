#include "Solution.h"

bool Leetcode1_100::Solution::isValid(string s)
{
    // 本题要求我们检查一组括号的合法性(即：左右括号是否均一一匹配)
    // 简单的想法很显然是利用栈
    // 用一个栈存储所有出现过的左括号，不管是哪一种都直接压入这个栈中
    // 注意观察本题的不同要求，根据要求的不同可能会需要对栈的使用策略进行更改
    stack<char> leftCols;
    int n = s.size();
    for (int i = 0; i < n; ++i)
    {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{')
        {
            leftCols.push(s[i]);
        }
        else
        {
            switch (s[i])
            {
            case ')':
                if (leftCols.empty() || leftCols.top() != '(')
                {
                    return false;
                }
                leftCols.pop();
                break;
            case ']':
                if (leftCols.empty() || leftCols.top() != '[')
                {
                    return false;
                }
                leftCols.pop();
                break;
            case '}':
                if (leftCols.empty() || leftCols.top() != '{')
                {
                    return false;
                }
                leftCols.pop();
                break;
            }
        }
    }
    // 之所以要检查 leftCols 是否为空，是因为我们要确保所有左括号也都被匹配了
    return leftCols.empty();
}