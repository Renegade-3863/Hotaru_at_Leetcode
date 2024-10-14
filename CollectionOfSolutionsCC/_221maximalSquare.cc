#include "Solution.h"

// 单纯的 DFS，可以预见的超时
int Leetcode201_300::Solution::maximalSquare(vector<vector<char>>& matrix)
{
    // 依然是一种类似动态规划的，含有重叠子问题和最优子结构性质的问题
    // 我们还是考虑先用 DFS 来实现一遍
    // 定义如下的子问题：dfs(i, j) 返回的是右下角结束于位置 (i, j) 处的最大正方形的边长
    // 那么我们可以发现下面的递推关系：
    // 1. 当前格子上方的格子存在一个最大的正方形，那么我们显然可以把它 "平移" 一步下来，形成一个新的最大正方形
    // 注意，这里是否能够平移会受到 (i, j) 这个格子左侧的一排格子的限制，即：它们是否为全1
    // 这可以视作是 dfs(i, j-1) 的限制，也就是，结束于左侧格子的最大正方形
    // 那么我们可以 "平移" 下来的最大的正方形就只有 min(dfs(i-1, j), dfs(i, j-1)) 这么大
    // 2. 当前格子左侧的格子存在一个最大的正方形，那么我们也显然可以把它 "平移" 一步向右，形成一个新的最大正方形
    // 分析过程同情况1:
    // 是 min(dfs(i, j-1), dfs(i-1, j)) 这么大
    // 注意：上面的分析其实不是完全正确的，因为左侧和上方的两个正方形，可能均比较大，而我们想要把它们平移向右，或者平移下来，还需要保证左上角的一块区域为全1
    // 这可以通过 dfs(i-1, j-1) 来进行判断，即：原本的左上角是否还有足够的1让我们执行上面两种 "平移"
    // 如果没有，那么我们只能 "平移" 满足左上角那些1个数那么大的正方形
    // 最终，得出的递推关系就变成了：dfs(i, j) = min(min(dfs(i-1, j), dfs(i, j-1)), dfs(i-1, j-1)) + 1
    // 根据上面的递推关系就可以写出 DFS 代码了
    function<int(int, int)> dfs = [&](int i, int j)
    {
        // 基本情况1. 要探查的范围只有一个方格，我们可以简单计算并返回结果
        // 基本情况2. 要探查的范围是一条宽度为1的竖直长方形/水平长方形
        // 两种情况可以合并，因为情况2也可以通过当前格子是否为 '1' 来判断是否能构成一个唯一的面积为1的正方形
        if(i == 0 || j == 0)
        {
            return matrix[i][j] == '1' ? 1 : 0;
        }
        // 递归情况：根据上面的公式进行递推即可
        if(matrix[i][j] != '1')
        {
            return 0;
        }
        return min(min(dfs(i-1, j), dfs(i, j-1)), dfs(i-1, j-1))+1;
    };
    // 调用函数计算出最大正方形的边长
    int m = matrix.size(), n = matrix[0].size();
    // 记录全局的最大值
    int maxRes = 0;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            maxRes = max(dfs(i, j), maxRes);
        }
    }
    return maxRes * maxRes;
}

