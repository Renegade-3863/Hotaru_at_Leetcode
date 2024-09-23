#include "Solution.h"

vector<string> Leetcode1_100::Solution::restoreIpAddresses(string s)
{
    // 非常经典的一道回溯类题目，不过细节感觉比回溯本身要难写
    // 老规矩，回溯类问题用回溯树
    // 根据回溯树的方案，我们可以这样定义回溯的回调函数体：
    /*
        res: 全局的答案数组，存储所有可行的 IP 解析
        cur: 存储当前枝中已检出的 IP 子串
        idx: 当前检查到的 IP 地址子块的起始下标
    */
    function<void(vector<string>&, string, int, int)> backtrack = [&](vector<string>& res, string cur, int idx, int cnt)
    {
        // 考虑递归的结束条件
        // 单纯从 idx 上应该就可以实现
        // 有 BUG：这种情况下，我们可能会搞出来这种不合法的 IP 地址
        // 2.5.5.2.5.5.1.1.1.3.5
        // 因为我们没有限定添加的子模块的个数
        // 所以应该多添加一个限制条件
        // 如果我们现在要检查的下标是 s.size() 下标处的字符，并且已经添加了恰好4个子模块，此时 cur 中就应该已经存储
        // 了一串可行的 IP 解析，直接添加结果即可
        if(cnt == 4)
        {
            if(idx == s.size())
            {
                res.push_back(cur);
            }
            return;
        }
        // 否则，这个下标仍然有效，我们讨论下一个模块的可能情况
        // 循环检查同层
        // i 代表的是要从 idx 开始检出到下标 i 的子串
        int val = 0;
        for(int i = idx; i < idx+3 && i < s.size(); ++i)
        {
            // 还有一种错误情况需要排除：每个子模块都不能以字符'0'开头
            if(i > idx && s[idx] == '0')
            {
                break;
            }
            // 判断检出的子串数值上是否合法
            if(val*10+(s[i]-'0') <= 255)
            {
                // 合法，就继续深入递归
                backtrack(res, cur+s.substr(idx, i-idx+1)+(cnt != 3 ? "." : ""), i+1, cnt+1);
                val = val*10+(s[i]-'0');
            }
            // 否则，就可以直接 break 了
            else
            {
                break;
            }
        }
    };
    // 直接调用并返回结果即可
    vector<string> res;
    string cur;
    backtrack(res, cur, 0, 0);
    return res;
}