#include "Solution.h"

// 第一版：暴力 DFS，不出意料的 TLE
int Leetcode101_200::Solution::minimumTotal(vector<vector<int>>& triangle)
{
    // 实不相瞒，遇到这种 "路径和"，"最小" 的字眼，其实做到现在，第一反应就应该是动态规划了
    // 至于具体的状态转移方程，还是老办法，我们不直接想自底向上的方案，先考虑自顶向下的方法
    // 定义如下的递归回调函数：
    // dfs(i, j) 代表到三角形中坐标为 (i, j) 位置处的结点可得的最小路径和
    // 那么基于这个定义，我们不难发现下面的最优子结构性质：
    // 如果要求的是 dfs(i, j)，由于这个值是最小路径和，因而所有下一跳能够到达坐标 (i, j) 的原坐标 (即(i-1, j-1)和(i-1, j)) 都必须是路径和最小的
    // 否则一定可以找出一条路径和更小的前一跳坐标，使得 dfs(i, j) 更小
    // 重叠子问题性质应该这样想
    // 我们在利用 dfs(i-1, j-1) 和 dfs(i-1, j) 的时候，它们的值均已经包含了所有能够到达它们的更小子路径的路径和，因而只需要考虑这两个值本身即可，更小的子问题无需考虑
    // 之后我们就不难写出单纯的不带剪枝的 DFS 了
    function<int(int, int)> dfs = [&](int i, int j) 
    {
        // 注意递归结束条件的设置
        // 当 j < 0 || i < 0 的时候，我们在尝试访问一个不存在的坐标，这时候只需要返回一个代表无限大的值，即不存在路径，也不存在对应路径和
        if(i < 0 || j < 0)
        {
            return 0x3f3f3f3f;
        }
        // 或者 j 的值超出了当前行的坐标域，也要返回0
        if(j >= triangle[i].size())
        {
            return 0x3f3f3f3f;
        }
        // 否则，根据 (i-1, j-1) 和 (i-1, j) 坐标处的信息对 dfs(i, j) 进行计算
        int cmp = min(dfs(i-1, j-1), dfs(i-1, j));
        return (cmp == 0x3f3f3f3f ? 0 : cmp) + triangle[i][j];
    };
    // 进行函数调用即可
    // 注意，我们需要计算的是最后一层上所有坐标的结果和
    int m = triangle.size();
    int n = triangle[m-1].size();
    int res = INT_MAX;
    for(int k = 0; k < n; ++k)
    {
        res = min(res, dfs(m-1, k));
    }
    return res;
}

// 第二版：DFS + 记忆化，可以通过
int minimumTotalMemo(vector<vector<int>>& triangle)
{
    // 实不相瞒，遇到这种 "路径和"，"最小" 的字眼，其实做到现在，第一反应就应该是动态规划了
    // 至于具体的状态转移方程，还是老办法，我们不直接想自底向上的方案，先考虑自顶向下的方法
    // 定义如下的递归回调函数：
    // dfs(i, j) 代表到三角形中坐标为 (i, j) 位置处的结点可得的最小路径和
    // 那么基于这个定义，我们不难发现下面的最优子结构性质：
    // 如果要求的是 dfs(i, j)，由于这个值是最小路径和，因而所有下一跳能够到达坐标 (i, j) 的原坐标 (即(i-1, j-1)和(i-1, j)) 都必须是路径和最小的
    // 否则一定可以找出一条路径和更小的前一跳坐标，使得 dfs(i, j) 更小
    // 重叠子问题性质应该这样想
    // 我们在利用 dfs(i-1, j-1) 和 dfs(i-1, j) 的时候，它们的值均已经包含了所有能够到达它们的更小子路径的路径和，因而只需要考虑这两个值本身即可，更小的子问题无需考虑
    // 之后我们就不难写出单纯的不带剪枝的 DFS 了
    // 添加一个记忆化数组
    int m = triangle.size();
    int n = triangle[m-1].size();
    vector<vector<int>> memo;
    // 按行进行复制
    for(int i = 0; i < m; ++i)
    {
        memo.push_back(vector<int>(triangle[i].size(), 0x3f3f3f3f));
    }
    function<int(int, int)> dfs = [&](int i, int j) 
    {
        // 注意递归结束条件的设置
        // 当 j < 0 || i < 0 的时候，我们在尝试访问一个不存在的坐标，这时候只需要返回一个代表无限大的值，即不存在路径，也不存在对应路径和
        if(i < 0 || j < 0)
        {
            return 0x3f3f3f3f;
        }
        // 或者 j 的值超出了当前行的坐标域，也要返回0
        if(j >= triangle[i].size())
        {
            return 0x3f3f3f3f;
        }
        if(memo[i][j] != 0x3f3f3f3f)
        {
            return memo[i][j];
        }
        // 否则，根据 (i-1, j-1) 和 (i-1, j) 坐标处的信息对 dfs(i, j) 进行计算
        int cmp = min(dfs(i-1, j-1), dfs(i-1, j));
        memo[i][j] = (cmp == 0x3f3f3f3f ? 0 : cmp) + triangle[i][j];
        return memo[i][j];
    };
    // 进行函数调用即可
    // 注意，我们需要计算的是最后一层上所有坐标的结果和
    int res = INT_MAX;
    for(int k = 0; k < n; ++k)
    {
        res = min(res, dfs(m-1, k));
    }
    return res;
}

