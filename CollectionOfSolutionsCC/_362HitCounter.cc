#include "Solution.h"

Leetcode301_400::Solution::HitCounter::HitCounter() : size(0)
{
}

// void Leetcode301_400::Solution::HitCounter::hit(int timestamp)
// {
//     // 根据给定的时间戳，我们检查维护的这个双端队列
//     this->visible.emplace_back(timestamp);
// }

// 优化版本的 hit
// 进阶要求是：同一秒发生的点击次数非常多，我们上面这种简单的添加元素策略就不那么可行，因为可能会搞出来非常大的队列
// 所以我们可以优化一下操作
// 如果敲击时间戳等于队尾元素的时间戳，我们给对应敲击的次数进行递加
void Leetcode301_400::Solution::HitCounter::hit(int timestamp)
{
    if(!this->visible.empty() && this->visible.back().timestamp == timestamp)
    {
        ++(this->visible.back().cnt);
    }
    else
    {
        this->visible.emplace_back(timestamp);
    }
    ++this->size;
}

int Leetcode301_400::Solution::HitCounter::getHits(int timestamp)
{
    // 如果当前时间戳和队头的敲击之间的时间差距超过了5分钟，我们直接弹出它即可
    // 注意，这个过程应该是循环进行的
    while(!this->visible.empty() && timestamp - this->visible.front().timestamp >= 300)
    {
        this->size -= this->visible.front().cnt;
        this->visible.pop_front();
    }
    // 返回队列的大小即可
    return this->size;
}