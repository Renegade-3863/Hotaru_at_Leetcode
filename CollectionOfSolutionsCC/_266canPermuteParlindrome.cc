#include "Solution.h"

bool Leetcode201_300::Solution::canPermuteParlindrome(string s)
{
    // 简单题简单做，本题要求我们检查一个字符串是否有回文排列，那么我们可以通过一个单一变量来简单实现：
    // 记录数组中出现了奇数次的字符的个数
    int cntDiff = 0;
    // 不难看出，cntDiff 最后如果不大于1，那么我们总能找到这样符合条件的排列
    // 不过还是需要一个哈希表结构来判断某个字符之前是否出现过
    unordered_map<char, int> cnts;
    int n = s.size();
    for(int i = 0; i < n; ++i)
    {
        if(cnts[s[i]] % 2 == 0)
        {
            cntDiff++;
        }
        else
        {
            cntDiff--;
        }
        ++cnts[s[i]];
    }
    return cntDiff <= 1;
}