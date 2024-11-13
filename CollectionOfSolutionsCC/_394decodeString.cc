#include "Solution.h"

string Leetcode301_400::Solution::decodeString(string s)
{
    // 本质上和解析嵌套整数的那道题没有区别，我们依旧采取由浅入深的策略来解决本题
    // 尝试用递归的写法
    // 先写出不含任何嵌套括号，每个字符串只包含一层[字符串]组合的情况下的解析方案，带数字的只是深入递归而已
    int n = s.size(), idx = 0;
    function<string(int&)> dfs = [&](int& idx) -> string
    {
        // cout << idx << endl;
        // 存储结果的展开字符串
        string res;
        // 记录子串重复的次数(如果有必要的话)
        int val = 0;
        // 遍历从 idx 开始的字符串
        while(idx < n)
        {
            // s[idx] 有四种可能
            // 1. s[idx] 是一个数字
            // 2. s[idx] 是一个字符
            // 3. s[idx] 是一个左中括号 '['
            // 4. s[idx] 是一个右中括号 ']'
            // 情况1.
            if(isdigit(s[idx]))
            {
                // 累加到数字 val 中
                val = val*10+(s[idx++]-'0');
            }
            // 情况2.
            else if(s[idx] != '[' && s[idx] != ']')
            {
                // 直接尾接到 res 中即可
                res.push_back(s[idx++]);
            }
            // 情况3.
            else if(s[idx] == '[')
            {
                string sub = dfs(++idx);
                // 把对应部分的字符解析出来，尾接即可
                for(int i = 0; i < val; ++i)
                {
                    res += sub;
                }
                // 重置 val
                val = 0;
            }
            // 情况4.
            else
            {
                // 此时我们只需要更新 idx，并退出循环即可
                ++idx;
                break;
            }
        }
        return res;
    };
    return dfs(idx);
}