#include "Solution.h"

Leetcode701_800::Soltuion::Soltuion::Soltuion(int n, vector<int>& blackList)
{
    // 我们用 [0, n-1] 中不在 blacklist 中的那些元素完成对 this->mapping 的构建
    // 记录最后 mapping 到 [0, n-m] 区间上的下标，其中 m 代表的是 blackList 的长度
    int idx = 0;
    this->n = n;
    this->m = blacklist.size();
    unordered_set<int> check;
    for(const auto& elem : blacklist)
    {  
        // 记录 blackList 中的元素到 check 中
        check.insert(elem);
    }
    // 之后，遍历 [0, n-1]，把不在 check 中的元素进行映射即可
    for(int i = 0; i < n; ++i)
    {
        if(check.count(i) == 0)
        {
            // 注意映射顺序，我们要的是能通过随机到的值求解原结果的函数
            // 也就是，我们随机出来的下标是 idx，它应该对应回一个没出现在 blackList 中的元素 i
            this->mapping[idx] = i;
            ++idx;
        }
    }
    // 处理完成，返回即可
}

int Leetcode701_800::Soltuion::Soltuion::pick()
{
    // 我们调用 rand() 函数，生成一个 [0, n-m-1] 之间的元素，之后，把这个元素用 mapping 对应回它原本的值并返回即可
    int idx = rand()%(n-m);
    return this->mapping[idx];
}

// 上面的第一版代码有一个存储空间的问题：由于 n 的值可能会很大，所以我们如果对 n-m 个元素都存储一个映射，很容易爆内存
// 所以我们需要用更好的映射原则：
// 考虑：
// 假设在 [0, n-m) 区间内，在 blacklist 中的元素个数为 x
// 那么在 [n-m, n-1] 区间内，在 blacklist 中的元素个数就是 m-x (m 为 blacklist 中元素的总数)
// 而在 [n-m, n-1] 区间中，在 whitelist 中的元素个数就是 m-(m-x) = x
// 我们会发现，我们恰好可以把 [0, n-m) 区间中的那些黑名单的位置让给在 [n-m, n-1] 区间内的白名单数据
// 至于剩下在 [n-m, n-1] 中的那些元素，我们可以考虑只在 [0, n-m) 中取随机数
// 对于取到的，在 [0, n-m) 中的，并且在 blacklist 中的元素
// 我们可以把他们替换成预先处理的 [n-m, n-1] 中的白名单元素
// 我们做一个一一映射即可
Soltuion(int n, vector<int>& blacklist)
{
    // 处理过程中，我们首先用一个 vector 记录在 [0, n-m) 中出现的黑名单数据
    // 再用一个 vector 记录在 [n-m, n-1] 中出现的白名单数据
    // 之后把数据一一对应存储到 this->mapping 中即可
    vector<int> bMemo;
    vector<int> wMemo;
    unordered_set<int> memo;
    this->m = blacklist.size();
    this->n = n;
    for(const auto& elem : blacklist)
    {
        memo.insert(elem);
    }
    for(int i = n-m; i < n; ++i)
    {
        if(memo.count(i) == 0)
        {
            wMemo.push_back(i);
        }
    }
    for(const auto& elem : blacklist)
    {
        if(elem >= n-m)
        {
            continue;
        }
        bMemo.push_back(elem);
    }
    // 一一对应，存储到 this->mapping 中去
    for(int i = 0; i < bMemo.size(); ++i)
    {
        this->mapping[bMemo[i]] = wMemo[i];
    }
}

int pick()
{
    // 生成一个 [0, n-m) 之间的元素
    int idx = rand()%(n-m);
    if(this->mapping.count(idx))
    {
        // 如果 idx 是黑名单中的数字，那么通过 mapping 把它替换成映射的一个 [n-m, n-1] 中的白名单数据
        return this->mapping[idx];
    }
    // 是一个白名单数据，直接返回即可
    return idx;
}