#include "Solution.h"

bool Leetcode501_600::Soltuion::checkInclusion(string s1, string s2)
{
    int m = s1.size(), n = s2.size();
    // 额外情况处理：如果 s1 长度大于 s2，那么肯定不会有结果，我们直接返回 false 即可
    if(m > n)
    {
        return false;
    }
    // 不管用什么方法，我们都应该先审题+分析
    // 题目要求我们找出的是：是否存在某个 "排列"
    // 这样说的话，我们需要做的就是遍历所有长度等于 s1 的子部分，检查每个子部分中含有的每种字符个数是否等于 s1 中的部分
    // 按模版来进行子串遍历即可
    // 一个 diff 变量，记录 s2 的某个子串是否与 s1 从字符类型与个数上 "全等"，diff == 0 时全等
    int diff = 0;
    // cnts 表记录当前的子串中每种字符出现的个数
    unordered_map<char, int> cnts;
    // 我们先检查 s1 中每一种字符出现的次数，记录到 diff 和 cnts 中
    for(const auto& c : s1)
    {
        // 记录 c 到 cnts 和 diff 中
        if(++cnts[c] == 1)
        {
            // 如果是一种新字符，那么就把 diff 增加 1
            ++diff;
        }
    }
    // 记录完成，我们后续遍历 s2 即可
    // 第一个长度为 m 的子串，检出
    for(int i = 0; i < m; ++i)
    {
        if(--cnts[s2[i]] == 0)
        {
            // 如果把某个字符的个数完全抵消了，那么把 diff 也同步减 1
            --diff;
        }
        // 注意，执行到这里，cnts[s2[i]] 已经被减了 1，不能再用 --cnts[s2[i]] 了
        else if(cnts[s2[i]] == -1)
        {
            ++diff;
        }
    }
    // 检出完成，我们观察 diff 是否为 0
    if(diff == 0)
    {
        return true;
    }
    // 之后，滚动这个长度为 m 的窗口
    for(int i = m; i < n; ++i)
    {
        // 更新头尾两个字符
        if(--cnts[s2[i]] == 0)
        {
            --diff;
        }
        else if(cnts[s2[i]] == -1)
        {
            ++diff;
        }
        if(++cnts[s2[i-m]] == 1)
        {
            ++diff;
        }
        else if(cnts[s2[i-m]] == 0)
        {
            --diff;
        }
        // 更新过一轮后，如果发现 diff == 0 了，那么直接返回 true 即可
        if(diff == 0)
        {
            return true;
        }
    }
    // 没有找到合法的，返回 false 即可
    return false;
}