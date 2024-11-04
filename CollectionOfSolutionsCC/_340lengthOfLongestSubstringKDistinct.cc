#include "Solution.h"

int Leetcode301_400::Solution::lengthOfLongestSubstringKDistinct(string s, int k)
{
    // 滑动窗口的模版题了属于是，字符个数不可能为负，所以可以用窗口算法
    // 我们用一个哈希表记录当前窗口中不同种类的字符出现的个数，以及一个拢共的字符种类数即可
    unordered_map<char, int> exists;
    int cnts = 0;
    // 划定窗口的左右边界，左边界只在需要的时候移动，右边界不断进行循环
    int left = -1, n = s.size();
    int res = 0;
    for(int right = 0; right < n; ++right)
    {
        // for 循环中的每一次，都求出以 right 结尾的、最长的、窗口内只有至多 k 种不同字符的最长连续子串的长度
        // 首先，记录这个 s[right] 字符出现了一次
        // 如果之前窗口里没出现过，就添加一种字符
        if(exists[s[right]] == 0)
        {
            ++cnts;
        }
        // 添加一次出现次数
        ++exists[s[right]];
        // 视需要移动 left 指针
        // 移动的条件是：当前窗口中的字符种类数已经超过了 k 种
        while(cnts > k)
        {
            // 如果我们移除当前 left+1 处的这个字符，使得现在窗口中出现的这种字符次数变为零了，那么我们就可以减少对应的记录
            if(--exists[s[++left]] == 0)
            {
                --cnts;
            }
            // 否则，只减少出现次数，不减少种类数
        }
        // 每次执行到这里，我们都保证了下面的条件：
        // 当前窗口中的字符种类数至多是 k 种
        // 并且我们只在必须移动 left 指针的时候才移动了它
        // 所以这个时候就是以 right 结尾的窗口最长的情况，我们进行更新即可
        res = max(res, right-left);
    }
    // 循环结束，返回结果即可
    return res;
}