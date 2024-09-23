#include "Solution.h"

// 第一版：完全纯粹的 DFS，直接进行一个时的超
int Leetcode1_100::Solution::numTrees(int n)
{
    // 上一题的简单版了属于是，还是三步走：纯递归 -> 递归+记忆化 -> dp
    // 纯递归版本
    // 定义一个递归回调函数：
    // int dfs(int i, int j)
    // 意义为使用 [i, j] 中的元素可以构成的不同二叉搜索树的个数
    // 之后就和上一题的思路完全一致了
    function<int(int, int)> dfs = [&](int i, int j)
    {
        // 基本情况
        // 如果这个集合是空的，那么只能构造一种树，就是只有一个空结点的树
        if(i > j)
        {
            return 1;
        }
        // 一般情况，进行循环，检查分割点
        int res = 0;
        for(int k = i; k <= j; ++k)
        {
            int leftCnt = dfs(i, k-1);
            int rightCnt = dfs(k+1, j);
            res += leftCnt * rightCnt;
        }
        // 返回结果
        return res;
    };
    // 进行调用即可
    return dfs(1, n);
}

// 第二版：DFS 爆改 记忆化+DFS
int numTreesMemo(int n)
{
    // 上一题的简单版了属于是，还是三步走：纯递归 -> 递归+记忆化 -> dp
    // 纯递归版本
    // 定义一个递归回调函数：
    // int dfs(int i, int j)
    // 意义为使用 [i, j] 中的元素可以构成的不同二叉搜索树的个数
    // 之后就和上一题的思路完全一致了
    // 记忆化数组
    vector<vector<int>> memo(n, vector<int>(n, -1));
    function<int(int, int)> dfs = [&](int i, int j)
    {
        if(i >= 1 && i <= n && j >= 1 && j <= n && memo[i-1][j-1] != -1)
        {
            return memo[i-1][j-1];
        }
        // 基本情况
        // 如果这个集合是空的，那么只能构造一种树，就是只有一个空结点的树
        if(i > j)
        {
            return 1;
        }
        // 一般情况，进行循环，检查分割点
        int res = 0;
        for(int k = i; k <= j; ++k)
        {
            int leftCnt = dfs(i, k-1);
            int rightCnt = dfs(k+1, j);
            res += leftCnt * rightCnt;
        }
        // 返回结果
        memo[i-1][j-1] = res;
        return res;
    };
    // 进行调用即可
    return dfs(1, n);
}

// 第三版：完全进化的 DP 方法
int numTreesDP(int n)
{
    // 直接根据上面的 DFS 代码进行仿造即可
    // 之所以要初始化为全1，是因为所有 i > j 的情况都需要记录为有 1 种树，而且数组中的初始值不会影响过程中对其对求解
    vector<vector<int>> dp(n+2, vector<int>(n+2, 1));
    // 注意到本题依然是一个区间类的问题，即所有大的区间在求解的时候，都要求长度更小的区间的结果已知，所以这里我们也按长度进行遍历
    for(int len = 2; len <= n; ++len)
    {
        // 枚举所有区间的起点
        for(int i = 1; i+len-1 <= n; ++i)
        {
            // 计算区间的结尾
            int j = i+len-1;
            // 对区间中的分割点进行进一步枚举
            int tmp = 0;
            for(int k = i; k <= j; ++k)
            {
                tmp += dp[i][k-1]*dp[k+1][j];
            }
            dp[i][j] = tmp;
        }
    }
    // 最后结果就是 dp[1][n];
    return dp[1][n];
}

// 第四版：完全进化的 DP 方法 + 空间优化 
int numTreesDPOpt(int n)
{
    // 其实这个优化不好想，不过确实很巧妙
    // 考虑这样的事实，我们最后要搞出来的是所有可能区间的结果，无所谓这些区间被求解的顺序是怎么样的
    // 只有一个要求：当我们要求一个大区间的时候，它 "需要" 的所有小区间都被求解完成了
    // 这就是压缩空间最关键的一步考虑
    // 上面基于区间 DP 的解法中，我们实际上是为一些大区间提供了必要条件，即我们求出了所有区间长度小于这个大区间的小区间的结果
    // 实际上，这并不是必须的，我们完全可以等到要求解一个大区间的时候，才满足 "它的所有需要的数据都被计算" 这一条件
    // 于是有了下面这样的定义方式
    // dp[i] 代表 [1..i] 这些结点能够构成的不同二叉搜索树个数，这样我们就丢掉了第二个维度，只剩下了一维
    // 我们考虑求解这个大区间的时候，它需要哪些小区间
    // 设分割点为 k
    // 那么它需要的区间就是 [1..k-1] 和 [k+1][i]
    // 那么我们只需要在循环中保证这两个结果总是在我们求解 dp[1..i] 之前被求解就行了
    vector<int> dp(n+2, 1);
    for(int i = 2; i <= n; ++i)
    {
        int tmp = 0;
        for(int j = 1; j <= i; ++j)
        {
            tmp += dp[j-1]*dp[i-j];
        }
        dp[i] = tmp;
    }
    return dp[n];
}