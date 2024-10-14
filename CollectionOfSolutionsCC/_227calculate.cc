#include "Solution.h"

int Leetcode201_300::Solution::calculate2(string s)
{
    // 本题就是 224 题的简化版，不带括号了，我们几乎可以简单照搬 224 题的代码过来
    // 可以尝试自己重写一遍
    char sign = '+';
    int num = 0;
    stack<int> adders;
    int n = s.size(), i = 0;
    while(i < n)
    {
        char c = s[i];
        // 分析不同的情况
        // 1. 当前字符是一个数字字符
        if(isdigit(c))
        {
            // 累计当前数字
            num = num*10+(c-'0');
        }
        // 2. 当前字符是一个操作符
        else if(c != ' ')
        {
            int prev = adders.empty() ? 0 : adders.top();
            switch(sign) 
            {
                case '+':
                adders.push(num);
                break;
                case '-':
                adders.push(-num);
                break;
                case '*':
                adders.pop();
                adders.push(prev*num);
                break;
                case '/':
                adders.pop();
                adders.push(prev/num);
            }
            num = 0;
            sign = c;
        }
        // 3. 当前字符是一个空格，我们直接跳过它即可
        // 这里直接合并写了
        ++i;
    }
    // 结束后，我们还需要把最后一个数字添加到加数栈中
    int prev = adders.empty() ? 0 : adders.top();
    switch(sign)
    {
        case '+':
        adders.push(num);
        break;
        case '-':
        adders.push(-num);
        break;
        case '*':
        adders.pop();
        adders.push(prev*num);
        break;
        case '/':
        adders.pop();
        adders.push(prev/num);
    }
    int res = 0;
    while(!adders.empty())
    {
        res += adders.top();
        adders.pop();
    }
    return res;
}