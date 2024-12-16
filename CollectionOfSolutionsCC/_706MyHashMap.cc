#include "Solution.h"

// 本质实现方法和 705 题是一致的
Leetcode701_800::Soltuion::MyHashMap::MyHashMap()
{
    // 我们需要对链表数组进行大小初始化，大小等于取模素数 p 的值
    this->lists = vector<list<pair<int, int>>>(MyHashMap::p);
}

// 往哈希表中添加一个键值对的函数，我们需要判断 key 值对应的链表中是否存在 value 值，如果存在的话不能进行插入
void Leetcode701_800::Soltuion::MyHashMap::put(int key, int value)
{
    // 首先检查对应的链表中是否存在 value 这个值
    // 计算出哈希值，用于定位具体的链表
    int h = MyHashMap::hash(key);
    // 对具体的链表进行遍历。检查 value 是否存在于这个链表中
    for(auto&& it = this->lists[h].begin(); it != this->lists[h].end(); ++it)
    {
        if((*it).first == key)
        {
            // 已经添加过了，不能重复添加，我们只能把这个值修改成新的 value
            (*it).second = value;
            return;
        }
    }
    // 没有添加过，我们可以进行添加
    // 这次添加的是一个数值对，用 emplace_back 比 push_back 更快更简洁
    this->lists[h].emplace_back(key, value);
}

// 用键获取元素值，我们同样需要线性遍历对应对链表来确认是否存在对应的键值
int Leetcode701_800::Soltuion::MyHashMap::get(int key)
{
    int h = MyHashMap::hash(key);
    for(auto&& it = this->lists[h].begin(); it != this->lists[h].end(); ++it)
    {
        // 如果 key 存在于对应的链表中，就返回值
        if((*it).first == key)
        {
            return (*it).second;
        }
    }
    // 不存在，返回 -1
    return -1;
}

void Leetcode701_800::Soltuion::MyHashMap::remove(int key)
{
    int h = MyHashMap::hash(key);
    for(auto&& it = this->lists[h].begin(); it != this->lists[h].end(); ++it)
    {
        if((*it).first == key)
        {
            this->lists[h].erase(it);
            return;
        }
    }
}