#include "Solution.h"

string Leetcode401_500::Soltuion::frequencySort(string s)
{
    // 本题是一道听明显的有序集合应用题，不难，但取决于你需不需要自己实现一个有序集合 (doge)
    // 我们先梳理一下基本的思路：
    // 题目要求的是，对字符串中每一种字符按出现次数多少进行聚集重排
    // 那么最直接的思路是：统计每一种字符出现的次数，记录到一个哈希表中，之后按哈希表中每个字符出现的次数重构答案
    // 不过哈希表本身不是有序的，所以我们实际上需要一个 "按字符出现次数有序的哈希集合"，人话就是：内容为 (字符，次数) 对 的优先队列
    // 思路整理完成，剩下的就是 STL 的使用问题了 (doge)
    // 这种自定义的优先队列需要自己设计比较函数，我们这里用仿函数来实现，具体为 cmp 仿函数类
    struct cmp 
    {
        bool operator() (const pair<char, int>& a, const pair<char, int>& b)
        {
            // 我们需要按次数排序，也就是按 a.second 和 b.second 来进行排序，写出逻辑即可
            // 需要的是大优先队列
            // 题目对出现次数相同的字符没有要求，所以这里不用其它特殊处理
            return a.second < b.second;
        }
    };
    priority_queue<pair<char, int>, vector<pair<char, int>>, cmp> pq;
    // 用一个哈希表记录每种字符出现的总次数，最后再压入优先队列中进行最终排序
    unordered_map<char, int> cnts;
    for(const auto& c : s)
    {
        ++cnts[c];
    }
    // 把每个单词压入优先队列
    for(const auto& cnt : cnts)
    {
        // cnt 本身就是 pair 类型，所以可以直接用
        pq.push(cnt);
    }
    // 最后进行构造即可
    string res;
    while(!pq.empty())
    {
        int cur = pq.top().second;
        for(int i = 0; i < cur; ++i)
        {
            res.push_back(pq.top().first);
        }
        pq.pop();
    }
    return res;
}