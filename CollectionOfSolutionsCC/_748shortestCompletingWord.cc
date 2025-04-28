#include "Solution.h"

string Leetcode701_800::Soltuion::shortestCompletingWord(string licensePlate, vector<string>& words)
{
    // 这道题只要读懂了题目的要求，着实是一道简单题
    // 我们首先需要了解 licensePlate 中包含了哪些元素，这些元素是我们后续检查 words 数组的样板
    // 用一个哈希表记录 plate 中每种字符出现的次数，不分大小写
    unordered_map<char, int> memo;
    for(const auto& p : licensePlate)
    {
        if(!isdigit(p) && p != ' ')
        {
            // 既不是数字字符，也不是空格，那么就一定是一个字母，我们记录它的出现
            // 注意，我们只记录小写字母
            ++memo[tolower(p)];
        }
    }
    // 之后，遍历 words 数组，检出符合题目要求的第一个单词即可
    string res;
    int n = memo.size();
    for(const auto& word : words)
    {
        unordered_map<char, int> tmp = memo;
        int tmpC = n;
        for(const auto& c : word)
        {
            if(--tmp[c] == 0)
            {
                --tmpC;
            }
        }
        if(tmpC == 0)
        {
            if(res.empty() || res.size() > word.size())
            {
                res = word;
            }
        }
    }
    return res;
}