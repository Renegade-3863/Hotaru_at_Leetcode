#include "Solution.h"

bool Leetcode201_300::Solution::isIsomorphic(string s, string t)
{
    // 类似密码的一一映射，需要保证每个原象对应的映射象是唯一的，我们只需要根据这一要求进行一轮遍历即可
    unordered_map<char, char> mapping;
    unordered_map<char, char> remapping;
    // 如果长度不一样，那么我们就不用检查了，之间返回 false 即可
    if(s.size() != t.size())
    {
        return false;
    }
    // 否则，我们就按位遍历一轮
    int n = s.size();
    for(int i = 0; i < n; ++i)
    {
        // 1. 同一字符映射到了不同的字符上，不合法
        if(mapping.find(s[i]) != mapping.end() && mapping[s[i]] != t[i])
        {
            return false;
        }
        // 2. 不同字符映射到了同一字符上，不合法
        else if(remapping.find(t[i]) != remapping.end() && remapping[t[i]] != s[i])
        {
            return false;
        }
        else
        {
            mapping[s[i]] = t[i];
            remapping[t[i]] = s[i];
        }
    }
    return true;
}