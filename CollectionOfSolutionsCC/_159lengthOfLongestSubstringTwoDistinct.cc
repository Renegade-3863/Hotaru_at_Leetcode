#include "Solution.h"

int Leetcode101_200::Solution::lengthOfLongestSubstringTwoDistinct(string s)
{
    // 本题同样是滑动窗口类方案的经典问题，可以考虑拓展 "两个不同字符" 为 "k 个不同字符"
    // 先给出 "两个不同字符的解法"
    // 依然是规定一个窗口的左右边界 left 和 right
    int n = s.size();
    int left = -1, right = 0;
    int res = 0;
    // 依然是用一个哈希表来记录当前窗口中出现过的字符类型以及次数
    // 配合一个整型变量用来记录当前窗口内不同字符的种类数
    unordered_map<char, int> cnts;
    int diff = 0;
    // 我们需要做的事很简单，就是求出窗口右界在每个可行的 right 值时，最长的可行窗口长度是多少
    while(right < n)
    {
        // 先根据当前 right 的值对哈希集合和 diff 值进行更新
        if(cnts.find(s[right]) == cnts.end())
        {
            // 如果这字符在之前的窗口中没有出现过，那么就更新 diff
            ++diff;
        }
        // 在哈希表中记录一次该字符的出现
        ++cnts[s[right]];
        // 如果当前窗口内出现的字符种类数超过了两种，那么就必须右移左界指针来尝试减少窗口内的字符种类数
        while(diff > 2)
        {
            if(--cnts[s[++left]] == 0)
            {
                // 别忘了先清理掉哈希表中对应的记录项
                cnts.erase(s[left]);
                --diff;
            }
        }
        // 每次上面的内部循环结束，我们都会得到一个以此时的 right 结尾的最长可行的子串，根据它的长度更新最大结果即可
        res = max(res, right-left);
        // 别忘了我们用的是外层的 while 循环，所以需要手动更新 right 值
        ++right;
    }
    return res;
}

// 备注，不难发现，上面的代码可以非常容易地拓展到 "k 个不同字符" 的情况下，我们甚至只需要修改 diff > 2 这一个条件即可 -> diff > k