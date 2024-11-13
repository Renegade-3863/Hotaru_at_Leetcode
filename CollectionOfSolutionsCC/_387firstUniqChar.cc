#include "Solution.h"

int Leetcode301_400::Solution::firstUniqChar(string s)
{
    // 简单的哈希表模拟题
    // 我们可以记录整个数组中每个字符出现的次数，并维护一个指向只出现一次的字符的下标的指针值作为答案
    // res == -1 代表不存在结果
    int res = -1;
    // cnts 记录每种字符出现的次数
    unordered_map<char, int> cnts;
    // indices 记录每种字符第一次出现的下标
    unordered_map<char, int> indices;
    int n = s.size();
    for(int i = 0; i < n; ++i)
    {
        ++cnts[s[i]];
        if(indices.find(s[i]) == indices.end())
        {
            indices[s[i]] = i;
        }
    }
    // 再遍历一遍哈希表，找出所有出现次数为 1 的字母中第一次出现下标最小的那一个
    for(const auto& cnt : cnts)
    {
        if(cnt.second == 1)
        {
            res = res == -1 ? indices[cnt.first] : min(res, indices[cnt.first]);
        }
    }
    // 返回 res 即可
    return res;
}