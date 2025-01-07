#include "Solution.h"

vector<int> Leetcode401_500::Soltuion::findAnagrams(string s, string p)
{
    // 基本上是一道不难的窗口类题目，不完全是动态的滑动窗口，因为窗口的长度是固定的
    // 首先，如果要是字母异位词，那么整个子字符串的长度一定是需要等于 p 的，所以我们只需检查那些长度等于 p.size() 的子串
    // 剩下的就是字符种类和个数的等价问题了，这个用哈希表不难实现
    // 定义一个哈希表，用于记录 p 中出现的每种字符的个数和当前窗口中的各种字符个数差距 (可以用定长数组实现，这里就用哈希表代替了，作用类似)
    unordered_map<char, int> cnts;
    // diff 变量用于记录当前窗口和 p 字符串中个数仍不一样的字符种类数，diff 为零的时候，代表找到了一个字母异位词
    int diff = 0;
    // 检出 p 的长度 len
    int len = p.size();
    int n = s.size();
    // 遍历 p，更新 diff
    for(const auto& c : p)
    {
        // 如果是第一次记录某种字符，那么需要额外修改 diff
        if(cnts.find(c) == cnts.end())
        {
            ++diff;
        }
        ++cnts[c];
    }
    // 初始化完成，接下来就是按定长子串滚动遍历 s 字符串
    // 首先是第一个窗口
    // 安全检查，如果 n < len，那么我们不用检查了，直接返回空数组即可
    if(n < len)
    {
        return {};
    }
    for(int i = 0; i < len; ++i)
    {
        // 减少 cnts 中对应的字符
        if(--cnts[s[i]] == 0)
        {
            // 差距变为零了，将 diff 减 1
            --diff;
        }
        else if(cnts[s[i]] == -1)
        {
            // 差距变为负了，说明当前窗口对应字符出现次数多了，那么将 diff 加 1
            ++diff;
        }
    }
    vector<int> res;
    // 别忘了最开始的起点也要检查
    if(diff == 0)
    {
        res.push_back(0);
    }
    // 之后是滚动的逻辑
    for(int i = len; i < n; ++i)
    {
        // 首先是滚动步骤
        // 删掉开头的字符
        if(++cnts[s[i-len]] == 0)
        {
            // 删掉后距离被抹平了，diff 减 1
            --diff;
        }
        else if(cnts[s[i-len]] == 1)
        {
            // 删掉后距离重新出现了，diff 加 1
            ++diff;
        }
        // 添加新的字符
        if(--cnts[s[i]] == 0)
        {
            // 添加后距离被抹平了，diff 减 1
            --diff;
        }
        else if(cnts[s[i]] == -1)
        {
            // 添加后距离重新出现了，diff 加 1
            ++diff;
        }
        // 之后判断留下的窗口是否合法
        if(diff == 0)
        {
            // 合法，那么添加对应的起始下标到结果中
            res.push_back(i-len+1);
        }
        // 滚动操作结束，继续下一轮循环即可
    }
    // 操作结束，返回结果
    return res;
}