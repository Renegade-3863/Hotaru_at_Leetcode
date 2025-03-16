#include "Solution.h"

// 我们要的是按照出现频率，大的在前面，也就是队尾
// 所以这里把出现频率更大的元素排到前面去即可
struct cmp
{
    bool operator()(const pair<string, int>& a, const pair<string, int>& b)
    {
        return a.second > b.second ? true : a.first < b.first;
    }
};
vector<string> Leetcode601_700::Soltuion::topKFrequent(vector<string>& words, int k)
{
    // 经典的优先队列问题
    // 我们可以用优先队列存储下面的信息：
    // [str, cnt] -> str 出现了 cnt 次
    // 之后对这个优先队列应用下面的排序逻辑：
    // 如果 cnt1 > cnt2，那么优先把 str1 排到 str2 前面
    // 而如果 cnt1 == cnt2，那么优先把字典序小的那一个排到前面
    // 按这样的方式，我们先用一个哈希表处理完所有 word 对应的上述信息对
    // 之后用一个优先队列将它们排好序即可
    // 当然，如果你想自己手搓一个优先队列，那我觉得也完全没问题
    // 这里就偷个懒，用 C++ 自带的 priority_queue 来完成任务了
    unordered_map<string, int> cnts;
    for(const auto& word : words)
    {
        // 记录每种单词出现的次数
        ++cnts[word];
    }
    // 之后考虑用一个自定义排序规则的优先队列来承接 cnts 中的信息
    // 这里用仿函数的格式来重载 pq 的比较规则
    priority_queue<pair<string, int>, vector<pair<string, int>>, cmp> pq;
    for(const auto& cnt : cnts)
    {
        pq.push(cnt);
        // 队内超过了 k 个元素，那么我们弹出优先级最低的那个元素即可
        if(pq.size() > k)
        {
            pq.pop();
        }
    }
    vector<string> res;
    while(!pq.empty())
    {
        res.push_back(pq.top().first);
        pq.pop();
    }
    reverse(res.begin(), res.end());
    return res;
}