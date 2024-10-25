#include "Solution.h"

// 初始化操作不需要做任何事
Leetcode201_300::Solution::MedianFinder::MedianFinder() : cnt(0) {}

void Leetcode201_300::Solution::MedianFinder::addNum(int num)
{
    // 根据当前 cnt 的值来决定这个 num 要添加到哪个队列中
    // 奇数个，此时假设我们规定添加到大优先队列中
    if(cnt % 2)
    {
        // 不过在添加之前，我们还需要判断一下，小优先队列中的顶部元素是否是不小于 num 的，如果小优先队列的顶部元素小于 num，我们需要把这个顶部元素弹出来添加到大优先队列中
        // 再把 num 添加到小优先队列中
        // 小优先队列顶部元素小于 num，先修改一下原队列
        if(smallQ.top() < num)
        {
            int tmp = smallQ.top();
            smallQ.pop();
            bigQ.push(tmp);
            smallQ.push(num);
        }
        else
        {
            bigQ.push(num);
        }
    }
    // 偶数个，注意此时可能会出现两个队列均为空的情况，所以需要特殊判断一下
    else
    {
        // 假设此时我们规定添加到小优先队列中
        // 添加之前，检查一下大优先队列顶部的元素是否是不大于 num 的
        if(!bigQ.empty() && bigQ.top() > num)
        {
            int tmp = bigQ.top();
            bigQ.pop();
            smallQ.push(tmp);
            bigQ.push(num);
        }
        else
        {
            smallQ.push(num);
        }
    }
    // 别忘了更新 cnt
    ++cnt;
}

double Leetcode201_300::Solution::MedianFinder::findMedian()
{
    // 如果 cnt 是奇数，直接返回小优先队列的顶部元素即可
    if(cnt % 2)
    {
        return double(smallQ.top());
    }
    // 如果 cnt 是偶数，返回大小优先队列的头部元素的平均值
    else
    {
        return ((double)(smallQ.top())+(double)(bigQ.top()))/2;
    }
}