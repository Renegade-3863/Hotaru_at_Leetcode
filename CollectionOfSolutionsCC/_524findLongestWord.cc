#include "Solution.h"

string Leetcode501_600::Soltuion::findLongestWord(string s, vector<string>& dictionary)
{
    // 简单的双指针题目
    // 给定了字符串 s，我们要检查 dictionary 中是否存在 s 的最长子序列
    // 我们只需要遍历 dictionary，对于每一对字符串 (s, dictionary[i])，使用双指针检查 dictionary[i] 是否是 s 的子字符串即可
    // 由于 s 是固定的，我们参数就只需要一个字符串
    int m = s.size();
    function<bool(const string&)> check = [&](const string& t) -> bool
    {
        int n = t.size();
        // 定义两个指针，分别指向 s 和 t 的开头
        // 之后应用一些简单的策略即可完成要求
        int ptrs = 0, ptrt = 0;
        // 任何一个指针到头了，都可以直接退出循环
        while(ptrs < m && ptrt < n)
        {
            // 如果 s[ptrs] == t[ptrt]，那么我们可以同步后移两个指针
            if(s[ptrs] == t[ptrt])
            {
                ++ptrt;
            }
            // 否则，我们只能移动 ptrs
            ++ptrs;
        }
        // 退出后，由于我们要检查的是：t 是不是 s 的子序列，所以我们只需要通过 ptrt 和 n 的关系来进行怕奴蛋即可
        // 如果 ptrt 是 n，说明 t 整个字符串可以通过 s 省略其中的一些字符来得到
        return ptrt == n;
    };
    // 用一个数组存储最终所有有效的结果
    vector<string> res;
    for(const string& t : dictionary)
    {
        if(check(t))
        {
            // 可行，我们记录这个字符串
            res.push_back(t);
        }
    }
    // 不存在合法解，返回空字符串即可
    if(res.empty())
    {
        return "";
    }
    // 最后，按长度优先，字典序次之的条件对 res 进行排序
    sort(res.begin(), res.end(), [&](const string& a, const string& b) -> bool {
        return a.size() == b.size() ? a < b : a.size() > b.size();
    });
    // 返回第一个作为答案
    return res[0];
}