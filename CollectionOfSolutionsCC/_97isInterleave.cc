#include "Solution.h"

// 版本一: 单纯 DFS，不带记忆化，很大概率暴毙
bool Leetcode1_100::Solution::isInterleave(string s1, string s2, string s3)
{
    // 依然是动态规划的一道入门级别的题目，不过我们依然不要上来就考虑 DP 的状态转移方程，那样其实不利于算法初学者理解 DP 的本质
    // 依然三步走：完全暴力 DFS -> 暴力 DFS + 记忆化 -> 完全优化 DP
    // 完全暴力 DFS
    // 可以这样定义 dfs 回调：
    // dfs(i, j, k) 代表使用 s1 的前 i 个字符，以及 s2 的前 j 个字符，能否交错出 s3 的前 k 个字符
    // 简化：注意到这三个数值之间有关系：i+j = k
    // 故简化成这样的定义：
    // dfs(i, j) 代表使用 s1 的前 i 个字符，以及 s2 的前 j-i 个字符，能否交错出 s3 的前 j 个字符
    // 之后考虑状态如何转移
    // 这样想：
    // 如果我们要判断 dfs(i, j)
    // 那么无非两种情况：
    // 1. 拿 s1 的第 i 个字符和 s3 的第 j 个字符进行匹配
    // 此时剩下要判断的就是 dfs(i-1, j-1)，也就是是否能够用 s1 剩下的前面 i-1 个字符，以及 s2 的前 j-i 个字符，交错出 s3 的前 j-1 个字符
    // 2. 拿 s2 的第 j-i 个字符和 s3 的第 j 个字符进行匹配
    // 此时剩下要判断的就是 dfs(i, j-1)，含义类似情况1可以推知
    // 明确了这些，回调函数就很好写了
    function<bool(int, int)> dfs = [&](int i, int j) -> bool
    {
        // 基本情况1：如果 i == j，即 s1 中剩下的字符数量和 s3 中相等，我们只需要判断这两个子串是否相等即可
        if(i == j)
        {
            return s1.substr(0, i) == s3.substr(0, j);
        }
        // 基本情况2: 如果 i == 0，即 s2 中剩下的字符数量和 s3 中相等，我们也只需要判断这两个子串是否相等即可
        if(i == 0)
        {
            return s2.substr(0, j) == s3.substr(0, j);
        }
        // 情况1.
        if(s1[i-1] == s3[j-1] && dfs(i-1, j-1))
        {
            return true;
        }
        // 情况2.
        if(s2[j-i-1] == s3[j-1] && dfs(i, j-1))
        {
            return true;
        }
        // 否则就无法交错，返回 false
        return false;
    };
    int m = s1.size(), n = s2.size(), len = s3.size();
    if(m+n != len)
    {
        return false;
    }
    return dfs(m, len);
}

// 版本2 DFS + 记忆化
bool isInterleaveMemo(string s1, string s2, string s3)
{
    // 依然是动态规划的一道入门级别的题目，不过我们依然不要上来就考虑 DP 的状态转移方程，那样其实不利于算法初学者理解 DP 的本质
    // 依然三步走：完全暴力 DFS -> 暴力 DFS + 记忆化 -> 完全优化 DP
    // 完全暴力 DFS
    // 可以这样定义 dfs 回调：
    // dfs(i, j, k) 代表使用 s1 的前 i 个字符，以及 s2 的前 j 个字符，能否交错出 s3 的前 k 个字符
    // 简化：注意到这三个数值之间有关系：i+j = k
    // 故简化成这样的定义：
    // dfs(i, j) 代表使用 s1 的前 i 个字符，以及 s2 的前 j-i 个字符，能否交错出 s3 的前 j 个字符
    // 之后考虑状态如何转移
    // 这样想：
    // 如果我们要判断 dfs(i, j)
    // 那么无非两种情况：
    // 1. 拿 s1 的第 i 个字符和 s3 的第 j 个字符进行匹配
    // 此时剩下要判断的就是 dfs(i-1, j-1)，也就是是否能够用 s1 剩下的前面 i-1 个字符，以及 s2 的前 j-i 个字符，交错出 s3 的前 j-1 个字符
    // 2. 拿 s2 的第 j-i 个字符和 s3 的第 j 个字符进行匹配
    // 此时剩下要判断的就是 dfs(i, j-1)，含义类似情况1可以推知
    // 明确了这些，回调函数就很好写了
    int m = s1.size(), n = s2.size(), len = s3.size();
    // 在版本一的基础上，添加一个全局的记忆化数组
    vector<vector<int>> memo(m+1, vector<int>(len+1, -1));
    function<bool(int, int)> dfs = [&](int i, int j) -> bool
    {
        if(memo[i][j] != -1)
        {
            return memo[i][j];
        }
        // 基本情况1：如果 i == j，即 s1 中剩下的字符数量和 s3 中相等，我们只需要判断这两个子串是否相等即可
        if(i == j)
        {
            return s1.substr(0, i) == s3.substr(0, j);
        }
        // 基本情况2: 如果 i == 0，即 s2 中剩下的字符数量和 s3 中相等，我们也只需要判断这两个子串是否相等即可
        if(i == 0)
        {
            return s2.substr(0, j) == s3.substr(0, j);
        }
        // 情况1.
        if(s1[i-1] == s3[j-1] && dfs(i-1, j-1))
        {
            memo[i][j] = true;
            return true;
        }
        // 情况2.
        if(s2[j-i-1] == s3[j-1] && dfs(i, j-1))
        {
            memo[i][j] = true;
            return true;
        }
        // 否则就无法交错，返回 false
        memo[i][j] = false;
        return false;
    };
    if(m+n != len)
    {
        return false;
    }
    return dfs(m, len);
}

