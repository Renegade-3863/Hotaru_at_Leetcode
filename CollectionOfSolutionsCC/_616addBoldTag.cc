#include "Solution.h"

string Leetcode601_700::Soltuion::addBoldTag(string s, vector<string>& words)
{
    // 该说是 KMP 写多了吗。。我第一眼看见这道题的想法居然是暴力 KMP。。
    // 虽然题解中一堆用字典树的
    // 不过个人认为，KMP 要存的东西可能比字典树更多 (KMP 需要针对每一个字符串都计算并保存一个前缀数组，而字典树可以合并多个字符串的前缀进行存储)
    // 用 KMP 的话，思路比较简单
    // 我们写一版可以找出母串中所有子串出现开始下标的 KMP 函数 (针对原版的 KMP 做一点改进即可)
    // 之后把每一个第一次出现下标开始的字符串前后套上 <b>..</b> 
    // 最后再整体做一次题目要求的合并即可
    // 按这个思路先写一次
    // 首先是找前缀的函数，定义为 getNext 函数
    function<void(const string&, vector<int>&)> getNext = [&](const string& t, vector<int>& next) -> void 
    {
        // 首先对 next 进行重新内存分配
        // 因为我们要做的是多个匹配，所以 next 数组的长度需要多一个，记录 "最后匹配成功了，该把 j 挪到哪里继续匹配"
        int n = t.size();
        next.resize(n+1);
        std::fill(next.begin(), next.end(), 0);
        // 之后划定 j 和 k，j 用来对 next 进行赋值
        int j = 0, k = -1;
        // 预赋值，如果第一个字符都没法匹配，那么用 -1 来指示 KMP 函数直接往后同步挪动 i 和 j 指针
        next[0] = -1;
        while(j < n)
        {
            if(k == -1 || t[j] == t[k])
            {
                // 如果 k == -1，或者 next[j] == next[k]，那么说明，当前字符可以匹配，我们可以对 next[j+1] 进行赋值
                ++k; ++j;
                if(j == n)
                {
                    // 如果 j == n，那么此时我们要记录的就是：
                    // 如果在 s 中找到了 t 的一个完全匹配，我们应该把 j 回溯到哪里继续进行匹配
                    // 很明显就是这时的 k
                    next[j] = k;
                }
                else
                {
                   // 进行优化，如果 t[j] == t[k]，那么我们让 j 回到 k，就是依然没法匹配的，所以此时，我们让 j 回到 next[k] 即可
                    if(t[j] == t[k])
                    {
                        next[j] = next[k];
                    }
                    // 否则，我们正常把 k 赋值给 next[j]
                    else
                    { 
                        next[j] = k;
                    }
                }
            }
            else
            {
                // 否则，我们没法让 t[j] 和 t[k] 匹配
                // 那么直接把 k 回溯到 next[k]，继续尝试匹配 next[j]
                k = next[k];
            }
        }
        // 赋值结束，不用返回任何值
    };
    //
    // KMP 函数本体，我们把所有能匹配 t 的 s 的子部分在 mark 中都标记成 true，代表 "能匹配"
    vector<bool> marks(s.size(), false); 
    function<void(const string&, const string&, const vector<int>&)> KMP = [&](const string& s, const string& t, const vector<int>& next) -> void
    {
        int i = 0, j = 0;
        int m = s.size(), n = t.size();
        // 对 i 进行遍历，直到检查完整个字符串
        while(i < m)
        {
            if(j == -1 || s[i] == t[j])
            {
                // 匹配，或者完全没法匹配，这两种情况，都要同步后移两个指针
                ++i; ++j;
                // 如果移动后，j == n 成立，说明我们已经完成了 t 的一次匹配，把 i-n (找到的合法起点坐标) 记录到 res 中即可
                if(j == n)
                {
                    std::fill(marks.begin()+i-n, marks.begin()+i, true);
                    // cout << t << " meet at " << i-n << " i-1: " << i-1 << endl;
                    // 同时，因为我们要找所有的匹配点，所以这里不能 break，而是要把 j 重置回 next[j] (也就是 next[n])
                    j = next[j];
                }
            }
            // 否则，不是完全没法匹配，也不能匹配，那么我们要回溯 j，继续尝试和 next[i] 进行匹配
            else
            {
                j = next[j];
            }
        }
        // 检出完成，直接结束函数即可
    };
    // 用一个 next 数组，对所有子字符串，复用它即可
    vector<int> next;
    for(const auto& word : words)
    {
        // 对于每一个 word，先 getNext(word)，然后用 KMP 把 它在 s 中出现的所有下标保存到 indices[word] 中
        getNext(word, next);
        // KMP
        KMP(s, word, next); 
    }
    // 检查完成，根据 marks 中保存的信息，我们自己构造一个 string 返回即可
    int m = s.size();
    string res;
    if(marks[0] == true)
    {
        // 开头添加一个左标签
        res += "<b>";
    }
    res.push_back(s[0]);
    // 遍历中间部分
    for(int i = 1; i < m; ++i)
    {
        if(marks[i] == true && marks[i-1] == false)
        {
            // 添加一个左标签
            res += "<b>";
        }
        else if(marks[i] == false && marks[i-1] == true)
        {
            // 添加一个右标签
            res += "</b>";
        }
        res.push_back(s[i]);
    }
    if(marks[m-1] == true)
    {
        res += "</b>";
    }
    return res;
}