// 第二版：DFS + 记忆化，可以通过
int maximalSquareMemo(vector<vector<char>>& matrix)
{
    // 依然是一种类似动态规划的，含有重叠子问题和最优子结构性质的问题
    // 我们还是考虑先用 DFS 来实现一遍
    // 定义如下的子问题：dfs(i, j) 返回的是右下角结束于位置 (i, j) 处的最大正方形的边长
    // 那么我们可以发现下面的递推关系：
    // 1. 当前格子上方的格子存在一个最大的正方形，那么我们显然可以把它 "平移" 一步下来，形成一个新的最大正方形
    // 注意，这里是否能够平移会受到 (i, j) 这个格子左侧的一排格子的限制，即：它们是否为全1
    // 这可以视作是 dfs(i, j-1) 的限制，也就是，结束于左侧格子的最大正方形
    // 那么我们可以 "平移" 下来的最大的正方形就只有 min(dfs(i-1, j), dfs(i, j-1)) 这么大
    // 2. 当前格子左侧的格子存在一个最大的正方形，那么我们也显然可以把它 "平移" 一步向右，形成一个新的最大正方形
    // 分析过程同情况1:
    // 是 min(dfs(i, j-1), dfs(i-1, j)) 这么大
    // 注意：上面的分析其实不是完全正确的，因为左侧和上方的两个正方形，可能均比较大，而我们想要把它们平移向右，或者平移下来，还需要保证左上角的一块区域为全1
    // 这可以通过 dfs(i-1, j-1) 来进行判断，即：原本的左上角是否还有足够的1让我们执行上面两种 "平移"
    // 如果没有，那么我们只能 "平移" 满足左上角那些1个数那么大的正方形
    // 最终，得出的递推关系就变成了：dfs(i, j) = min(min(dfs(i-1, j), dfs(i, j-1)), dfs(i-1, j-1)) + 1
    // 根据上面的递推关系就可以写出 DFS 代码了
    // 添加一个记忆化数组即可
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> memo(m, vector<int>(n, -1));
    function<int(int, int)> dfs = [&](int i, int j)
    {
        if(memo[i][j] != -1)
        {
            return memo[i][j];
        }
        // 基本情况1. 要探查的范围只有一个方格，我们可以简单计算并返回结果
        // 基本情况2. 要探查的范围是一条宽度为1的竖直长方形/水平长方形
        // 两种情况可以合并，因为情况2也可以通过当前格子是否为 '1' 来判断是否能构成一个唯一的面积为1的正方形
        if(i == 0 || j == 0)
        {
            memo[i][j] = matrix[i][j] == '1' ? 1 : 0;
            return memo[i][j];
        }
        // 递归情况：根据上面的公式进行递推即可
        if(matrix[i][j] != '1')
        {
            return 0;
        }
        memo[i][j] = min(min(dfs(i-1, j), dfs(i, j-1)), dfs(i-1, j-1))+1;
        return memo[i][j];
    };
    // 调用函数计算出最大正方形的边长
    // 记录全局的最大值
    int maxRes = 0;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            maxRes = max(dfs(i, j), maxRes);
        }
    }
    return maxRes * maxRes;
}

// 第三版：完全优化的 DP 方案
int maximalSquareDP(vector<vector<char>>& matrix)
{
    // 基于前两版的 DFS 方案，优化出自底向上的 DP 解法
    // 初始化 DP 数组
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    // 全局最大值
    int maxRes = 0;
    for(int i = 0; i < m; ++i)
    {
        dp[i][0] = matrix[i][0] == '1' ? 1 : 0;
        maxRes = max(maxRes, dp[i][0]);
    }
    for(int j = 1; j < n; ++j)
    {
        dp[0][j] = matrix[0][j] == '1' ? 1 : 0;
        maxRes = max(maxRes, dp[0][j]);
    }
    
    for(int i = 1; i < m; ++i)
    {
        for(int j = 1; j < n; ++j)
        {
            // 和上面的 DFS 过程是相同的递推方法
            dp[i][j] = matrix[i][j] == '1' ? min(min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1])+1 : 0;
            maxRes = max(maxRes, dp[i][j]);
        }
    }
    return maxRes * maxRes;
}

// 第四版：尝试优化 DP 的空间复杂度
int maximalSquareDPOpt(vector<vector<char>>& matrix)
{
    // 优化二维数组为一维的滚动数组
    int m = matrix.size(), n = matrix[0].size();
    vector<int> dp(n, 0);
    // 全局最大值
    int maxRes = 0;
    // 初始化第一行的信息
    for(int j = 0; j < n; ++j)
    {
        dp[j] = matrix[0][j] == '1' ? 1 : 0;
        maxRes = max(maxRes, dp[j]);
    }
    // 之后逐行进行滚动更新

    for(int i = 1; i < m; ++i)
    {
        // 记录 dp[j-1] 数据的临时变量
        int tmp1 = dp[0];
        dp[0] = matrix[i][0] == '1' ? 1 : 0;
        maxRes = max(maxRes, dp[0]);
        for(int j = 1; j < n; ++j)
        {
            int tmp2 = dp[j];
            dp[j] = matrix[i][j] == '1' ? min(min(dp[j-1], dp[j]), tmp1)+1 : 0;
            maxRes = max(maxRes, dp[j]);
            // 更新 tmp1
            tmp1 = tmp2;
        }
    }
    // 返回计算得出的结果即可
    return maxRes * maxRes;
}