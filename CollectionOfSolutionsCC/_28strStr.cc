#include "Solution.h"

int Leetcode1_100::Solution::strStr(string haystack, string needle)
{
    // 经典的 KMP 模版题，而且本题数据量在 10^4，故可以认为传统的暴力匹配方法已经行不通了
    // 我们可以直接上 KMP(个人认为本质是类似动态规划的递推方法)
    // KMP 需要对匹配串进行预处理，找出前缀数组 next，之后利用这个预处理的信息和进行匹配串和原串的匹配
    /**
     * @param next 待计算的前缀数组
     * @param needle 匹配串，用于计算前缀数组
     */
    function<void(vector<int>&, const string&)> findNext = [&](vector<int>& next, const string& needle)
    {
        // 明确一点：如果原串的某一个字符甚至无法和匹配串的第一个字符匹配，那么显然无法回溯重匹，我们把这一位前缀设定为 -1 (不存在真前缀)
        next[0] = -1;
        // 进行循环填写
        // 保证一个循环不变式：每一次填写下标为 j 处的前缀数组值时，k 代表的都是这个下标如果无法匹配，需要回溯到的上一个匹配串内下标值
        int j = 0, k = -1, n = needle.size();
        while(j < n)
        {
            // 如果当前下标 j 处的字符和 k 处的字符相等，那么说明我们可以计算下一个 j 位置处的前缀数组值了
            // k == -1 意味着现在长度为 j+1 的子串没有真前缀，如果 j+1 下标处的元素没法匹配，我们只能从头开始匹配
            // 从处理逻辑上来说，和字符相等的情况是一样的
            if(k == -1 || needle[j] == needle[k])
            {
                // 准备更新 j+1 处的信息
                ++j; ++k;
                if(j < n)
                {
                    // 加上这一步的原因在于，如果我们指定如果 j 下标处的元素无法匹配，要从 k 处重新尝试匹配，而 needle[j] 和 needle[k]
                    // 却是相等的，那么显然我们没必要再进行这一步尝试，而是应该继续回溯到上一个字符
                    if(needle[j] == needle[k])
                    {
                        next[j] = next[k];
                    }
                    else
                    {
                        next[j] = k;
                    }
                }
                // 这里的 else 是用于多次匹配找出 needle 的所有起始下标的
                // 只匹配一次的话，这一位用不到
                else
                {
                    next[j] = k;
                }
            }
            // 逻辑运算：k != -1 && needle[j] != needle[k]
            // 这意味着当前这种 (k, j) 对无法推出 j+1 位置处应该填入的前缀长度，应该进一步回溯 k 值
            else
            {
                k = next[k];
            }
        }
        // 全部结束后，我们就完成了对前缀数组的内容填入
    };
    int n = needle.size();
    // 可以执行 KMP 的主体程序了
    vector<int> next(n+1, 0);
    // 计算 next 数组
    findNext(next, needle);
    int i = 0, j = 0, m = haystack.size();
    while(i < m)
    {
        if(j == -1 || haystack[i] == needle[j])
        {
            ++i; ++j;
            if(j == n)
            {
                return i-j;
            }
        }
        // 没法匹配，回溯 j 到上一个位置继续尝试和 haystack[i] 做匹配
        else
        {
            j = next[j];
        }
    }
    // 如果循环体内部没有返回结果，那么说明 haystack 中不存在 needle，返回-1
    return -1;
}