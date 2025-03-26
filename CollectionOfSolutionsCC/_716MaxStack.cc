#include "Solution.h"

// 其实看到这道题，我最直接的想法就是分开维护
// 分别维护一个单纯的栈和一个大顶堆
// 之后，当我们当前弹出的，或者之前弹出过的栈中元素出现在了大顶堆的堆顶，那么我们也同时从大顶堆中弹出一个元素
// 往大顶堆和正常栈中添加元素的操作同步进行即可
// 注意，C++ 提供了大顶堆的 STL 模版类，就是 priority_queue
Leetcode701_800::Soltuion::MaxStack::MaxStack()
{
    // STL 的构造函数会帮我们处理好它们的初始化，我们什么也不用做
}

void Leetcode701_800::Soltuion::MaxStack::push(int x)
{
    // 同步压入即可
    this->s.emplace(cnt, x);
    this->pq.emplace(x, cnt);
    ++cnt;
}

int Leetcode701_800::Soltuion::MaxStack::pop()
{
    auto [i, v] = s.top();
    while(removed.count(i))
    {
        s.pop();
        tie(i, v) = s.top();
    }
    s.pop();
    removed.insert(i);
    return v;
}

int Leetcode701_800::Soltuion::MaxStack::top()
{
    auto [i, v] = s.top();
    while(removed.count(i))
    {
        s.pop();
        tie(i, v) = s.top();
    }
    return v;
}

int Leetcode701_800::Soltuion::MaxStack::peekMax()
{
    auto [v, i] = pq.top();
    while(removed.count(i))
    {
        pq.pop();
        tie(v, i) = pq.top();
    }
    return v;
}

int Leetcode701_800::Soltuion::MaxStack::popMax()
{
    auto [v, i] = pq.top();
    while(removed.count(i))
    {
        pq.pop();
        tie(v, i) = pq.top();
    }
    pq.pop();
    removed.insert(i);
    return v;
}