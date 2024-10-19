#include "Solution.h"

// 使用两个栈可以以很易懂的方式实现这个栈形式的队列
Leetcode201_300::Solution::MyQueue() {}

void Leetcode201_300::Solution::MyQueue::push(int x)
{
    // 可以使用两个栈来模拟一个队列的功能
    // 其中一个栈用作输入栈，另一个用作输出栈
    // 压入队列操作，可以通过直接压入输入栈中来完成
    this->stk1.push(x);
}

int Leetcode201_300::Solution::MyQueue::pop()
{
    // 弹出队列的操作可以通过从输出栈中弹出元素来实现，我们的先验假设是：输出栈中的元素是等同于队列中顺序的
    // 即：输出栈道栈顶元素就是最先压入 "模拟队列" 中的元素
    // 如果输出栈是空的，那么我们可以直接把输出栈中的元素逐一弹出并压入到输出栈中，这样就维护了我们上面的先验假设
    if(this->stk2.empty())
    {
        while(!this->stk1.empty())
        {
            this->stk2.push(this->stk1.top());
            this->stk1.pop();
        }
    }
    // 弹出一个输出栈顶部的元素即可
    int ret = this->stk2.top();
    this->stk2.pop();
    return ret;
}

int Leetcode201_300::Solution::MyQueue::peek()
{
    // 和 pop() 是类似的过程
    if(this->stk2.empty())
    {
        while(!this->stk1.empty())
        {
            this->stk2.push(this->stk1.top());
            this->stk1.pop();
        }
    }
    // 弹出一个输出栈顶部的元素即可
    return this->stk2.top();
}

bool Leetcode201_300::Solution::MyQueue::empty()
{
    return this->stk1.empty() && this->stk2.empty();
}