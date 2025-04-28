#include "Solution.h"

int Leetcode701_800::Soltuion::monotoneIncreasingDigits(int n)
{
    // 本质上的逻辑还是类似状态机
    // 我们考虑从高到低处理 n 的每一位
    // 这样我们就需要先把 n 转换为字符串
    string str = to_string(n);
    // 之后，简单总结一下逻辑链
    // 从最高位开始：
    // 1. 如果 i == str.size()-1，那么我们已经判断到结尾了，整个数已经处理完成，结束处理即可 
    // 2. 如果 str[i] <= str[i+1]，那么当前数对满足要求，我们可以跳过它，继续处理下标 i+1
    // 3. 如果 str[i] > str[i+1]，那么当前数不满足要求，我们需要将 str[i]减 1，并把后续所有数都变成 9 (这个条件能满足要求的单调递增)
    // 注意：情况3 还没完，如果我们把 str[i] 减了 1，那么 i-1 和 i 之间可能又不满足单调递增关系了
    // 所以，完成了后续值的转换后，我们还需要从 i 开始往前进行转换，把所有逆序的数值对进行类似的处理
    int idx = 0, len = str.size();
    while(idx < len)
    {
        // 情况 1.
        if(idx == len-1)
        {
            break;
        }
        // 情况 2.
        else if(str[idx] <= str[idx+1])
        {
            ++idx;
        }
        // 情况 3.
        // 注意，如果 str[idx] > str[idx+1] 成立，那么 str[idx] 一定是大于 0 的
        // 所以不用判断 str[idx]-1 是否小于 0
        else
        {
            int memo = idx;
            --str[idx++];
            // 后续我们把从 idx+1 到 len-1 的所有 digit 都变成 9 即可
            while(idx < len)
            {
                str[idx++] = '9';
            }
            // 处理完成，结束处理即可
            // 后向处理完成，接着前向处理
            while(memo >= 1)
            {
                // 如果 str[memo-1] > str[memo]，那么我们需要把 str[memo] 转换成 '9'，然后把 str[memo-1] 再减少 1
                if(str[memo-1] > str[memo])
                {
                    str[memo] = '9';
                    str[--memo] -= 1;
                }
                else
                {
                    // 否则，不用继续回溯了，我们退出循环即可
                    break;
                }
            }
            break;
        }
    }
    // 转换回整数返回即可
    return stoi(str);
}