#include "Solution.h"

int Leetcode401_500::Soltuion::findContentChildren(vector<int>& g, vector<int>& s)
{
    // 简单题简单做，我们对两个数组分别按升序排好，之后用两个指针同步遍历即可
    // 这个思路其实挺明显的，原因这里就不细写了
    sort(g.begin(), g.end()); sort(s.begin(), s.end());
    // 从头开始遍历
    int ptr1 = 0, ptr2 = 0;
    int res = 0, m = g.size(), n = s.size();
    // 任何一个指针到头了都可以结束循环
    while(ptr1 < m && ptr2 < n)
    {
        // 如果当前这块饼干可以满足这个目前要求最低的孩子，我们就把这块目前最小的饼干给他/她
        if(g[ptr1] <= s[ptr2])
        {
            // 同步后移
            ++ptr1; ++ptr2;
            // 记录数值
            ++res;
        }
        // 如果当前这块饼干没法满足这个目前要求最低的孩子，那么它也不可能满足后面任何一个孩子了，我们直接丢弃它即可
        else
        {
            ++ptr2;
        }
    }
    return res;
}