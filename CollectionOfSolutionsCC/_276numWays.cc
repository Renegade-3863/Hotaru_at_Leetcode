#include "Solution.h"

// 第一版：暴力 DFS，不带记忆化，TLE (64/65)
int Leetcode201_300::Solution::numWays(int n, int k)
{
    // 经典的状态 DP 类问题
    // 还是先从自顶向下的角度进行分析
    // 定义下面的 dfs 函数：
    // dfs(i, isSame) 代表给前 i 个栅栏上色，并且第 i 个栅栏和前面的一个栅栏 (isSame == true -> 相等, isSame == false -> 不相等)
    // 之后我们考虑如何进行递推
    // dfs(i, true) = dfs(i-1, false) 
    // 意思是，最后一个栅栏和前一个相同的涂法，应该是前一个和再前一个颜色不相等，之后再把第 i 个栅栏涂成和第 i-1 个相等颜色的方法数
    // dfs(i, false) = (k-1)*dfs(i-1, true) + (k-1)*dfs(i-1. false)
    // 意思是，最后一个栅栏和前一个颜色不相同的涂法，等于前一个和再前一个颜色不等，加上前一个和再前一个颜色相等，最后把第 i 个栅栏涂成和第 i-1 个不等颜色的方法数
    // 解释一下这里乘上 (k-1) 的原因：因为我们要的是当前栅栏和前一个颜色不同，所以对于前面找到的每一种涂色方案，我们当前栅栏的颜色方法都只有 (k-1) 种，因为要除去被占用的那一种
    // 明确了递归规则，写代码就不难了
    function<int(int, bool)> dfs = [&](int i, bool isSame) -> int
    {
        // 递归结束情况
        // i == 1
        // 不过注意一点，如果 isSame == true 和 isSame == false 我们都返回 k，那么显然在 i == 2 的时候会出问题
        // 因为 dfs(2, false) 会用到 dfs(1, true) 和 dfs(1, false) 的值，而如果我们 dfs(1, true) 和 dfs(1, false) 都返回 k
        // 明眼人都能看出这样 dfs(2, false) 计算的结果就是错的
        // 换句话说，我们相当于计算了两次给第一个栅栏涂某一种颜色的情况
        // 所以我们只能给一种情况记 k 次，另一种情况只能记 0 次
        // 那么应该给谁记 k 次呢？
        // 不难发现应该是 dfs(1, false)
        // 原因很简单：dfs(2, true) 会用到这个值，同时从定义上也更好解释，因为前面没有任何栅栏，所以我们做不到给第一个栅栏涂成和前面的栅栏同样的颜色这件事
        if(i == 1)
        {
            return isSame ? 0 : k;
        }
        // 之后的一般情况就很简单了
        return isSame ? dfs(i-1, false) : (k-1)*(dfs(i-1, false)+dfs(i-1, true));
    };
    // 调用即可
    return dfs(n, true)+dfs(n, false);
}

// 第二版：DFS + 记忆化，正常通过
int numWays(int n, int k)
{
    // 简单地添加一个记忆化数组
    vector<vector<int>> memo(n, vector<int>(2, -1));
    // 经典的状态 DP 类问题
    // 还是先从自顶向下的角度进行分析
    // 定义下面的 dfs 函数：
    // dfs(i, isSame) 代表给前 i 个栅栏上色，并且第 i 个栅栏和前面的一个栅栏 (isSame == true -> 相等, isSame == false -> 不相等)
    // 之后我们考虑如何进行递推
    // dfs(i, true) = dfs(i-1, false) 
    // 意思是，最后一个栅栏和前一个相同的涂法，应该是前一个和再前一个颜色不相等，之后再把第 i 个栅栏涂成和第 i-1 个相等颜色的方法数
    // dfs(i, false) = (k-1)*dfs(i-1, true) + (k-1)*dfs(i-1. false)
    // 意思是，最后一个栅栏和前一个颜色不相同的涂法，等于前一个和再前一个颜色不等，加上前一个和再前一个颜色相等，最后把第 i 个栅栏涂成和第 i-1 个不等颜色的方法数
    // 解释一下这里乘上 (k-1) 的原因：因为我们要的是当前栅栏和前一个颜色不同，所以对于前面找到的每一种涂色方案，我们当前栅栏的颜色方法都只有 (k-1) 种，因为要除去被占用的那一种
    // 明确了递归规则，写代码就不难了
    function<int(int, bool)> dfs = [&](int i, bool isSame) -> int
    {
        // 递归结束情况
        // i == 1
        // 不过注意一点，如果 isSame == true 和 isSame == false 我们都返回 k，那么显然在 i == 2 的时候会出问题
        // 因为 dfs(2, false) 会用到 dfs(1, true) 和 dfs(1, false) 的值，而如果我们 dfs(1, true) 和 dfs(1, false) 都返回 k
        // 明眼人都能看出这样 dfs(2, false) 计算的结果就是错的
        // 换句话说，我们相当于计算了两次给第一个栅栏涂某一种颜色的情况
        // 所以我们只能给一种情况记 k 次，另一种情况只能记 0 次
        // 那么应该给谁记 k 次呢？
        // 不难发现应该是 dfs(1, false)
        // 原因很简单：dfs(2, true) 会用到这个值，同时从定义上也更好解释，因为前面没有任何栅栏，所以我们做不到给第一个栅栏涂成和前面的栅栏同样的颜色这件事
        // 记忆化调用
        if(memo[i-1][isSame] != -1)
        {
            return memo[i-1][isSame];
        }
        if(i == 1)
        {
            memo[0][isSame] = isSame ? 0 : k;
            return memo[0][isSame];
        }
        // 之后的一般情况就很简单了
        memo[i-1][isSame] = isSame ? dfs(i-1, false) : (k-1)*(dfs(i-1, false)+dfs(i-1, true));
        return memo[i-1][isSame];
    };
    // 调用即可
    return dfs(n, true)+dfs(n, false);
}

// 第三版：改写成 DP
int numWays(int n, int k)
{
    // 还是用二维数组即可
    vector<vector<int>> dp(n, vector<int>(2, 0));
    // 对应上面的基本情况
    dp[0][0] = k;
    for(int i = 1; i < n; ++i)
    {
        for(int isSame = 0; isSame < 2; ++isSame)
        {
            dp[i][isSame] = isSame ? dp[i-1][false] : (k-1)*(dp[i-1][true]+dp[i-1][false]);
        }
    }
    return dp[n-1][true]+dp[n-1][false];
}

// 第四版：空间优化
int numWays(int n, int k)
{
    // 不再赘述，这题的空间优化很简单
    int dp0 = k, dp1 = 0;
    for(int i = 1; i < n; ++i)
    {
        int tmp = dp0;
        dp0 = (k-1)*(dp0+dp1);
        dp1 = tmp;
    }
    return dp0+dp1;
}