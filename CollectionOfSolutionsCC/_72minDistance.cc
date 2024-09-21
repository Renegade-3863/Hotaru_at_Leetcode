#include "Solution.h"

int Leetcode1_100::Solution::minDistance(string word1, string word2)
{
    // 非常经典的动态规划题，可以先从递归/深搜的角度进行分析
    // 我们要解决的最终问题是：
    // word1 的全串转换成 word2 的全串的最少操作数 (设为 dfs(word1, m, word2, n) 问题)
    // 那么我们可以用有三种可能的子问题(假设 word1 的长度是 m，word2 的长度是 n：
    // 1. 先把 word1 的前 m-1 个字符转换成 word2 的前 n 个字符，最后一步删除 word1 结尾的字符
    //    这种构造方式我们有 dfs(word1, m-1, word2, n)+1 次操作
    // 2. 先把 word1 的前 m 个字符转换成 word2 的前 n-1 个字符，最后一步往转换后的 字符串结尾添加一个 word2 结尾的字符
    //    这种构造方式我们有 dfs(word1, m, word2, n-1)+1 次操作
    // 3. 先把 word1 的前 m-1 个字符转换成 word2 的前 n-1 个字符，最后一步把转换后的最后一对不一样的字符都转换成 word2 中结尾的那个字符
    //    这种构造方式我们有 dfs(word1, m-1, word2, n-1) + (word[i-1] != word[j-1]) 种构造方式
    //    (思考：本题要求是把 word1 转换成 word2，所以这里我们替换的时候，只能是把 word1 转换后结尾的字符固定替换成 word2 中结尾的字符)
    // 因而我们不难写出下面的递归代码
    int m = word1.size(), n = word2.size();
#if 0
    // ----- 虽然只过了 24 个案例就 TLE 了 ----- 
    function<int(const string&, int, const string&, int)> dfs = [&](const string& word1, int i, const string& word2, int j) -> int
    {
        // 边界情况：如果两个字符串有一个为空，则只能要么不断向 word1 中添加字符，要么不断从 word1 中删除字符
        // 这里次数就是二者中不为零的那一个的长度，使用异或投机一波
        if(i == 0 || j == 0)
        {
            return i^j;
        }
        return min(min(dfs(word1, i-1, word2, j)+1, dfs(word1, i, word2, j-1)+1), dfs(word1, i-1, word2, j-1) + (word1[i-1] != word2[j-1]));
    };
    return dfs(word1, m, word2, n);
#endif
    // 观察到，我们一定重复计算了非常多的重复子问题：
    // 例如 dfs(3, 4) (如果我们要求解的最终问题是 dfs(10, 8))
    // 因而，我们只需要引入记忆化，也就把解法转成了动态规划了
    // 利用我们深搜的参数，我们可以定义下面这样的 DP 数组
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    // DP 除了具有这种最优子结构性质(本题没有最优，只有重叠)，还有重叠子问题的性质
    // 我们上面说到会有很多重复求解的子问题，因而这些子问题的解就可以只求解一次，之后把它们记录到 DP 数组中，供后续调用
    // dp[i][j] 代表是和上面深搜函数一样的意义，即 dfs(word1, i, word2, j) 问题
    for(int i = 0; i <= m; ++i)
    {
        for(int j = 0; j <= n; ++j)
        {
            // 这里这么写只是为了和上面的 dfs 函数体统一理解，实际运行起来由于编译器预测的性质，跑起来会效率很低，建议还是把能分开的部分分开来写
            dp[i][j] = i == 0 || j == 0 ? i ^ j : min(min(dp[i-1][j]+1, dp[i][j-1]+1), dp[i-1][j-1]+ (word1[i-1] != word2[j-1]));
        }
    }
    // dp[m][n] 即为答案
    return dp[m][n];
}