#include "Solution.h"

// 题解区有用字典树的解法，愿意看的可以去了解一下挑战自己，这里本人就放弃内卷了，反正这题也没有公司面试考过。。。。
vector<vector<int>> Leetcode301_400::Solution::palindromePairs(vector<string>& words)
{
    // 只能想到暴力解法，进阶要求的 O(sum of words[i].length) 的解法恕难从命。。。
    // 对于每个字符串，枚举其它所有字符串，进行双指针回文判定
    vector<vector<int>> res;
    int n = words.size();
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            string word1 = words[i];
            string word2 = words[j];
            // 确保不是选到了同一个字符串
            if(word1 != word2)
            {
                // 先拼接
                // 进行双指针呢判定
                string word = word1+word2;
                int left = 0, right = word.size()-1;
                while(left < right)
                {
                    if(word[left] != word[right])
                    {
                        break;
                    }
                    ++left; --right;
                }
                if(left >= right)
                {
                    res.push_back({i, j});
                }
            }
        }
    }
    return res;
}