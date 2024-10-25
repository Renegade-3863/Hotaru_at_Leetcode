#include "Solution.h"

int Leetcode201_300::Solution::hIndex(vector<int>& citations)
{
    // 本质是一道计数排序类问题，但是感觉如果单纯用计数排序来解决，可能会导致一些空间上的浪费
    // 如果一个科学家，它的所有论文的引用次数都很多
    // 那么很明显我们会浪费大量的空间存储一些不必要的数据
    int h = 0;
    // 先找出来所有论文被引用次数的上界和下界
    int maximum = *max_element(citations.begin(), citations.end()), minimum = *min_element(citations.begin(), citations.end());
    // 用一个一维数组记录所有引用次数为某个值的论文出现的次数
    vector<int> memo(maximum+1, 0);
    int n = citations.size();
    for(int i = 0; i < n; ++i)
    {
        ++memo[citations[i]];
    }
    // 类似计数排序，进行从低到高的累加
    for(int i = memo.size()-2; i >= 0; --i)
    {
        memo[i] += memo[i+1];
    }
    // 从大到小再找第一个满足 memo[i] >= i+minimum 的值
    for(int i = memo.size()-1; i >= 0; --i)
    {
        if(memo[i] >= i)
        {
            return i;
        }
    }
    // 不存在 h 值，返回0即可
    return 0;
}

// 优化策略：根据题解提供的属性进行空间优化
int hIndex(vector<int>& citations)
{
    // 本质是一道计数排序类问题，但是感觉如果单纯用计数排序来解决，可能会导致一些空间上的浪费
    // 如果一个科学家，它的所有论文的引用次数都很多
    // 那么很明显我们会浪费大量的空间存储一些不必要的数据
    int h = 0;
    // 题解给出了一种很巧妙的空间优化策略
    // 因为 h 指数的定义包含：科学家至少发表了 h 篇论文
    // 那么 h 最大就是不可能超过 citations 的长度的
    // 所以我们可以进行限制：所有论文引用次数超过了 citations 长度次的，都归一到 citations.size() 次
    int n = citations.size();
    vector<int> memo(n+1, 0);
    for(int i = 0; i < n; ++i)
    {
        ++memo[citations[i] >= n ? n : citations[i]];
    }
    // 类似计数排序，进行从低到高的累加
    for(int i = n-1; i >= 0; --i)
    {
        memo[i] += memo[i+1];
    }
    // 从大到小再找第一个满足 memo[i] >= i+minimum 的值
    for(int i = n; i >= 0; --i)
    {
        if(memo[i] >= i)
        {
            return i;
        }
    }
    // 不存在 h 值，返回0即可
    return 0;
}