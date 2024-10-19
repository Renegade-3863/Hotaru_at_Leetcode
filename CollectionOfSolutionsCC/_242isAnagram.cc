#include "Solution.h"

bool Leetcode201_300::Solution::isAnagram(string s, string t)
{
    // 一道很基本的哈希表运用题
    // 我们用一个哈希表加一个临时存储变量对两个字符串进行遍历即可完成任务
    // 不过在开始之前，我们可以先检查两个字符串的长度是否相同，如果不相同，那么说明两个字符串肯定不会是字母异位词
    int m = s.size(), n = t.size();
    if(m != n)
    {
        return false;
    }
    // 一个哈希表，用于存储每个字符出现的次数
    unordered_map<char, int> cnts;
    // 一个 diff 变量用于记录当前 cnts 哈希表中的项数
    // 如果结束循环后，这个 diff 值是0，那么就代表两个字符串是字母异位词
    int diff = 0;
    for(int i = 0; i < m; ++i)
    {
        // s 对 cnts 提供正向贡献，t 对 cnts 提供反向贡献
        // 累加一次 s[i]，检查是多了一个某种字符，还是恰好完全抵消了某种字符
        if(++cnts[s[i]] == 1)
        {
            ++diff;
        }
        else if(cnts[s[i]] == 0)
        {
            --diff;
        }
        // 累减一次 t[i]，检查是少了一个某种字符，还是恰好完全抵消了某种字符
        if(--cnts[t[i]] == 0)
        {
            --diff;
        }
        else if(cnts[t[i]] == -1)
        {
            ++diff;
        }
    }
    return diff == 0;
}