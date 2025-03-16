#include "Solution.h"

int Leetcode601_700::Soltuion::calPoints(vector<string>& operations)
{
    // 简单题简单做
    // 我们需要一个字符串 -> 整数的转换函数，因为原数据中可能有负数，所以 stoi 函数可能不适用
    function<int(const string&)> myStoi = [&](const string& num) -> int
    {
        int res = 0;
        // num 是一个负数，那么我们进入 “负数处理" 分支
        if(num[0] == '-')
        {
            return -1*stoi(num.substr(1));
        }
        // 否则，num 就是正常的正数，那么我们直接返回 stoi(num) 即可
        return stoi(num);
    };
    // 有了分数的处理函数，其它三种字母的处理逻辑直接写出来就可以了
    // 用栈记录最多两个运算数
    stack<int> ops;
    // ans 为最后的结果
    int ans = 0;
    for(const auto& operation : operations)
    {
        if(operation == "+")
        {
            ans = 0;
            // 按题意，这种情况下需要计算 op1+op2
            ans += ops.top();
            int tmp = ops.top();
            ops.pop();
            ans += ops.top();
            ops.push(tmp);
            ops.push(ans);
        }
        else if(operation == "D")
        {
            // 本回合得到的分数是前一个得分的两倍，我们假定前两次出现的数据中，先出现的保存在 op1 中
            ops.push(ops.top()*2);
        }
        else if(operation == "C")
        {
            ops.pop();
        }
        // 剩余情况为 operation 是数字的情况
        else
        {
            ops.push(myStoi(operation));
        }
    }
    ans = 0;
    while(!ops.empty())
    {
        ans += ops.top();
        ops.pop();
    }
    return ans;
}