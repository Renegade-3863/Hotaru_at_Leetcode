#include "Solution.h"

vector<string> Leetcode101_200::Solution::wordBreak2(string s, vector<string>& wordDict)
{
    // 对于 139 题的常规扩展，前一题要求判断是否能够拆分，本题要求输出所有可行的构造方案
    // 本质上应该是回溯，对单词处理的部分其实和 139 题是完全一样的
    // 我们这里依然用 KMP 来求解
    vector<int> next;
    unordered_map<int, int> pos;
    function<void(const string&)> findNext = [&](const string& word)
    {
        int n = word.size();
        next.resize(n+1);
        int j = 0, k = -1;
        while(j < n)
        {
            if(k == -1 || word[j] == word[k])
            {
                ++k; ++j;
                if(j < n)
                {
                    if(word[j] == word[k])
                    {
                        next[j] = next[k];
                    }
                    else
                    {
                        next[j] = k;
                    }
                }
                else
                {
                    next[j] = k;
                }
            }
            else
            {
                k = next[k];
            }
        }
    };
    function<void(int, const string&)> KMP = [&](int idx, const string& s)
    {
        int m = s.size(), n = wordDict[idx].size();
        string word = wordDict[idx];
        // 先调用 findNext 函数计算 next 前缀数组
        findNext(word);
        // 之后使用 next 数组进行求解
        int i = 0, j = 0;
        while(i < m)
        {
            if(j == -1 || s[i] == word[j])
            {
                ++i; ++j;
                if(j == n)
                {
                    pos[i-n].push_back(idx);
                    j = next[j];
                }
            }
            else
            {
                j = next[j];
            }
        }
    };
    // 调用 KMP 函数
    for(int k = 0; k < wordDict.size(); ++k)
    {
        KMP(k, s);
    }
    // 结束后，可以使用 pos 数组中存储的信息
    // 我们需要通过这个信息进行所有可能解的构造，因而需要利用回溯
    // 用一个 path 字符串记录当前检出的子串
    string path = "";
    // 最后的答案数组
    vector<string> res;
    function<void(int)> backtrack = [&](int idx)
    {
        // 递归结束条件为
        // 我们下一个要尝试添加的下标已经是 s 最大可行下标的下一个位置了，此时说明我们前面已经恰好填满了整个字符串，就得到了一种可行解
        // 可以添加答案并返回了
        // 另一个递归的结束条件：
        // 如果当前要寻找的下标已经超过了我们可以寻找的下标范围，那么就说明找到了一条不合法的添加方式(添多了)
        // 此时不添加 path，直接返回
        if(idx >= s.size())
        {
            if(idx == s.size())
            {
                res.push_back(path);
            }
            return;
        }
        // 否则，我们需要尝试所有可以添加到当前位置的单词，并继续深入递归
        for(int i = 0; i < pos[idx].size(); ++i)
        {
            // 添加单词
            path += wordDict[pos[idx][i]];
            // 如果不是最后一个单词，就添加一个空格
            if(idx+wordDict[pos[idx][i]].size() < s.size())
            {
                path += " ";
            }
            // 递归
            backtrack(idx+wordDict[pos[idx][i]].size());
            // 回溯
            path = path.substr(0, idx);
        }
    };
    backtrack(0);
    return res;
}