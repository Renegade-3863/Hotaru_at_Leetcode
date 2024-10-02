#include "Solution.h"

Leetcode101_200::Solution::MinStack::MinStack()
{
    // 构造函数不需要做任何事情，STL 容器会被自动创建
}

Leetcode101_200::Solution::MinStack::~MinStack()
{
    // 析构函数也不需要做任何人群，STL 容器会被自动析构
}

void Leetcode101_200::Solution::MinStack::push(int val)
{
    // 首先，往正常的栈中压入当前元素
    this->original.push(val);
    // 判断辅助的栈中栈顶的元素是否是小于 val 的，如果是，就再压入一个栈顶元素
    // 否则，就再压入一个 val
    if(mono.empty() || mono.top() >= val)
    {
        mono.push(val);
    }
    else
    {
        mono.push(mono.top());
    }
}

void Leetcode101_200::Solution::MinStack::pop()
{
    // 要弹出一个元素，由于我们添加元素的时候保证了 mono 栈和 original 栈二者的元素是同步添加的
    // 因而这里可以直接从两个栈中各弹出一个元素
    mono.pop(); original.pop();
}

int Leetcode101_200::Solution::MinStack::top()
{
    // 这里直接返回 original 的 top 即可
    return original.top();
}

int Leetcode101_200::Solution::MinStack::getMin()
[
    // 这里直接返回 mono 的 top 即可
    return mono.top();
]