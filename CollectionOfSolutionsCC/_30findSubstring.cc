#include "Solution.h"

vector<int> Leetcode1_100::Solution::findSubstring(string s, vector<string> &words)
{
    // 本题要求的是给定一组相同长度的字符串词典，检查给定字符串 s 中是否存在词典中所有词以某种形式排列而成的长串
    // 如果使用 KMP，那么我们的 intuitive 是计算出 words 中单词所有可能的排列结果，之后利用 KMP 检查这些字符串是否在 s 中出现过
    // 不过这种方案的复杂度非常高，达到了 O(n!) 级别，而且求所有排列的方法同样设计难度较大
    // 注意到本题，所有 word 的组合串长度一定是固定的，因而本题可以使用更方便的字符串哈希+滚动数组策略
    // 为了便于检查单词的存在与否，我们可以把 words 数组中的单词转存到一个哈希表中，并记录一个差距值 diff
    // 初始的 diff 记录的是 words 数组中存在多少种单词(以防搞出 words 中存在重复单词的情况，这里我们用种类数来描述)
    // 之后，滑动一个长度等于 words 中所有单词长度和的窗口，每次滑动变动一个单词的距离
    // 动态维护 diff 的值，如果 diff 的值变为了0，那么就记录相应的起始下标
    int diff = 0;
    int n = words[0].size(), m = words.size(), len = s.size();
    unordered_map<string, int> rec;
    // 答案数组
    vector<int> res;
    for (int i = 0; i < m; ++i)
    {
        // 如果遇到一种新的单词，就递增 diff 值
        if (rec.find(words[i]) == rec.end())
        {
            ++diff;
        }
        // 增加相应单词的 count
        ++rec[words[i]];
    }
    // 现在 diff 记录了要匹配出相应字符串需要的单词种数
    // 可以从头开始初始化窗口了
    // 枚举所有可能的窗口开始位置
    // 最开始的想法可能是，所有向后延伸，能扩展出一个长度为 m*n 的字符串的位置都可以，但是鉴于我们的窗口滑动机制，其实有些位置的窗口我们之前已经检查过了
    // 举个例子：hel old how are you 这五个单词
    //         以及 helyouarehowold 这个字符串，其实我们会发现，对于起始点在一个单词长度位置开始的所有初始窗口，它们其实都是某个前面的初始窗口转移过来的，因而也就已经被检查过了
    // 所以我们只需要检查以一个单词长度以内的所有下标位置开始的窗口就可以了
    for (int i = 0; i < n && i + m * n <= len; ++i)
    {
        // 由于我们会对哈希表中的信息进行修改，故有必要拷贝一个哈希表的副本
        unordered_map<string, int> tmp = rec;
        // diff 原数据不动，这里用副本进行计算
        int diffCopy = diff;
        // 先进行窗口的初始化，再进行滑动
        // 每次检查一个长度为 n 的字符串，检查这个字符串是否在 rec 中出现过
        // 一共检查 m 个字符串
        for (int j = 0; j < m; ++j)
        {
            string cur = s.substr(i + j * n, n);
            // 对于每一个提取出来的字符串，检查其是否在复制过来的哈希表记录过，如果记录过，就要更新对应的记录，并根据更新后的结果
            // 相应地更新 diff 值
            if (tmp.find(cur) != tmp.end())
            {
                // 如果减少过之后对应单词的区别值清零了，就可以减少一次总体的区别值
                if (--tmp[cur] == 0)
                {
                    --diffCopy;
                }
                // 而如果对应单词的区别值变为了负数
                // 就说明这种单词多出现了几次，diff 值也应该相应增加1
                if (tmp[cur] == -1)
                {
                    ++diffCopy;
                }
            }
        }
        // cout << endl;
        // 检查完 m 个字符串后，判断 diff 是不是 0，如果是 0，那么就说明找到了一个合法的初始下标，可以把这个下标记录到答案中
        if (diffCopy == 0)
        {
            res.push_back(i);
        }
        // 之后进行步长为 n 的窗口滚动，动态地进行判断即可
        for (int j = i + n; j < len && j + m * n <= len; j += n)
        {
            // 取最后一个字符串和刚刚被丢弃的第一个字符串
            string cur = s.substr(j + (m - 1) * n, n);
            string pre = s.substr(j - n, n);
            // 针对丢弃的单词进行处理
            if (tmp.find(pre) != tmp.end())
            {
                // 给丢弃的那个字符串的区别值增加1
                // 如果修改后的单词区别值等于0了，就可以减少整体的区别值
                if (++tmp[pre] == 0)
                {
                    --diffCopy;
                }
                // 如果修改后的区别值大于0了，就需要增加整体的区别值
                if (tmp[pre] == 1)
                {
                    ++diffCopy;
                }
            }
            // 针对新加入的单词进行处理
            if (tmp.find(cur) != tmp.end())
            {
                // 给新加入的那个字符串的区别值减1
                // 如果修改后的单词区别值等于0了，就可以减少整体的区别值
                if (--tmp[cur] == 0)
                {
                    --diffCopy;
                }
                // 如果修改后的区别值小于0了，就需要增加整体的区别值
                if (tmp[cur] == -1)
                {
                    ++diffCopy;
                }
            }
            // 判断 diff 是否等于0，如果是，说明这个起始下标是可行的，添加到答案中即可
            if (diffCopy == 0)
            {
                res.push_back(j);
            }
        }
    }
    // 全部检查完毕后，就可以返回结果了
    return res;
}