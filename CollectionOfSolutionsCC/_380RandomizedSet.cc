#include "Solution.h"

Leetcode301_400::Solution::RandomizedSet::RandomizedSet()
{
    // 不是很难的一道设计题，唯一的难点在于 getRandom 函数
    // 如何实现结构中所有元素等概率返回？
    // 我们可以把结构中存储的值映射到一个固定的数轴上，具体的：[0, set.size()-1] 这个区间上
    // 这个映射关系可以通过哈希表来存储
    // key: 映射后的值，value: 原值
}

bool Leetcode301_400::Solution::RandomizedSet::insert(int val)
{
    if(this->remapping.find(val) != this->remapping.end())
    {
        // 已经存在了，不能重复插入
        return false;
    }
    // 否则，分别记录到 exist 和 mapping 结构中
    this->remapping[val] = this->idx++;
    this->memo.push_back(val);
    return true;
}

bool Leetcode301_400::Solution::RandomizedSet::remove(int val)
{
    // 如果这个数没有被添加过，返回 false，无法删除
    if(this->remapping.find(val) == this->remapping.end())
    {
        return false;
    }
    // 把要删除位置上的元素和 memo 结尾的元素交换，删除结尾的元素
    this->remapping[this->memo[this->memo.size()-1]] = this->remapping[val];
    swap(this->memo[this->remapping[val]], this->memo[this->memo.size()-1]);
    this->remapping.erase(val);
    this->memo.pop_back();
    return true;
}

int Leetcode301_400::Solution::RandomizedSet::getRandom()
{
    // 我们获取元素的总个数
    int size = this->memo.size();
    // 利用 rand() 接口获取一个 [0, size-1] 之间的随机数，返回对应的元素
    return this->memo[rand()%size];
}