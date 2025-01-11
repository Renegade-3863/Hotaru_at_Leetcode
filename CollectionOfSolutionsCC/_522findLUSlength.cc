#include "Solution.h"

int Leetcode501_600::Soltuion::findLUSlength(vector<string>& strs)
{
    // 基于上一题的结论，我们来求解本题：
    // 容易发现的是，我们实际上只需要检查：某个字符串是否是其它字符串的子序列
    // 如果某个字符串不是其它任何一个字符串的子序列，那么它就能成为一个特殊序列，否则，无论是它本身，还是它的任何一个子序列，都会是这个包含它作为子序列的字符串的子序列
    // 换句话说，它就不可能是特殊序列了
    // 所以基本的遍历逻辑就是 O(n^2) 的枚举，我们枚举每一对字符串，固定第一个字符串 s，枚举第二个字符串 t
    // 判断是否存在：s 是 t 的子序列，或者 t 是 s 的子序列
    // 那么我们就需要考虑实现一个类似双指针判断的算法
    // 我们在下面做一下实现
    function<bool(const string&, const string&)> check = [&](const string& s, const string& t) -> bool
    {
        // 本函数返回值：
        // 如果 s 是 t 的子序列，或者 t 是 s 的 子序列，那么函数返回 false
        // 否则，函数返回 true，表示可以继续检查
        // 我们划定两个指针，分别指向两个字符串的开头，之后通过相应的移动逻辑来进行判断
        int ptrs = 0, ptrt = 0, m = s.size(), n = t.size();
        // 只要有任何一个指针走到了最后，我们就不用继续检查了
        while(ptrs < m && ptrt < n)
        {
            // 匹配了一个字符，那么我们同步移动 ptrs 和 ptrt
            if(s[ptrs] == t[ptrt])
            {
                ++ptrs;
            }
            // 没法匹配，我们只能移动 ptrt
            ++ptrt;
        }
        // 如果是正常退出，就说明这对字符串中某一个是另一个的子序列，而我们要判断的是：s 是否是 t 的子序列，所以如果 t 是 s 的子序列，那么我们依然可以返回 true
        return ptrs != m;
    };
    int n = strs.size();
    // 用一个数组，存储所有可能的结果
    vector<string> res;
    // 我们用两层循环遍历 s 和 t，如果 check(s, t) 为 true，就暂定 s 是合法结果，直到我们结束同一层的遍历
    for(int i = 0; i < n; ++i)
    {
        int j = 0;
        for(; j < n; ++j)
        {
            // 相等的字符串，我们不能比较，上面的调用函数没有针对这种情况做特殊处理
            if(i == j)
            {
                continue;
            }
            // 如果检查后，发现 s 是 t 的子序列，那么我们就直接结束对 s 的检查即可
            if(!check(strs[i], strs[j]))
            {
                break;
            }
        }
        // 根据 j 是否为 n，来判断上面的循环是否是正常退出的，如果是正常退出，就说明我们找到了一个可能为答案的字符串
        if(j == n)
        {
            res.push_back(strs[i]);
        }
    }
    // 没找到合法的结果，返回 -1 即可
    if(res.empty())
    {
        return -1;
    }
    // 因为题目要的是字典序最小的，所以我们需要对 res 进行排序，把字典序最小的那一个返回
    sort(res.begin(), res.end(), [&](const string& a, const string& b) -> bool {
        return a.size() == b.size() ? a < b : a.size() > b.size();
    });
    return res[0].size();
}