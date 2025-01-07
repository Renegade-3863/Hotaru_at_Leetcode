#include "Solution.h"

string Leetcode401_500::Soltuion::licenseKeyFormatting(string s, int k)
{
    // 题目只允许第一组字符串的长度包含不到 k 个字符，所以我们可以反向遍历 s，来重构整个 s
    string res;
    int i = s.size()-1;
    // 记录右侧最近的结尾/破折号到现在的字符个数，这个值不能超过 k
    int right = 0;
    // 当 i 小于 0 的时候，我们的重构就完成了
    while(i >= 0)
    {
        // 1. 当前字符是一个破折号，我们需要根据右侧已经检出的字符个数，以及左侧是否还有字符，来判定这个破折号是否要保留
        if(s[i] == '-')
        {
            // 如果 right == k，并且左侧还有字符，那么我们需要保留这个破折号，并继续往左进行检查，否则不保留这个破折号
            if(right == k)
            {
                // 重置 right 变量
                right = 0;
                if(i > 0 && s[i-1] != '-')
                {
                    // 修改 res
                    res.insert(0, "-");
                }
                // 修改 i 值
                --i;
            }
            // 如果 right < k，那么我们检查这是不是最后一个子部分，如果不是，那么这个破折号需要丢弃
            else if(right < k)
            {
                // 无论如何，我们都需要丢弃这个破折号，不管右侧的这个部分是不是最后一个子部分
                --i;
            }
        }
        // 2. 当前字符是一个正常字符，那么我们需要计算这个字符如果和右侧的部分结合起来，那么是否会导致子串长度长过 k 
        // 如果会超出 k，那么我们不移动 i，给 res 添加一个破折号做分割点，重置记录右侧子串中字符个数的变量
        else
        {
            // 检查 right 的值
            if(right < k)
            {
                ++right;
                res.insert(0, 1, toupper(s[i]));
                --i;
            }
            else
            {
                // 此时需要添加一个破折号，i 不变，之后把 right 重置
                right = 0;
                res.insert(0, "-");
            }
        }
    }
    // 处理完成，返回结果即可
    return res;
}