#include "Solution.h"

Leetcode301_400::Solution::MovingAverage::MovingAverage(int size) : maxSize(size), sum(0)
{
    // 可以用很简单的方式来实现这个接口，我们保存一个 maxSize 作为这个窗口中元素的最大个数
    // 之后用一个内置的队列来实际维护这个窗口中全部的元素，用一个 sum 来加速平均数的实际运算
}

double Leetcode301_400::Solution::MovingAverage::next(int val)
{
    // 如果当前窗口中的元素个数不足上限值，那么我们直接把这个新元素添加到队列尾部，之后更新 sum 并返回结果即可
    if(this->q.size() < this->maxSize)
    {
        this->sum += val;
        this->q.push(val);
        return this->sum / (double)this->q.size();
    }
    // 否则，我们先弹出队头的那个元素，之后压入 val，并更新 sum 和计算返回结果
    sum -= q.front();
    q.pop();
    q.push(val);
    sum += val;
    return sum / this->maxSize;
}