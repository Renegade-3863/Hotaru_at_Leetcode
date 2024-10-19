#include "Solution.h"

vector<vector<string>> Leetcode201_300::Solution::groupStrings(vector<string>& strings)
{
    // 基本可以明确的一点是，如果两个字符串是属于同一移位序列的，那么它们肯定是相同长度的
    // 因而我们可以先对 strings 数组进行拆分，长度相同的字符串分成一组
    // 之后我们就可以在每一个长度区间上分别进行处理，这样问题可以被简化
    // 先遍历一轮原数组，获取出长度最长的区间和长度最短的区间
    int minLen = INT_MAX, maxLen = 0, n = strings.size();
    for(int i = 0; i < n; ++i)
    {
        minLen = min((int)strings[i].size(), minLen);
        maxLen = max((int)strings[i].size(), maxLen);
    }
    // 根据两个边界长度分配区间数组
    vector<vector<string>> subSets(maxLen-minLen+1, vector<string>());
    // 再遍历一次，进行实际的分组
    for(int i = 0; i < n; ++i)
    {
        subSets[strings[i].size()-minLen].push_back(strings[i]);
    }
    // 之后我们可以专注于每一种长度唯一的字符串集合
    // 考虑对于一组长度统一的字符串集合，如何根据它们是否是移位字符串来进行进一步细分？
    // 突然想到了一种简单暴力的检查方案
    // 难点其实无非在于：如何量化字符串的属性
    // 其实很简单
    // 本题属于同中移位字符串的每个字符串，相邻字符之间的距离都是一样的
    // 我们可以对这个属性进行量化，存成一个字符串作为哈希表的键，之后按照这个字符串进行哈希映射，最后把哈希表的各个字符串集合再合并成一个最终结果
    unordered_map<string, vector<string>> results;
    // 分组进行遍历
    for(int i = 0; i < subSets.size(); ++i)
    {
        // 对于每个组，我们计算每个字符串的 "差距性质串"，并根据哈希表的键进行记录
        for(int j = 0; j < subSets[i].size(); ++j)
        {
            string mark = "";
            // 按相邻字符串间的差距进行 mark 差距串更新
            for(int k = 1; k < i+minLen; ++k)
            {
                mark += to_string(subSets[i][j][k]>= subSets[i][j][k-1] ? subSets[i][j][k]-subSets[i][j][k-1] : 26+subSets[i][j][k]-subSets[i][j][k-1]);
                // 添加一个下划线，防止两个连续的1和一个11等效的问题
                if(k < i+minLen-1)
                {
                    mark += "_";
                }
            }
            // 记录这个 mark 特征串，如果已经存在过，就添加到对应的集合中
            results[mark].push_back(subSets[i][j]);
        }
    }
    vector<vector<string>> res;
    // 结束后，我们只需要对哈希表进行遍历，取出每个细分的分组即可
    for(auto result: results)
    {
        res.push_back(result.second);
    }
    return res;
}