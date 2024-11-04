#include "Solution.h"

// 第一版：暴力 DFS，直接 TLE
int Leetcode301_400::Solution::longestIncreasingPath(vector<vector<int>>& matrix)
{
    // 乍一看有点像 DP，不过我们还是先从 DFS 的角度来看待这个问题
    // 我们定义这样的一个母问题：
    // dfs(i, j) 代表： 从坐标 (i, j) 出发的最长递增路径长度
    // 那么很显然的解法是：dfs(i, j) = max({dfs(i-1, j), dfs(i, j+1), dfs(i+1, j), dfs(i, j-1)})+1
    // 比较抽象的是基本情况的设定
    // 什么时候，我们可以简单地确定结束于一个位置的最长递增路径长度？
    // 隐含条件：一个矩阵，一定会有全局的最大值
    // 那么只要我们走到了这个矩阵中任意一个最大值格(这可以通过向四个方向探查来得知)
    // 这个结点的最长递增路径长度就只能是1，因为它走不出去
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int m = matrix.size(), n = matrix[0].size();
    function<int(int, int)> dfs = [&](int i, int j)
    {
        // 记录四周小于当前结点值的下一跳
        vector<pair<int, int>> nextPos;
        for(int k = 0; k < 4; ++k)
        {
            int nxti = i+dirs[k][0], nxtj = j+dirs[k][1];
            // 检查是否是一个合法的下一跳下标，并且是一个可以递增的位置
            if(nxti >= 0 && nxti < m && nxtj >= 0 && nxtj < n && matrix[nxti][nxtj] > matrix[i][j])
            {
                // 也可以写 nextPos.emplace_back(i+dirs[k][0], j+dirs[k][1])
                nextPos.push_back(make_pair<int, int>(i+dirs[k][0], j+dirs[k][1]));
            }
        }
        // 循环结束后，检查是否有下一跳结点，没有的话直接返回 1
        if(nextPos.size() == 0)
        {
            return 1;
        }
        // 否则，深入递归
        int res = 1;
        for(const auto& nxt: nextPos)
        {
            res = max(res, dfs(nxt.first, nxt.second)+1);
        }
        return res;
    };
    // 我们只需要对每个结点都调用一遍 dfs 函数即可
    int ans = 1;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            ans = max(ans, dfs(i, j));
        }
    }
    return ans;
}

// 第二版：给 DFS 加上记忆化加速
int longestIncreasingPath(vector<vector<int>>& matrix)
{
    // 乍一看有点像 DP，不过我们还是先从 DFS 的角度来看待这个问题
    // 我们定义这样的一个母问题：
    // dfs(i, j) 代表： 从坐标 (i, j) 出发的最长递增路径长度
    // 那么很显然的解法是：dfs(i, j) = max({dfs(i-1, j), dfs(i, j+1), dfs(i+1, j), dfs(i, j-1)})+1
    // 比较抽象的是基本情况的设定
    // 什么时候，我们可以简单地确定结束于一个位置的最长递增路径长度？
    // 隐含条件：一个矩阵，一定会有全局的最大值
    // 那么只要我们走到了这个矩阵中任意一个最大值格(这可以通过向四个方向探查来得知)
    // 这个结点的最长递增路径长度就只能是1，因为它走不出去
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int m = matrix.size(), n = matrix[0].size();
    // 记忆化数组
    vector<vector<int>> memo(m, vector<int>(n, -1));
    function<int(int, int)> dfs = [&](int i, int j)
    {
        if(memo[i][j] != -1)
        {
            return memo[i][j];
        }
        // 记录四周小于当前结点值的下一跳
        vector<pair<int, int>> nextPos;
        for(int k = 0; k < 4; ++k)
        {
            int nxti = i+dirs[k][0], nxtj = j+dirs[k][1];
            // 检查是否是一个合法的下一跳下标，并且是一个可以递增的位置
            if(nxti >= 0 && nxti < m && nxtj >= 0 && nxtj < n && matrix[nxti][nxtj] > matrix[i][j])
            {
                // 也可以写 nextPos.emplace_back(i+dirs[k][0], j+dirs[k][1])
                nextPos.push_back(make_pair<int, int>(i+dirs[k][0], j+dirs[k][1]));
            }
        }
        // 循环结束后，检查是否有下一跳结点，没有的话直接返回 1
        if(nextPos.size() == 0)
        {
            memo[i][j] = 1;
            return 1;
        }
        // 否则，深入递归
        int res = 1;
        for(const auto& nxt: nextPos)
        {
            res = max(res, dfs(nxt.first, nxt.second)+1);
        }
        memo[i][j] = res;
        return res;
    };
    // 我们只需要对每个结点都调用一遍 dfs 函数即可
    int ans = 1;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            ans = max(ans, dfs(i, j));
        }
    }
    return ans;
}

// 第三版：把自顶向下的 DFS 改成自底向上的 DP
int longestIncreasingPath(vector<vector<int>>& matrix)
{
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    // 初始化边界情况
    
}