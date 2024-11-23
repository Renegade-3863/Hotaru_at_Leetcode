#include "Solution.h"

int Leetcode401_500::Solution::longestPalindrome(string s)
{
    // 构成的最长回文串有一个特性：
    // 如果可以的话，一定是一堆偶数个的字符加上一个出现奇数次的字符
    // 否则，就是一堆偶数次的字符，没有奇数次的字符
    // 我们只需要遍历一遍整个字符串，就知道最后的结果了
    // 记录那个唯一的奇数次字符是否已经出现过了
    bool found = false;
    // 第一步：检索出每种字符出现的总次数
    // 记录到一个哈希表结构中
    unordered_map<char, int> cnts;
    for(const char& c : s)
    {
        ++cnts[c];
    }
    // 之后，再遍历一遍这个出现次数表，根据每种字符出现的总次数计算出最后可以构成的最长长度
    int res = 0;
    for(const auto& cnt : cnts)
    {
        if(cnt.second % 2 == 0)
        {
            res += cnt.second;
        }
        else
        {
            if(!found)
            {
                res += cnt.second;
                found = true;
            }
            else
            {
                res += cnt.second-1;
            }
        }
    }
    return res;
}