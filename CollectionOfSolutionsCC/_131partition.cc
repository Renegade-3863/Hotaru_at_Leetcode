#include "Solution.h"

// 第一版：单纯 DFS，不带记忆化
vector<vector<string>> Leetcode101_200::Solution::partition(string s)
{
    // 本题要求我们对一个给定的字符串进行回文分割，并输出所有可行的分割方案
    // 这题应该能很快反应出来是回溯/深搜算法
    // 先定义这个 helper function：checkPalindrome
    function<bool(int, int)> checkPalindrome = [&](int start, int end)
    {
        // 这个子过程用来判断 s 的下标 start 到 end 之间的子串是否是一个回文串
        int left = start, right = end;
        while(left < right)
        {
            if(s[left] == s[right])
            {
                ++left; --right;
            }
            else
            {
                return false;
            }
        }
        // 循环可以正常退出，我们返回 true，证明可以断定这个字符串是回文的
        return true;
    };
    // 我们可以定义一个如下的回溯函数体
    // backtrack(idx) 用于检查从 s[idx] 开始的所有合法的回文字符串并添加到一个本地的答案集合 path 中
    // 全局的答案数组，用于存储所有可行的分割结果
    vector<vector<string>> res;
    int n = s.size();
    // 本地的路径数组，存储当前的分割方案
    vector<string> path;
    function<void(int)> backtrack = [&](int idx)
    {
        // 递归结束条件：我们已经找到了一条完整，且完全合法的回文分割，就可以把这条路径添加到 res 中了
        if(idx == n)
        {
            res.push_back(path);
            return;
        }
        string cur = "";
        // 从当前位置开始逐步向后遍历新添加的字符串的结尾下标
        for(int i = idx; i < n; ++i)
        {
            // 先添加一个新字符
            // 判断添加后的新字符是不是一个合法的回文串，如果是，就加入到 path 中并继续深入递归
            if(checkPalindrome(idx, i))
            {
                path.push_back(s.substr(idx, i-idx+1));
                backtrack(i+1);
                // 回溯，弹出前面添加的结果
                path.pop_back();
            }
        }
    };
    // 对 backtrack 回溯函数进行调用即可
    backtrack(0);
    // 返回结果
    return res;
}

// 第二版：DFS + 记忆化数组
vector<vector<string>> partition(string s)
{
    // 本题要求我们对一个给定的字符串进行回文分割，并输出所有可行的分割方案
    // 这题应该能很快反应出来是回溯/深搜算法
    // 先定义这个 helper function：checkPalindrome
    // 添加一个记忆化数组 memo，用于记录可能重复查找的区间
    int n = s.size();
    // -1 代表还未检查过这个区间
    vector<vector<int>> memo(n, vector<int>(n, -1));
    function<bool(int, int)> checkPalindrome = [&](int start, int end) -> bool
    {
        // 利用记忆化信息，提高检查效率
        if(memo[start][end] != -1)
        {
            return memo[start][end];
        }
        // 这个子过程用来判断 s 的下标 start 到 end 之间的子串是否是一个回文串
        int left = start, right = end;
        while(left < right)
        {
            if(s[left] == s[right])
            {
                ++left; --right;
            }
            else
            {
                memo[start][end] = 0;
                return false;
            }
        }
        memo[start][end] = true;
        // 循环可以正常退出，我们返回 true，证明可以断定这个字符串是回文的
        return true;
    };
    // 我们可以定义一个如下的回溯函数体
    // backtrack(idx) 用于检查从 s[idx] 开始的所有合法的回文字符串并添加到一个本地的答案集合 path 中
    // 全局的答案数组，用于存储所有可行的分割结果
    vector<vector<string>> res;
    // 本地的路径数组，存储当前的分割方案
    vector<string> path;
    function<void(int)> backtrack = [&](int idx)
    {
        // 递归结束条件：我们已经找到了一条完整，且完全合法的回文分割，就可以把这条路径添加到 res 中了
        if(idx == n)
        {
            res.push_back(path);
            return;
        }
        string cur = "";
        // 从当前位置开始逐步向后遍历新添加的字符串的结尾下标
        for(int i = idx; i < n; ++i)
        {
            // 先添加一个新字符
            // 判断添加后的新字符是不是一个合法的回文串，如果是，就加入到 path 中并继续深入递归
            if(checkPalindrome(idx, i))
            {
                path.push_back(s.substr(idx, i-idx+1));
                backtrack(i+1);
                // 回溯，弹出前面添加的结果
                path.pop_back();
            }
        }
    };
    // 对 backtrack 回溯函数进行调用即可
    backtrack(0);
    // 返回结果
    return res;
}

// 第三版：DP + 回溯
vector<vector<string>> partition(string s)
{
    // 注意到我们的 checkPalindrome 过程可以使用记忆化数组加快检查效率，那么我们显然也可以用 DP 的方案自底向上预处理出所有的区间值，并在回溯的时候直接使用这个数组中的信息
    int n = s.size();
    vector<vector<bool>> dp(n, vector<bool>(n, true));
    // 按区间长度进行递推
    for(int len = 2; len <= n; ++len)
    {
        // 枚举所有可能的区间开始点
        for(int i = 0; i <= n-len; ++i)
        {
            // 计算出区间的结束点
            int j = i+len-1;
            // 利用递推关系进行回文性检查
            dp[i][j] = (s[i] == s[j] && dp[i+1][j-1]);
        }
    }
    // 之后使用和前两版相同的回溯算法即可
    // 全局的答案数组，用于存储所有可行的分割结果
    vector<vector<string>> res;
    // 本地的路径数组，存储当前的分割方案
    vector<string> path;
    function<void(int)> backtrack = [&](int idx)
    {
        // 递归结束条件：我们已经找到了一条完整，且完全合法的回文分割，就可以把这条路径添加到 res 中了
        if(idx == n)
        {
            res.push_back(path);
            return;
        }
        string cur = "";
        // 从当前位置开始逐步向后遍历新添加的字符串的结尾下标
        for(int i = idx; i < n; ++i)
        {
            // 先添加一个新字符
            // 判断添加后的新字符是不是一个合法的回文串，如果是，就加入到 path 中并继续深入递归
            if(dp[idx][i])
            {
                path.push_back(s.substr(idx, i-idx+1));
                backtrack(i+1);
                // 回溯，弹出前面添加的结果
                path.pop_back();
            }
        }
    };
    // 对 backtrack 回溯函数进行调用即可
    backtrack(0);
    // 返回结果
    return res;
}