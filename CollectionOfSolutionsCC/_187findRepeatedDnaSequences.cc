#include "Solution.h"

vector<string> Leetcode101_200::Solution::findRepeatedDnaSequences(string s)
{
    // 很简单的滚动哈希类问题，题目固定了需要检查的子串长度为 10，因而我们只需要滚动一轮即可
    const unsigned long long exp = 13131;
    unsigned long long exponent = 1;
    unordered_map<long long, int> memo;
    // 使用最简单的长整形溢出来简单应对哈希冲突
    unsigned long long hash = 0;
    int n = s.size();
    vector<string> res;
    // 先计算第一个长度为10的子串的哈希值
    for(int i = 0; i < 10; ++i)
    {
        hash = hash * exp + (unsigned long long)(s[i]);
        exponent *= exp;
    }
    // 记录这个哈希值到哈希表中
    ++memo[hash];
    for(int i = 10; i < n; ++i)
    {
        hash = hash * exp - (unsigned long long)(s[i-10]) * exponent + (unsigned long long)(s[i]);
        // 如果这个哈希值(对应的是一个特定字符串 理想情况下)
        // 我们使用哈希表而不是哈希集合的原因在于，本题要求我们只添加一次重复出现了的子字符串，因而我们通过记录某个子字符串出现的次数来判断之前是否曾经添加过这个子字符串
        if(memo.find(hash) != memo.end() && memo[hash] < 2)
        {
            // 我们把这个子字符串添加到结果字符串数组中
            res.push_back(s.substr(i-9, 10));
            ++memo[hash];
        }
        else
        {
            ++memo[hash];
        }
    }
    return res;
}