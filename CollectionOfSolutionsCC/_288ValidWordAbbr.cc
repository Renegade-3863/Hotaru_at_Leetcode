#include "Solution.h"

Leetcode201_300::Solution::ValidWordAbbr::ValidWordAbbr(vector<string>& dictionary)
{
    // 初始化步骤，我们需要做的是把这个传入的 dictionary 中的数据按 [缩写, 实际单词] 的格式保存到 memo 中
    int n = dictionary.size();
    for(int i = 0; i < n; ++i)
    {
        // 对于每个单词，我们显然需要先计算出其 "缩写"
        int len = dictionary[i].size()-2;
        // 如果这个单词中间部分的长度非零，我们就把这个长度值添加到首尾字符中间
        string key = "";
        // 分情况讨论：
        // 1. 原单词长度是1或2
        // 此时我们的缩写就是单词本身
        if(len <= 0)
        {
            key = dictionary[i];
        }
        // 2. 原单词长度大于2
        // 我们的缩写是首字符+长度转字符串+尾字符
        else
        {
            key.push_back(dictionary[i][0]);
            key += to_string(len);
            key.push_back(dictionary[i][dictionary[i].size()-1]);
        }
        // 拼接完成后，我们尝试把 [key, dictionary[i]] 对添加到哈希表中
        memo[key].insert(dictionary[i]);
    }
}

Leetcode201_300::Solution::ValidWordAbbr::isUnique(string word)
{
    // 要检查这个单词是否是唯一的
    // 我们按要求来就行
    // 1. 计算出这个单词的缩写
    string key = "";
    if(word.size() <= 2)
    {
        key = word;
    }
    else
    {
        key.push_back(word[0]);
        key += to_string((int)word.size()-2);
        key.push_back(word[word.size()-1]);
    }
    // 拿到了缩写，我们只需要在 memo 中查找这个缩写即可
    // 情况1. 不存在这个缩写
    // 情况2. 这个缩写对应的单词只有一个，并且对应的单词就是 word
    if(memo.find(key) == memo.end() || (memo[key].size() == 1 && memo[key].find(word) != memo[key].end()))
    {
        return true;
    }
    return false;
}