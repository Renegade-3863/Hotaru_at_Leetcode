#include "Solution.h"

bool Leetcode301_400::Solution::canConstruct(string ransomNote, string magazine)
{
    // 依然是一道可以用差分哈希表解决的简单题
    // 我们用一个哈希表和一个全局的差分值即可解决问题
    // 哈希表记录 ransomNote 中各个字符的剩余未匹配个数
    unordered_map<char, int> diffs;
    // diff 变量记录到达最后的完全匹配还剩下的 "未匹配" 字符种类数
    int diff = 0;
    // 先遍历 ransomNote，预处理 diffs 数组和 diff 变量
    for(const char& c : ransomNote)
    {
        if(diffs.find(c) == diffs.end())
        {
            ++diff;
        }
        ++diffs[c];
    }
    // 之后再遍历 magazine 数组，对结果进行处理
    for(const auto& c : magazine)
    {
        if(diffs.find(c) != diffs.end())
        {
            if(--diffs[c] == 0)
            {
                diffs.erase(c);
                --diff;
            }
        }
    }
    return diff == 0;
}