#include "Solution.h"

int Leetcode701_800::Soltuion::minimumDeleteSum(string s1, string s2)
{
    // 依然是动态规划问题，我们考虑如何定义递归子问题：
    // 定义 dfs(i, j) 代表把 s1 的前 i 个字符构成的子串删成和 s2 的前 j 个字符构成的子串，所需删除的字符的 ASCII 值的最小和
    // 考虑如何进行递推
    // 基本情况：
    // 如果 i == 0 || j == 0
    // 也就是说其中一个字符串是空的，那么我们直接返回 max(i, j) 即可
    // 就是说我们把非空的那个字符串也删成空的即可
    // 其它情况为一般情况，我们考虑如何进行递推
    // 如果 s1[i-1] == s2[j-1]，说明最后两个字符是一样的，我们有 "不动这两个字符中的任何一个" 的选择
    // 那么 dfs(i, j) = min(dfs(i-1, j-1), dfs(i-1, j)+s1[i-1], dfs(i, j-1)+s2[j-1])
    // 也就是，我们现在有三种选择：
    // 1. 两个结尾字符都不删
    // 2. 删除 s1[i-1]
    // 3. 删除 s2[j-1]
    // 观察上面三个关系式：
    // 我们会发现，其实 dfs(i-1, j) 和 dfs(i, j-1) 在递推过程中都会包含到一个 dfs(i-1, j-1) 项
    // 而且这种递推还一定会给 dfs(i-1, j) / dfs(i, j-1) 添加上某些常数项 (因为要删改成 dfs(i-1, j-1)，二者都需要删除一个字符)
    // 所以实际上 dfs(i-1, j)+s1[i-1] 和 dfs(i, j-1)+s2[j-1] 我们就不用管了，它们一定会比单纯的 dfs(i-1, j-1) 要大
    // 否则，
    // 如果 s1[i-1] != s2[j-1]，那么说明最后两个字符不相等，那么我们就必须删除其中一个
    // 也就是
    // dfs(i, j) = min(dfs(i-1, j)+s1[i-1], dfs(i, j-1)+s2[j-1])
    // 综上，递推公式我们就找到了，剩下的就是写代码了
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        if(i == 0)
        {
            // 如果两个部分其中一个为空，那么我们要做的是删掉另一个非空部分中的所有字符
            int res = 0;
            for(int k = 0; k < j; ++k)
            {
                res += s2[k];
            }
            return res;
        }
        if(j == 0)
        {
            int res = 0;
            for(int k = 0; k < i; ++k)
            {
                res += s1[k];
            }
            return res;
        }
        if(s1[i-1] == s2[j-1])
        {
            return dfs(i-1, j-1);
        }
        return min(dfs(i-1, j)+s1[i-1], dfs(i, j-1)+s2[j-1]);
    };
    return dfs(s1.size(), s2.size());
}

// 第二版：修改上面的暴力 dfs 方法，添加上记忆化
int minimumDeleteSum(string s1, string s2)
{
    int m = s1.size(), n = s2.size();
    vector<vector<int>> memo(m+1, vector<int>(n+1, -1));
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 记忆化步骤
        if(memo[i][j] != -1)
        {
            return memo[i][j];
        }
        if(i == 0)
        {
            // 如果两个部分其中一个为空，那么我们要做的是删掉另一个非空部分中的所有字符
            int res = 0;
            for(int k = 0; k < j; ++k)
            {
                res += s2[k];
            }
            memo[i][j] = res;
            return res;
        }
        if(j == 0)
        {
            int res = 0;
            for(int k = 0; k < i; ++k)
            {
                res += s1[k];
            }
            memo[i][j] = res;
            return res;
        }
        if(s1[i-1] == s2[j-1])
        {
            memo[i][j] = dfs(i-1, j-1);
            return memo[i][j];
        }
            memo[i][j] = min(dfs(i-1, j)+s1[i-1], dfs(i, j-1)+s2[j-1]);
        return memo[i][j];
    };
    return dfs(s1.size(), s2.size());
}

// 第三版：尝试把自顶向下的 dfs 改成自底向上的 dp
int minimumDeleteSum(string s1, string s2)
{
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    // 先初始化所有的边界情况
    // 这里发现上面处理基本情况时的一些问题：
    // 我们没必要在每次遇到边界情况的时候，都重新计算一次非空字符串的所有字符和
    // 这些数据已经保存在了我们的 dp 数组中
    // 默认情况下，dp[0][0] 的结果就是 0，这一点我们已经处理完了
    // 填写第一列
    for(int i = 1; i <= m; ++i)
    {
        dp[i][0] = dp[i-1][0]+s1[i-1];
    }
    // 之后填写第一行
    for(int j = 1; j <= n; ++j)
    {
        dp[0][j] = dp[0][j-1]+s2[j-1];
    }
    // 边界情况初始化完成，之后我们可以考虑开始递推流程了
    for(int i = 1; i <= m; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            // s1[i-1] == s2[j-1] 和 s1[i-1] != s2[j-1] 两种情况
            if(s1[i-1] == s2[j-1])
            {
                dp[i][j] = dp[i-1][j-1];
            }
            else
            {
                dp[i][j] = min(dp[i-1][j]+s1[i-1], dp[i][j-1]+s2[j-1]);
            }
        }
    }
    // 结果就是 dp[m][n]
    return dp[m][n];
}

// 第四版：处理 DP 数组的空间优化
int minimumDeleteSum(string s1, string s2)
{
    // 这种二维的 DP 好多都能简化空间复杂度
    // 我们考虑进行滚动数组优化
    // 只保存第一行即可
    int n = s2.size(), m = s1.size();
    vector<int> dp(n+1, 0);
    // 开始的时候，dp[0] 就对应了第三版中的 dp[0][0]，所以我们不用做任何初始化
    // 但是在循环体内部，我们是需要对每一个 dp[0] 进行初始化的，这一点不能忘！！
    for(int j = 1; j <= n; ++j)
    {
        dp[j] = dp[j-1]+s2[j-1];
    }
    for(int i = 1; i <= m; ++i)
    {
        // tmp 用于记录 dp[j-1] 原本的值，这个值对应的是上面方法中的 dp[i-1][j-1]
        int tmp = dp[0];
        // cout << tmp << endl;
        for(int j = 0; j <= n; ++j)
        {
            // 注意，如果 j == 0，那么我们需要做的是直接计算，而不是用递推关系式，不然会访问 -1 下标
            if(j == 0)
            {
                // 注意，s1 此时子串长度为 i，而 dp[0] 记录的是长度为 i-1 的 s1 子串字符值和
                // 所以我们添加一个 s1[i-1] 的值即可完成更新
                dp[0] += s1[i-1];
                continue;
            }
            int memo = dp[j];
            // 否则，j 大于 0，我们正常进行更新即可
            if(s1[i-1] == s2[j-1])
            {
                // 注意，tmp 对应的是 dp[i-1][j-1]，使用完后，我们需要更新它
                // 实际上需要更新成 dp[j] 更新前的值，对标上面方法中的 dp[i-1][j]
                // 但更新 dp[j]，我们又需要 tmp 更新前的值，所以我们用另一个中间值 memo 来完成更新
                dp[j] = tmp;
            }
            else
            {
                int cur = min(dp[j-1]+s2[j-1], dp[j]+s1[i-1]);
                dp[j] = cur;
            }
            tmp = memo;
        }
    }
    // dp[n] 就是结果
    return dp[n];
}