#include "Solution.h"

vector<string> Leetcode401_500::Soltuion::findWords(vector<string>& words)
{
    // 简单题，简单做
    // 模拟题，我们记录美式键盘中的键位，按行记录
    unordered_map<char, int> mapping {{'Q', 0}, {'W', 0}, {'E', 0}, {'R', 0}, {'T', 0}, {'Y', 0}, {'U', 0}, {'I', 0}, {'O', 0}, {'P', 0}, 
                                      {'A', 1}, {'S', 1}, {'D', 1}, {'F', 1}, {'G', 1}, {'H', 1}, {'J', 1}, {'K', 1}, {'L', 1}, 
                                      {'Z', 2}, {'X', 2}, {'C', 2}, {'V', 2}, {'B', 2}, {'N', 2}, {'M', 2}};
    // 之后对 words 中的每一个字符串进行遍历检查即可
    // 标记位，记录当前遍历到的单词中的元素应该全部属于哪一行
    // 初始值随意
    int line = -1;
    // 答案数组
    vector<string> res;
    for(const auto& word: words)
    {
        // 对于每一个 word，我们按照 word[0] 确认这个单词中的字符应该全部属于哪个串
        // 统一当成大写字母对待
        line = mapping[toupper(word[0])];
        int n = word.size(), i = 1;
        for(; i < n; ++i)
        {
            if(mapping[toupper(word[i])] != line)
            {
                break;
            }
        }
        if(i == n)
        {
            res.push_back(word);
        }
    }
    return res;
}  