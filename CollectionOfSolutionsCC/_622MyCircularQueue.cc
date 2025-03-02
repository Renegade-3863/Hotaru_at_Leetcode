#include "Solution.h"
#include <iostream>

Leetcode601_700::Soltuion::MyCircularQueue(int k)
{
    // resize elem 数组即可，front 和 rear 指针简单初始化一下
    this->elem.resize(k);
    std::fill(this->elem.begin(), this->elem.end(), 0);
    // 最开始，队列内没有元素
    this->front = 0;
    this->rear = 0;
    this->size = k;
    this->cnt = 0;
}

bool Leetcode601_700::Soltuion::MyCircularQueue::enQueue(int value)
{
    // 检查是否已满，用 isFull() 函数
    if(this->isFull())
    {
        // 满了，没法插入，返回 false
        return false;
    }
    // 入队，需要扩展 this->rear，注意超出范围时对 rear 进行回卷
    this->elem[rear] = value;
    // 计算 (this->rear+1)%k
    this->rear = (this->rear+1)%this->size;
    ++this->cnt;
    // 队头不用动
    return true;
}

bool Leetcode601_700::Soltuion::MyCircularQueue::deQueue()
{
    // 检查是否为空，用 isEmpty() 函数
    if(this->isEmpty())
    {
        return false;
    }
    // 我们并不需要把 this->elem[front] 处的元素实际进行清除，只移动 front 指针即可
    this->front = (this->front+1)%this->size;
    --this->cnt;
    return true;
}

int Leetcode601_700::Soltuion::MyCircularQueue::Front()
{
    // 返回 this->elem[front]，如果 isEmpty() 为 false
    if(!this->isEmpty())
    {
        return this->elem[this->front];
    }
    return -1;
}

int Leetcode601_700::Soltuion::MyCircularQueue::Rear()
{
    if(!this->isEmpty())
    {
        return this->elem[(this->rear+this->size-1)%this->size];
    }
    return -1;
}

bool Leetcode601_700::Soltuion::MyCircularQueue::isEmpty()
{
    return this->cnt == 0;
}

bool Leetcode601_700::Soltuion::MyCircularQueue::isFull()
{
    return this->cnt == this->size;
}


