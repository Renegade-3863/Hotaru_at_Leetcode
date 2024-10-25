#include "Solution.h"

// 第一版：暴力 DFS，简单粗暴的 TLE
int Leetcode201_300::Solution::minCostII(vector<vector<int>>& costs)
{
    // 获取颜色的总种类数
    int k = costs[0].size(), n = costs.size();
    // 本质上是 "粉刷房子" 的拓展问题，基本思路没有任何区别，我们依然可以先从自顶向下的 DFS 角度切入
    // 还是定义一个 dfs 回调函数
    // 定义：给前 i 间房子粉刷，最后一间房屋的颜色是 color 色的最少开销
    function<int(int, int)> dfs = [&](int i, int color)
    {
        // 边界情况
        if(i == 1)
        {
            // 这里我们需要获取颜色的所有可能值，我们在回调函数前面获取一下，然后通过传引用的方式传给 dfs 函数体  
            for(int j = 0; j < k; ++j)
            {
                if(color == j)
                {
                    return costs[0][j];
                }
            } 
            // 不会执行到这一行 make the compiler happy
            return -1;
        }
        // 一般情况
        // 我们直接通过 color 的颜色进行循环检查即可
        int minimum = INT_MAX;
        for(int j = 0; j < k; ++j)
        {
            if(j != color)
            {
                minimum = min(minimum, dfs(i-1, j)+costs[i-1][color]);
            }
        }
        return minimum;
    };
    int res = INT_MAX;
    // 循环一轮最后一间房屋的颜色种类，进行深搜即可
    for(int color = 0; color < k; ++color)
    {
        res = min(res, dfs(n, color));
    }
    return res;
}

// 第二版：DFS + 记忆化数组加速，正常通过
int minCostII(vector<vector<int>>& costs)
{
    // 获取颜色的总种类数
    int k = costs[0].size(), n = costs.size();
    // 记录一个记忆化数组
    vector<vector<int>> memo(n, vector<int>(k, -1));
    // 本质上是 "粉刷房子" 的拓展问题，基本思路没有任何区别，我们依然可以先从自顶向下的 DFS 角度切入
    // 还是定义一个 dfs 回调函数
    // 定义：给前 i 间房子粉刷，最后一间房屋的颜色是 color 色的最少开销
    function<int(int, int)> dfs = [&](int i, int color)
    {
        if(memo[i-1][color] != -1)
        {
            return memo[i-1][color];
        }
        // 边界情况
        if(i == 1)
        {
            // 这里我们需要获取颜色的所有可能值，我们在回调函数前面获取一下，然后通过传引用的方式传给 dfs 函数体  
            // 不会执行到这一行 make the compiler happy
            return costs[0][color];
        }
        // 一般情况
        // 我们直接通过 color 的颜色进行循环检查即可
        int minimum = INT_MAX;
        for(int j = 0; j < k; ++j)
        {
            if(j != color)
            {
                minimum = min(minimum, dfs(i-1, j)+costs[i-1][color]);
            }
        }
        memo[i-1][color] = minimum;
        return minimum;
    };
    int res = INT_MAX;
    // 循环一轮最后一间房屋的颜色种类，进行深搜即可
    for(int color = 0; color < k; ++color)
    {
        res = min(res, dfs(n, color));
    }
    return res;
}

// 第三版：自顶向下的 DFS 换成自底向上的 DP 
int minCostII(vector<vector<int>>& costs)
{
    // memo 换成 dp 数组即可，其它基本没区别
    int n = costs.size(), k = costs[0].size();
    vector<vector<int>> dp(n, vector<int>(k, INT_MAX));
    // 边界情况设定
    for(int j = 0; j < k; ++j)
    {
        dp[0][j] = costs[0][j];
    }
    // 进行一般的递推
    for(int i = 1; i < n; ++i)
    {
        for(int color = 0; color < k; ++color)
        {
            // 每一个 color 都需要上一层整个一层的数据
            for(int preColor = 0; preColor < k; ++preColor)
            {
                if(preColor != color)
                {
                    dp[i][color] = min(dp[i][color], dp[i-1][preColor]+costs[i][color]);
                }
            }
        }
    }
    // 返回最终结果，应该是最后一行的最小值
    return *min_element(dp[n-1].begin(), dp[n-1].end());
}

// 第四版：DP + 滚动数组空间优化
int minCostII(vector<vector<int>>& costs)
{
    // 注意到第三版的递推代码中，只涉及到当前层对上一层的数据利用，所以我们可以压缩到只有两行的二维数组进行滚动
    int n = costs.size(), k = costs[0].size();
    vector<vector<int>> dp(2, vector<int>(k, INT_MAX));
    // 初始值设定
    for(int j = 0; j < k; ++j)
    {
        dp[0][j] = costs[0][j];
    }
    for(int i = 1; i < n; ++i)
    {
        for(int color = 0; color < k; ++color)
        {
            int tmpMin = 0x3f3f3f3f;
            for(int preColor = 0; preColor < k; ++preColor)
            {
                // 这里为了避免需要重置 dp[1] 这一行的时间开销，我们用一个临时变量来更新 dp[1][color]
                if(preColor != color)
                {
                    tmpMin = min(tmpMin, dp[0][preColor]+costs[i][color]);
                }
            }
            dp[1][color] = tmpMin;    
        }
        // 还需要把 dp[1] 中的数据复制给 dp[0] 这一行
        copy(dp[1].begin(), dp[1].end(), dp[0].begin());
    }
    return n > 1 ? *min_element(dp[1].begin(), dp[1].end()) : *min_element(dp[0].begin(), dp[0].end());
}