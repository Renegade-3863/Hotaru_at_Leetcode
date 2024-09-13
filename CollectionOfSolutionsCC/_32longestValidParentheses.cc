#include "Solution.h"

int Leetcode1_100::Solution::longestValidParentheses(string s)
{
    // 本质是一道很常规的动态规划题，我们可以先从最简单的一维开始考虑
    // 设 dp[i] 代表以 s[i] 结尾的最长有效括号串的长度
    // 考虑是否能够进行递推
    // 如果 s[i] 为 '('，那么显然不存在以一个左括号结尾的任何有效括号串，设置 dp[i] = 0 即可
    // 如果 s[i] 为 ')'，那么我们需要考虑 s[i-1] 是什么
    // 1. s[i-1] 是一个左括号，那么显然有 dp[i] = dp[i-2]+2
    // 2. s[i-1] 是一个右括号，那么应该想到 s[i] 这个右括号需要和前面的一个左括号进行匹配
    // 应该是检查刨除掉以 s[i-1] 这个右括号结尾的最长合法括号串之后的下一个字符是不是左括号，如果是，那么我们显然可以把当前 s[i] 这个右括号
    // 并入左侧的合法括号串，否则说明无法并入
    int n = s.size();
    if(n < 2)
    {
        return 0;
    }
    vector<int> dp(n, 0);
    dp[1] = s[0] == '(' && s[1] == ')' ? 2 : 0;
    int res = dp[1];
    for(int i = 2; i < n; ++i)
    {
        if(s[i] == '(')
        {
            continue;
        }
        if(s[i-1] == '(')
        {
            dp[i] = dp[i-2]+2;
        }
        else
        {
            if(i-dp[i-1]-1 >= 0 && s[i-dp[i-1]-1] == '(')
            {
                dp[i] = dp[i-1]+((i-dp[i-1]-2 >= 0) ? dp[i-dp[i-1]-2] : 0)+2;
            }
        }
        res = max(res, dp[i]);
    }
    return res;
}