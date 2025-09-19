#include <iostream>

class Solution
{
public:
    int strStr(string haystack, string needle)
    {
        // 经典 KMP 算法，本质上也是一种动态规划
        int n = needle.size();
        // 初始化一个前缀数组，用于记录当 needle 中每一个下标上的字符不匹配时，应该把指针挪回到哪里继续尝试进行匹配
        vector<int> next(n, 0);
        int j = 0, k = -1;
        next[0] = -1;   // 如果第一个字符就没法匹配，我们规定让匹配串的指针往后移动一个位置
        // 尝试对 next 数组进行处理
        while(j < n)
        {
            // 对于当前的 j 与 k，无非两种可能的关系
            // 1. k == -1 或者 needle[j] == needle[k]
            // 此时要么是后缀无法和任意长度的字符串匹配，要么当前的 j 和 k 是可以匹配的
            // 这两种情况下，我们都可以认为，如果 haystack[i] != needle[j+1]，那么我们可以在匹配时把 j 指针前移到 k+1 位置进行匹配
            if(k == -1 || needle[j] == needle[k])
            {
                ++j;
                // 各自后移一位
                ++k;
                if(j < n)
                {
                    next[j] = k;
                }
            }
            // 2. 否则，needle[k] 与 needle[j] 无法匹配，这不是一组合法的前后缀，所以我们需要回弹 k 的值
            else
            {
                k = next[k];
            }
        }
        // next 数组处理完成，我们接下来可以使用它求解最终的问题
        int m = haystack.size(), i = 0;
        j = 0;
        // 遍历 haystack 字符串，尝试进行匹配
        while(i < m)
        {
            // 如果当前的 i 和 j 匹配成功，那么我们可以同步后移 i 和 j 指针，尝试进行下一个字符的匹配
            if(j == -1 || haystack[i] == needle[j])
            {
                ++i;
                ++j;
                if(j == n)
                {
                    // 此时说明我们已经匹配到了最终结果妈妈，返回下标即可
                    return i-n;
                }
            }
            // 否则，我们无法匹配当前两元素，需要把 j 回卷
            else
            {
                j = next[j];
            }
        }
        // 执行到这里，说明我们没有找到匹配的子串，返回 -1
        return -1;
    }
};