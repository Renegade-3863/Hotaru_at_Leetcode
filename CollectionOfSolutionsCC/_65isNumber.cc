#include "Solution.h"

bool Leetcode1_100::Solution::isNumber(string s)
{
    // 不同的模拟题，同样的恶心人，一步一步按逻辑进行推导即可，没什么特别的，状态机问题都是这样的
    // 这里借用一下三叶大佬的解析方式
    // 面试哪个面试官要是考这玩意，多少是对应聘者有点意见了。。
    int n = s.size();
    // 切入点是以下事实：在整个字符串中，只有指数符号 ('E'/'e') 是要么不出现，出现了就只能出现一次的字符
    // 我们可以使用这个事实来对 s 进行分割
    int idx = -1;
    for(int i = 0; i < n; ++i)
    {
        if(s[i] == 'e' || s[i] == 'E')
        {
            // 如果出现了一次指数符号，记录它的下标
            if(idx == -1) 
            {
                idx = i;
            }
            // 出现了多于一个指数符号，说明一定不是合法的有效数字，返回 false 即可
            else
            {
                return false;
            }
        }
    }
    // 记录是否是一个有效数字
    bool res = true;
    /* 检查函数 check */
    /*
        start：要检查的子串起始位置
        end：要检查的子串结束位置
        mustInteger：这个数字是否必须是一个整数
    */
    function<bool(int, int, bool)> check = [&](int start, int end, bool mustInteger)
    {
        if(start > end) 
        {
            return false;
        }
        // 如果要检查的部分以符号开头，直接跳过这个符号即可
        if(s[start] == '+' || s[start] == '-')
        {
            ++start;
        }
        bool hasDot = false, hasNum = false;
        // 对抛掉可能的开头第一个符号后的子串进行遍历检查
        for(int i = start; i <= end; ++i)
        {
            if(s[i] == '.')
            {
                // 如果这个子串必须是一个整数，或者这个子串前面已经出现过小数点了，就可以肯定这不是一个合法的有效数字子串了
                if(mustInteger || hasDot) 
                {
                    return false;
                }
                // 标记这个小数点
                hasDot = true;
            }
            else if(s[i] >= '0' && s[i] <= '9')
            {
                hasNum = true;
            }
            else
            {
                return false;
            }
        }
        // 如果找到了至少一个数字，并且这个数字中小数点和符号的位置是正确的，就可以返回 true，注意，只有符号没有数字显然也是不行的
        return hasNum;
    };
    // 如果有指数符号分割，就按分割后两侧是否有效来进行检查
    if(idx != -1)
    {
        res &= check(0, idx-1, false);
        // 指数的次方部分必须是一个整数
        res &= check(idx+1, n-1, true);
    }
    // 否则，只需要对整体进行一遍检查
    else
    {
        res &= check(0, n-1, false);
    }
    return res;
}