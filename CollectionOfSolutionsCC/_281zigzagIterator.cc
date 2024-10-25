#include "Solution.h"

Leetcode201_300::Solution::zigzagIterator(vector<int>& v1, vector<int>& v2)
{
    // 基本的思路是，把两个数组的元素保存到类本地，之后用一个指针模拟在这两个向量上来回交替的过程
    this->total = 0;
    this->msg.push_back(v1);
    this->msg[0].push_back(0);
    this->total += v1.size();
    this->msg.push_back(v2);
    this->msg[1].push_back(0);
    this->total += v2.size();
    // 初始化交替变量为0
    this->cnt = 0;
}

int Leetcode201_300::Solution::zigzagIterator::next()
{
    // 根据 cnt 当前的值进行下一个元素的提取
    // 如果当前这个子数组中没有元素，就跳到下一个数组中
    while(this->msg[this->cnt][this->msg[this->cnt].size()-1] == this->msg[this->cnt].size()-1)
    {
        cnt = (cnt+1)%2;
    }
    int ret = this->msg[this->cnt][this->msg[this->cnt][this->msg[this->cnt].size()-1]];
    ++this->msg[this->cnt][this->msg[this->cnt].size()-1];
    cnt = (cnt+1)%2;
    --this->total;
    return ret;
}

bool Leetcode201_300::Solution::zigzagIterator::hasNext()
[
    return this->total != 0;
]