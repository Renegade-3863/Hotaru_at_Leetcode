#include "Solution.h"

Leetcode701_800::Soltuion::KthLargest::KthLargest(int k, vector<int>& nums)
{
    // 这里已经把 pq 初始化完成了
    // 初始化步骤，我们把 nums 中的数据插入到对象内部的优先队列中
    for(const auto& num : nums)
    {
        this->pq.push(num);
        if(this->pq.size() > k)
        {
            this->pq.pop();
        }
    }
    this->cnt = k;
}

int Leetcode701_800::Soltuion::KthLargest::add(int val)
{
    // 把 val 插入到 this->pq 中
    this->pq.push(val);
    // 此时 this->pq 的大小可能会大于 k，如果是这样，我们先弹出最大的那一个，之后再返回堆顶元素
    if(this->pq.size() > this->cnt)
    {
        this->pq.pop();
    }
    return this->pq.top();
    }
    priority_queue<int, vector<int>, greater<int>> pq;
    int cnt = 0;
}