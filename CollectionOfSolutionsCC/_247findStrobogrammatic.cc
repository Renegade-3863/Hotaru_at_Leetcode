#include "Solution.h"

// 第一版：简单的纯 DFS，不带记忆化，居然可以通过，不过最好还是添加一下记忆化，那样更快一些
vector<string> Leetcode201_300::Solution::findStrobogrammatic(int n)
{
    // 依然是一道比较简单的递归构造类问题
    // 考虑下面的结构递推关系：
    // 一个更大的中心对称数，一定是由一个长度比它短2(掐头去尾)的小中心对称数，通过在头尾添加一对中心对称的数字字符形成的
    // 我们可以利用这种子问题关系来实现本题
    // 写一个内部嵌套递归，至于原因见函数体内部分析
    function<vector<string>(int, const int&)> dfs = [&](int len, const int& n) -> vector<string>
    {
        // 解释：如果要计算的是长度为0的中心对称数，那么我们显然只有空数字串这一种结果
        if(len == 0)
        {
            return {""};
        }
        // 解释：如果要计算的是长度为1的中心对称数，那么我们显然只有对应的长度为1的中心对称数字作为结果
        if(len == 1)
        {
            return {"0", "1", "8"};
        }
        // 其它情况下，进行递归操作
        vector<string> subStr = dfs(len-2, n);
        vector<string> res;
        // 对找到的 subStr 中的每一个更小的中心对称数，进行首尾添数即可
        int m = subStr.size();
        for(int i = 0; i < m; ++i)
        {
            // 根据题意，所有含有前导0的数字串都不是真正意义上的 "数字"，我们需要删掉对应的部分，不过应该注意的是，只有最上层的调用才可以执行这种删除操作，任何中间过程都不应该进行删除，否则会丢解
            // 这么看，我们还必须重写一个内部递归函数。。。有够 nt 的
            if(len != n)
            {
                res.push_back("0"+subStr[i]+"0");
            }
            res.push_back("1"+subStr[i]+"1");
            res.push_back("8"+subStr[i]+"8");
            res.push_back("6"+subStr[i]+"9");
            res.push_back("9"+subStr[i]+"6");
        }
        // 返回结果即可
        return res;
    };
    return dfs(n, n);
}

// 第二版：DFS + 记忆化数组
vector<string> Leetcode201_300::Solution::findStrobogrammatic(int n)
{
    // 添加一个记忆化数组
    vector<vector<string>> memo(n+1, vector<string>());
    // 依然是一道比较简单的递归构造类问题
    // 考虑下面的结构递推关系：
    // 一个更大的中心对称数，一定是由一个长度比它短2(掐头去尾)的小中心对称数，通过在头尾添加一对中心对称的数字字符形成的
    // 我们可以利用这种子问题关系来实现本题
    // 写一个内部嵌套递归，至于原因见函数体内部分析
    function<vector<string>(int, const int&)> dfs = [&](int len, const int& n) -> vector<string>
    {
        // 如果这种长度的中心对称串已经被记录过，我们就直接返回记录即可
        if(!memo[len].empty())
        {
            return memo[len];
        }
        // 解释：如果要计算的是长度为0的中心对称数，那么我们显然只有空数字串这一种结果
        if(len == 0)
        {
            memo[0] = {""};
            return memo[0];
        }
        // 解释：如果要计算的是长度为1的中心对称数，那么我们显然只有对应的长度为1的中心对称数字作为结果
        if(len == 1)
        {
            memo[1] = {"0", "1", "8"};
            return memo[1];
        }
        // 其它情况下，进行递归操作
        vector<string> subStr = dfs(len-2, n);
        vector<string> res;
        // 对找到的 subStr 中的每一个更小的中心对称数，进行首尾添数即可
        int m = subStr.size();
        for(int i = 0; i < m; ++i)
        {
            // 根据题意，所有含有前导0的数字串都不是真正意义上的 "数字"，我们需要删掉对应的部分，不过应该注意的是，只有最上层的调用才可以执行这种删除操作，任何中间过程都不应该进行删除，否则会丢解
            // 这么看，我们还必须重写一个内部递归函数。。。有够 nt 的
            if(len != n)
            {
                res.push_back("0"+subStr[i]+"0");
            }
            res.push_back("1"+subStr[i]+"1");
            res.push_back("8"+subStr[i]+"8");
            res.push_back("6"+subStr[i]+"9");
            res.push_back("9"+subStr[i]+"6");
        }
        memo[len] = res;
        // 返回结果即可
        return res;
    };
    return dfs(n, n);
}