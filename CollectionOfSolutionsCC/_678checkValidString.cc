#include "Solution.h"

bool Leetcode601_700::Soltuion::checkValidString(string s)
{
    // 简单的栈类问题
    // 核心思想为使用一个栈记录所有未被匹配的左括号 "("
    // 检查直到整个遍历完成，是否可以保证栈是空即可
    // 相对于原本只匹配左右括号的题目，本题引入了星号，稍加分析，就应该能想到，不能把星号和左右括号放到一个栈中存储
    // 我们需要两个栈，分别存储括号和星号
    stack<int> leftCol;
    stack<int> stars;
    // 最后结束时，如果只考虑右括号没法清空 leftCol
    // 那么我们就可以调用 stars 中的星号来进行匹配，而存储对应的位置就保证了我们可以在检查时确保不会把前面的星号匹配给任何它后面的左括号
    // 最后，返回 leftCol.empty() 即可
    int n = s.size();
    for(int i = 0; i < n; ++i)
    {
        switch(s[i])
        {
            case '(':
                leftCol.push(i);
                break;
            case ')':
                if(leftCol.empty())
                {
                    // 如果这个右括号没法匹配，那么根据题意，我们优先检查是否有星号可以处理这个右括号
                    if(!stars.empty())
                    {
                        // 有星号可用，那就匹配一个
                        stars.pop();
                        break;
                    }
                    return false;
                }
                // 可以匹配，就匹配一次
                leftCol.pop();
                break;
            case '*':
                stars.push(i);
                break;
            default:
                // 默认情况什么都不做 
        }   
    }
    // 处理结束后，leftCol 中可能还有未匹配的左括号，此时我们只能求助于 stars
    // 
    while(!leftCol.empty())
    {
        // 检查 stars.top() 是否大于 leftCol.top()，如果是，那么同时弹出两个栈顶部元素即可
        // 否则，直接 return false 即可
        if(stars.empty() || stars.top() < leftCol.top())
        {
            return false;
        }
        stars.pop();
        leftCol.pop();
    }
    return true;
}