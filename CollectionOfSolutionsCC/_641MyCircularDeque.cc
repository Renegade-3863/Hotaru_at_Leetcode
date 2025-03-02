#include "Solution.h"

// 数据结构类题目，考察我们的设计思维和细节处理能力
// 依然不难，我们可以定义两个指针，head 和 tail，定义为 [haed, tail) 中有元素
// 以及一个个数标记 cnt
// 当 cnt == 0 时，isEmpty 为 true
// 当 cnt == k 时，isFull 为 true
// 最后把 k 保存到结构中，作为 size 变量
Leetcode601_700::Soltuion::MyCircularDeque::MyCircularDeque(int k)
{
    // 把三个基本变量进行初始化
    this->size = k;
    this->head = 0;
    this->tail = 0;
    this->cnt = 0;
    this->nums = vector<int>(k);
}

bool Leetcode601_700::Soltuion::MyCircularDeque::insertFront(int value)
{   
    // 首先检查是否 isFull
    // 如果是满的，那么没法添加元素
    if(this->isFull())
    {
        return false;
    }
    // cout << "InsertFront ";
    // 头指针往前走一步
    this->head = (this->head-1+this->size)%this->size;
    // 把 value 放到 (this->head-1+this->size)%this->size 下标处
    this->nums[this->head] = value;
    // showCase();
    ++this->cnt;    
    return true;
}

bool Leetcode601_700::Soltuion::MyCircularDeque::insertLast(int value)
{
    // 首先检查是否 isFull
    if(this->isFull())
    {
        return false;
    }
    // cout << "InsertLast" << endl;
    this->nums[this->tail] = value;
    ++this->cnt;
    this->tail = (this->tail+1)%this->size;
    // showCase();
    return true;
}

bool Leetcode601_700::Soltuion::MyCircularDeque::deleteFront()
{
    if(this->isEmpty())
    {
        return false;
    }
    --this->cnt;
    this->head = (this->head+1)%this->size;
    // showCase();
    return true;
}

bool Leetcode601_700::Soltuion::MyCircularDeque::deleteLast()
{
    if(this->isEmpty())
    {
        return false;
    }
    --this->cnt;
    this->tail = (this->tail-1+this->size)%this->size;
    return true;
}

int Leetcode601_700::Soltuion::MyCircularDeque::getFront()
{
    if(this->isEmpty())
    {
        return -1;
    }
    return this->nums[this->head];
}


int Leetcode601_700::Soltuion::MyCircularDeque::getRear()
{
    if(this->isEmpty())
    {
        return -1;
    }
    return this->nums[this->tail];
}

bool Leetcode601_700::Soltuion::MyCircularDeque::isEmpty()
{
    return this->cnt == 0;
}

bool Leetcode601_700::Soltuion::MyCircularDeque::isFull()
{
    return this->cnt == this->size;
}

void Leetcode601_700::Soltuion::MyCircularDeque::showCase()
{
    if(this->isEmpty())
    {
        return;
    }
    for(int i = 0; i < this->size; ++i)
    {
        cout << this->nums[i] << " ";
    }
    cout << endl;
}