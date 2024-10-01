#include "Solution.h"

int Leetcode101_200::Solution::evalRPN(vector<string>& tokens)
{
    // 数据结构课上栈相关的经典例题，基本就是栈的简单推弹
    // 逆波兰表达式就是一般算术表达式存储到二叉树上后后序遍历出来的结果，优点在于不需要使用括号，编程计算十分简单
    // 基本思路是：
    // 使用两个栈，一个存储运算数，另一个存储运算符
    stack<string> optrs;
    stack<int> opnds;
    // 遇到一个数字，就把这个数压入运算数栈，遇到一个运算符，就根据这个运算符决定要如何进行后续计算
    int res = 0, n = tokens.size();
    for(int i = 0; i < n; ++i)
    {
        // 如果遍历到了一个运算符，那么根据它的类型决定要如何对运算数栈中的数字进行操作
        if(tokens[i] == "*")
        {
            // 如果是一个乘号
            int op1 = opnds.top();
            opnds.pop();
            int op2 = opnds.top();
            opnds.pop();
            // 计算乘积
            int mult = op2 * op1;
            opnds.push(mult);
        }
        else if(tokens[i] == "/")
        {
            // 如果是一个除号
            int op1 = opnds.top();
            opnds.pop();
            int op2 = opnds.top();
            opnds.pop();
            int div = op2 / op1;
            opnds.push(div);
        }
        else if(tokens[i] == "+")
        {
            int op1 = opnds.top();
            opnds.pop();
            int op2 = opnds.top();
            opnds.pop();
            int addi = op2 + op1;
            opnds.push(addi);
        }
        else if(tokens[i] == "-")
        {
            int op1 = opnds.top();
            opnds.pop();
            int op2 = opnds.top();
            opnds.pop();
            int subi = op2 - op1;
            opnds.push(subi);
        }
        // 否则，这是一个代表整数的字符串，我们需要把它转成一个整形变量存入操作数栈中
        // 应该不用大数运算那些字符串表示的操作，那样有点太麻烦了。。。。
        else
        {
            int num = 0, sign = tokens[i][0] == '-' ? -1 : 1;
            int cur = tokens[i][0] == '-' ? 1 : 0;
            while(cur < tokens[i].size())
            {
                num = num * 10 + (tokens[i][cur]-'0');
                ++cur;
            }
            // 记录好这个整数的整型形式后，就可以压栈了
            opnds.push(num*sign);
        }
    }
    // 这个最后剩下的值就是答案
    return opnds.top();
}