// 第三版：完全优化的 DP 方案
int minimumTotalDP(vector<vector<int>>& triangle)
{
    int m = triangle.size();
    vector<vector<int>> dp;
    // 按行复制 DP 数组
    for(int i = 0; i < m; ++i)
    {
        dp.push_back(vector<int>(triangle[i].size(), 0x3f3f3f3f));
    }
    // 直接进行递推即可，根据下标有效性进行递推
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < triangle[i].size(); ++j)
        {
            if(i == 0)
            {
                dp[i][j] = triangle[i][j];
            }
            // i > 0
            else if(j == 0)
            {
                dp[i][j] = triangle[i][j]+dp[i-1][j];
            }
            // i > 0 && j > 0 && j >= triangle[i-1].size()
            else if(j >= triangle[i-1].size())
            {
                dp[i][j] = triangle[i][j]+dp[i-1][j-1];
            }
            // i > 0 && j > 0 && j < triangle[i-1].size()
            else 
            {
                dp[i][j] = min(dp[i-1][j], dp[i-1][j-1]) + triangle[i][j];
            }
        }
    }
    int res = INT_MAX;
    for(int j = 0; j < triangle[m-1].size(); ++j)
    {
        res = min(res, dp[m-1][j]);
    }
    return res;
}

// 第四版：完全优化的 DP 方案 + 空间优化
int minimumTotalDPOpt(vector<vector<int>>& triangle)
{
    // 注意到上面填表的过程同样不会用到某个位置前面所有的元素，因而可以进行空间压缩
    int m = triangle.size();
    // dp 数组压缩成一维
    vector<int> dp;
    int memo = 0;
    // 直接进行递推
    for(int i = 0; i < m; ++i)
    {
        // 每个下一行只会比上一行多一个位置，我们把这个位置置为 0x3f3f3f3f 即可
        dp.push_back(0x3f3f3f3f);
        memo = dp[0];
        // 对数组进行更新
        for(int j = 0; j < triangle[i].size(); ++j)
        {
            // 更新逻辑本体和上面是一致的
            if(i == 0)
            {
                dp[j] = triangle[i][j];
            }
            // i > 0
            else if(j == 0)
            {
                dp[j] = triangle[i][j]+dp[j];
            }
            // i > 0 && j > 0 && j >= triangle[i-1].size()
            else if(j >= triangle[i-1].size())
            {
                int tmp = dp[j];
                dp[j] = triangle[i][j]+memo;
                memo = tmp;
            }
            // i > 0 && j > 0 && j < triangle[i-1].size()
            else
            {
                int tmp = dp[j];
                dp[j] = triangle[i][j]+min(memo, dp[j]);
                memo = tmp;
            }
        }
    }
    int res = INT_MAX;
    for(int j = 0; j < dp.size(); ++j)
    {
        res = min(res, dp[j]);
    }
    return res;
}