#include "Solution.h"

bool Leetcode501_600::Soltuion::checkRecord(string s)
{
    // 简单题简单做即可，轻松惬意～
    // valid 代表满足的条件个数，如果 valid >= 2，那么返回 true，否则返回 false
    int valid = 0;
    // rec 哈希表，记录 'A', 'L', 'P' 三种字符出现的个数
    unordered_map<char, int> rec;
    // 记录连续出现的 'L' 记录个数
    int conseq = 0;
    for(const auto& c : s)
    {
        if(c != 'L')
        {
            conseq = 0;
        }
        else if(c == 'L')
        {
            if(++conseq >= 3)
            {
                valid = -1;
            }
        }
        ++rec[c];
    }
    // 如果没有遇到非法情况，那么把 valid 修改为 1，代表第二个条件满足了
    if(valid == 0)
    {
        ++valid;
    }
    // 记录完成后，检查题目要求的 'A' 有关的条件即可
    if(rec['A'] < 2)
    {
        ++valid;
    }
    return valid == 2;
}