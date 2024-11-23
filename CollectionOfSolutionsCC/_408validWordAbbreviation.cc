#include "Solution.h"

bool Leetcode401_500::Solution::validWordAbbreviation(string word, string abbr)
{
    // 简单的模拟题，我们按要求检查缩写串和原串即可
    int idx1 = 0, idx2 = 0;
    int m = word.size(), n = abbr.size();
    while(idx1 < m && idx2 < n)
    {
        // abbr 有两种可能
        // 1. 就是一个正常字符，那么此时它应该和 word[idx1] 正好相等
        // 2. 是一个数字，那么我们需要先解析出这个数字
        // 之后才能按这个解析出来的数字对 word 进行对应次数的检查
        // 情况1.
        if(!isdigit(abbr[idx2]))
        {
            // 我们判断 word[idx1] 是否等于 abbr[idx2]
            if(word[idx1] != abbr[idx2])
            {
                // 不想等，说明模拟出错，返回 false 即可
                return false;
            }
            // 否则，我们可以正常后移两个指针
            ++idx1; ++idx2;
        }
        // 情况2.
        else
        {
            // 我们解析 abbr[idx2] 代表的一整串数字
            int num = abbr[idx2]-'0';
            while(isdigit(abbr[++idx2]))
            {
                if(num == 0)
                {
                    return false;
                }
                num = num*10+(abbr[idx2]-'0');
            }
            if(num == 0)
            {
                return false;
            }
            // 解析完成，我们按 num 次对 idx1 指针进行移动
            for(int i = 0; i < num; ++i)
            {
                ++idx1;
            }
        }
    }
    return idx1 == m && idx2 == n;
}