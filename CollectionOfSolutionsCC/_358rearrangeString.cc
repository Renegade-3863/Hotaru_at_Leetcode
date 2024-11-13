#include "Solution.h"

string Leetcode301_400::Solution::rearrangeString(string s, int k)
{
    // 如果间距不做任何要求，那么我们直接返回原字符串就行，不用进行任何修改
    if(k == 0) 
    {
        return s;
    }
    // 我们的基本思路很简单，就是贪心地构建最终的结果
    // 一个核心的贪心想法是：
    // 出现次数越多的那种字符，我们越应该把它们往前放
    // 因为只有往前放，我们才更有可能按 k 个为间距把它们排布到最终的答案中
    // 而且每两个同种字符之间的间距保证是 k
    // 这样就是最有可能拿到符合要求的字符串的方法
    // 为了明确一组字符串是否满足了间距为 k，可以放入下一个字符，我们可以用一个队列来模拟填入字符的过程
    // 就是，当我们填入的字符总数达到了 k 个，说明队头的这个字符就可以再填入到答案串中一个(如果它还有剩余的话)
    // 我们保存一组每种字符以及剩余个数的大优先队列
    priority_queue<pair<int, char>> pq;
    unordered_map<char, int> mp;
    queue<pair<int, char>> q;
    string ret;
    for(const char& c : s)
    {
        ++mp[c];
    }
    for(const auto& [c, i] : mp)
    {
        pq.emplace(i, c);
    }
    while(!pq.empty())
    {
        auto& [i, c] = pq.top();
        ret += c;
        q.emplace(i-1, c);
        pq.pop();
        // 如果队列长度达到了 k，说明我们可以再填入一个队头的字符了，如果它的剩余出现次数非零的话
        if(q.size() == k)
        {
            if(q.front().first > 0)
            {
                pq.emplace(q.front().first, q.front().second);
                q.pop();
            }
        }
    }
    // 如果我们提前退出了，说明我们遇到了没法填成间距为 k 的情况，返回空字符串即可
    return ret.size() < s.size() ? "" : ret;
}
