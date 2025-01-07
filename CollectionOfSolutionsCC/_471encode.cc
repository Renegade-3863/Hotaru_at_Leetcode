#include "Solution.h"

string Leetcode401_500::Soltuion::encode(string s)
{
    // 编写 dfs 代码时发现函数嵌套调用的问题，所以直接改成 dp 方式来写了
    int n = s.size();
    vector<vector<string>> dp(n, vector<string>(n));
    // 这里是根据后面逻辑得出需要定义的子过程 findRepeatPattern，用于寻找 s[i..j] 中最短的循环节的长度
    function<string(int, int)> findRepeatPattern = [&](int i, int j) -> string
    {
        // 结果字符串
        string res = s.substr(i, j-i+1);
        if(j-i+1 <= 4)
        {
            return res;
        }
        string cur = res;
        // 否则，我们找循环节，这里直接用 459 题的方法来找最短循环节即可，找最短节的原因不难想
        // KMP 就不再写一遍了，直接用 find 函数代替，简化实现代码
        // 这行代码的逻辑详见 459 题题解
        int len = (cur+cur).find(cur, 1);
        // 如果 len == s.size()，说明找到的重复点是尾接的那个 s，这个 s 不存在循环节
        if(len != cur.size())
        {
            // 计算出循环节的长度，返回对应的循环节
            // 注意：对应的循环节也要先进行编码再执行拼接，这里用数组代替
            return to_string(cur.size() / len) + "[" + dp[i][i+len-1] + "]";
        }
        // 不存在循环节，返回原串 s
        return cur;
    }; 
    for(int len = 1; len <= n; ++len)
    {
        for(int i = 0; i+len-1 < n; ++i)
        {
            int j = i+len-1;
            dp[i][j] = findRepeatPattern(i, j);
            if(len > 4)
            {
                for(int k = i; k < j; ++k)
                {
                    string tmp = dp[i][k]+dp[k+1][j];
                    if(dp[i][j].size() > tmp.size())
                    {
                        dp[i][j] = tmp;
                    }
                }
            }
        }
    }
    return dp[0][n-1];
}