// 版本3 完全优化的 DP 方案
int isInterleaveDP(string s1, string s2, string s3)
{
    int m = s1.size(), n = s2.size(), len = s3.size();
    if(m+n != len)
    {
        return false;
    }
    vector<vector<bool>> dp(m+1, vector<bool>(len+1, false));
    // 边界情况设定
    // i == 0 的情况
    for(int j = 0; j <= n; ++j)
    {
        dp[0][j] = s2.substr(0, j) == s3.substr(0, j);
    }
    // i == j 的情况
    for(int i = 0; i <= m; ++i)
    {
        dp[i][i] = s1.substr(0, i) == s3.substr(0, i);
    }
    // 进行完整的递推即可
    for(i = 1; i <= m; ++i)
    {
        // 注意这里的一个循环边界细节：由于我们这里是自底向上进行数组的填写和条件的检查，因而可能会出现越界情况
        // 具体的，s2[j-i-1] 这里可能会取到超出了 s2 原本可取范围内的元素下标，因而这里需要限制一下 j 的取值
        for(int j = i+1; j <= len && j-i <= n; ++j)
        {
            dp[i][j] = (s1[i-1] == s3[j-1] && dp[i-1][j-1]) || (s2[j-i-1] == s3[j-1] && dp[i][j-1]);
        }
    }
    // 返回最终结果即可
    return dp[m][len];
}

// 版本4 完全优化的 DP 方案 + 空间优化
int isInterleaveDPOpt(string s1, string s2, string s3)
{
    int m = s1.size(), n = s2.size(), len = s3.size();
    if(m+n != len)
    {
        return false;
    }
    // 观察我们上面的递推关系式，注意到它们的第二维都是 j-1
    // 而前面一维的取值为 i-1 或 i 本身
    // 这显然暗示着我们，这个二维数组可以被压缩
    // 考虑这样的事实，我们填表的时候，当前要填写的值只和它左侧和左上的两个值有关，那么我们只需要记录当前行和上一行的信息就行了
    vector<vector<bool>> dp(2, vector<bool>(len+1, false));
    for(int j = 0; j <= n; ++j)
    {
        dp[0][j] = s2.substr(0, j) == s3.substr(0, j);
    }
    for(int i = 1; i <= m; ++i)
    {
        // 更新 i == j 的情况
        dp[1][i] = s1.substr(0, i) == s3.substr(0, i);
        for(int j = i+1; j <= len && j-i <= n; ++j)
        {
            // 按画出来的表格进行判断，我们除了需要把上一行对应更新了的位置一一复制下来，还需要最后把最后一位也更新下来(这里画个图就能理解我想说什么了)
            dp[1][j] = (s1[i-1] == s3[j-1] && dp[0][j-1]) || (s2[j-i-1] == s3[j-1] && dp[1][j-1]);
            dp[0][j-1] = dp[1][j-1];
        }
        dp[0][i+n] = dp[1][i+n];
    }
    return m == 0 ? dp[0][len] : dp[1][len];
}