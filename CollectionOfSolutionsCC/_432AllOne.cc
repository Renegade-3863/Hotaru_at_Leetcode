#include "Solution.h"

Leetcode401_500::Solution::AllOne::AllOne()
{
    head = new Bucket("", 0);
    tail = new Bucket("", INT_MAX);
    head->next = tail;
    tail->last = head;
}

void Leetcode401_500::Solution::AllOne::insert(Bucket* cur, Bucket* pos)
{
    cur->next->last = pos;
    pos->next = cur->next;
    cur->next = pos;
    pos->last = cur;    
}

void Leetcode401_500::Solution::AllOne::remove(Bucket* cur)
{
    cur->last->next = cur->next;
    cur->next->last = cur->last;
}

// 用于增加一次计数的函数
void Leetcode401_500::Solution::AllOne::inc(string key)
{
    if(map.find(key) == map.end())
    {
        // key 不在 map 中，插入 key 到 cnt 为 1 的桶中
        if(head->next->cnt == 1)
        {
            // 这个 cnt 为 1 的桶已经存在了，我们直接添加即可
            map[key] = head->next;
            head->next->set.insert(key);
        }
        else
        {
            // 否则，我们还没有这个 cnt 为 1 的桶，需要先构造一个记录所有 cnt 为 1 的字符串的桶结点
            Bucket* newBucket = new Bucket(key, 1);
            // 记录 key 属于这个桶结点
            map[key] = newBucket;
            // 把这个新结点(因为是次数为1的桶)添加到 head 这个哨兵结点后面，因为它一定是出现次数最少的那一个桶
            insert(head, newBucket);
        }
    }
    else
    {
        // key 已经存在于 map 中，那么我们找出对应的桶，增加其出现计数即可
        Bucket* bucket = map[key];
        // 如果当前桶的下一个桶恰好是相邻的次数桶，那么我们不用新建对应的桶，进行插入即可
        if(bucket->next->cnt == bucket->cnt + 1)
        {
            map[key] = bucket->next;
             bucket->next->set.insert(key);
        }
        else
        {
            // 否则，我们需要新建 bucket->cnt+1 次数多桶再进行插入
            Bucket* newBucket = new Bucket(key, bucket->cnt + 1);
            map[key] = newBucket;
            insert(bucket, newBucket);
        }
        // 把 key 从当前桶中删除
        bucket->set.erase(key);
        // 如果原来所在的桶删掉 key 后空了，我们需要把这个桶也给删除掉
        if(bucket->set.empty())
        {
            remove(bucket);
            delete bucket;
        }
    }
}

void Leetcode401_500::Solution::AllOne::dec(string key)
{   
    Bucket* bucket = map[key];
    // 如果这个 key 在出现次数为 1 的桶中，那么我们还需要把这个 key 从记录表中删除，因为它已经不存在了
    if(bucket->cnt == 1)
    {
        map.erase(key);
    }
    else
    {
        // 如果出现次数少1的桶是存在的，那么我们不需要构造新桶，只需要执行删除和插入
        if(bucket->last->cnt == bucket->cnt - 1)
        {
            map[key] = bucket->last;
            bucket->last->set.insert(key);
        }
        else
        {
            // 否则，我们需要新建一个出现次数少1的桶
            Bucket* newBucket = new Bucket(key, bucket->cnt-1);
            // 之后修改引用和进行插入操作
            map[key] = newBucket;
            insert(bucket->last, newBucket);
        }
    }
    bucket->set.erase(key);
    if(bucket->set.empty())
    {
        remove(bucket);
        delete bucket;
    }
}

string Leetcode401_500::Solution::AllOne::getMaxKey()
{
    return tail->last == head ? "" : *tail->last->set.begin();
}

string Leetcode401_500::Solution::AllOne::getMinKey()
{
    return head->next == tail ? "" : *head->next->set.begin();
}