#include "Solution.h"

bool Leetcode201_300::Solution::wordPattern(string pattern, string s)
{
    // 最简单的方案是利用哈希表，记录 pattern 中的字符和 s 中子单词之间的映射关系
    unordered_map<char, string> mapping;
    unordered_map<string, char> reMapping;
    // 如果找到了同一个字符的新的映射，那么很显然我们的单词规律就是错误的
    int m = pattern.size(), n = s.size();
    int i = 0, j = 0;
    while(i < m && j < n)
    {
        // 取一节字符串出来
        string cur = "";
        while(j < n && s[j] != ' ')
        {
            cur.push_back(s[j++]);
        }
        // 别忘了丢掉空格
        if(j < n && s[j] == ' ')
        {
            ++j;
        }
        // 结束后，我们就取出了当前的下一个子串
        // 再取一个字符出来进行配对
        char curC = pattern[i++];
        // 一对多，不合法，直接返回 false
        if(mapping.find(curC) != mapping.end() && mapping[curC] != cur)
        {
            return false;
        }
        // 多对一，不合法，直接返回 false
        if(reMapping.find(cur) != reMapping.end() && reMapping[cur] != curC)
        {
            return false;
        }
        // 否则，进行映射即可
        mapping[curC] = cur;
        reMapping[cur] = curC;
    }
    // 结束后，还需要检查是否有剩余的未匹配的部分，pattern 和 s 都是
    return i == m && j == n;
}