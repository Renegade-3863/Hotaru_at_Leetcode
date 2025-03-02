#include "Solution.h"

// 第一版：纯暴力 DFS，不加任何记忆化
int Leetcode601_700::Soltuion::countSubstrings(string s)
{
    // 经典的 DP 类问题
    // 我们可以这样来处理
    // 定义一个这样的子问题：
    // dp[i][j] 代表区间 [i, j] 代表的子串是否能够形成一个回文子串
    // 那么对于 dp[i][j]
    // 我们只需要考虑：
    // s[i] == s[j] && dp[i+1][j-1] 是否成立即可
    // 如果这个表达式结果为 true，那么 dp[i][j] 就是 true
    // 否则，dp[i][j] 就是 false
    // 我们按照这个格式来定义子问题函数即可
    // tot 定义为全局的最终结果
    int tot = 0, n = s.size();
    // 同时注意，本题我们必须在 dfs 中直接引入记忆化
    // 因为 tot 的更新只能是有效更新，不能重复更新
    // 所以我们必须记忆哪些区间已经处理过了
    // -1 代表这个区间还没被处理过
    vector<vector<int>> memo(n, vector<int>(n, -1));
    function<bool(int, int)> dfs = [&](int i, int j) -> bool
    {
        // 定义基本情况，如果 i == j，那么这个子串就是一个回文串
        if(i == j)
        {
            if(memo[i][j] == -1)
            {
                ++tot;
                memo[i][j] = 1;
            }
            return true;
        }
        // 如果 i == j-1，那么我们也只需要检查 s[i] 是否等于 s[j]
        if(i == j-1)
        {
            if(memo[i][j] == -1)
            {
                if(s[i] == s[j])
                {
                    ++tot;
                    memo[i][j] = 1;
                }
                else
                {
                    memo[i][j] = 0;
                }
            }
            return memo[i][j];
        }
        // 记忆化
        if(memo[i][j] != -1)
        {
            return memo[i][j];
        }
        // 否则，是一般情况，我们考虑上面的递推关系式
        if(s[i] == s[j] && dfs(i+1, j-1))
        {
            // 只有第一次计算出这个结果的时候才进行赋值
            ++tot;
            memo[i][j] = 1;
            return true;
        }
        memo[i][j] = 0;
        return false;
    };
    for(int len = 1; len <= n; ++len)
    {
        for(int i = 0; i <= n-len; ++i)
        {
            int j = i+len-1;
            // cout << i << ", " << j << endl;
            dfs(i, j);
        }
    }
    return tot;
}

// 第二版：把 DFS 改成自底向上的 DP 
int countSubstrings(string s)
{
    int n = s.size(), res = 0;
    vector<vector<int>> dp(n, vector<int>(n, -1));
    // 对一些已知结果进行初始化
    dp[0][0] = 1;
    ++res;
    for(int i = 1; i < n; ++i)
    {
        dp[i][i] = 1;
        ++res;
        if(s[i] == s[i-1])
        {
            dp[i-1][i] = 1;
            ++res;
        }
        else
        {
            dp[i][i-1] = 0;
        }
    }
    // 之后开始填表
    for(int len = 3; len <= n; ++len)
    {
        for(int i = 0; i <= n-len; ++i)
        {
            int j = i+len-1;
            if(s[i] == s[j] && dp[i+1][j-1] == 1)
            {
                if(dp[i][j] == -1)
                {
                    ++res;
                }
                dp[i][j] = 1;
            }
            else
            {
                dp[i][j] = 0;
            }
        }
    }
    return res;
}