#include "Solution.h"

int Leetcode501_600::Soltuion::longestLine(vector<vector<int>>* mat)
{
    // 经典的 DFS 类问题
    // 我们可以有两种定义子问题的方法
    // 1. 简单定义法：
    // 定义 dfs(i, j, k) 为从坐标 (i, j) 出发，往 k 方向走，可以得到的最长连续 1 线段长度
    // 我们先按第一版写一下 (55/56，超时)：
    // 定义八个方向的数组
    const int dirs[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};
    int m = mat.size(), n = mat[0].size();
    function<int(int, int, int)> dfs = [&](int i, int j, int dir) -> int
    {
        // 定义一个基本情况：
        // 如果 mat[i][j] 是 0，那么很明显从这个位置出发的连续 1 线段长度就是 0
        if(mat[i][j] == 0)
        {
            return 0;
        }
        // 其它情况下，我们可以向八个方向运动
        int res = 1;
        int nxtx = i+dirs[dir][0], nxty = j+dirs[dir][1];
        // 确保新坐标合法
        if(nxtx < 0 || nxtx >= m || nxty < 0 || nxty >= n)
        {
            // 注意，此时 mat[i][j] 本身也是一个 1 格，所以我们需要返回 1 作为结果
            return 1;
        }
        // 合法坐标，我们进行递归调用
        res = max(dfs(nxtx, nxty, dir)+1, res);
        return res;
    };
    // 直接调用即可
    int ans = 0;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(mat[i][j] == 0)
            {
                continue;
            }
            for(int k = 0; k < 8; ++k)
            {
                ans = max(ans, dfs(i, j, k));
            }
        }
    }
    return ans;
}

int longestLine(vector<vector<int>>& mat)
{
    // 第二版，我们修改一下 DFS 定义，以更贴近 DP 的方法来定义这个子问题
    // dfs 定义修改成：
    // dfs(i, j, k) 为从左上或者右上方到达 (i, j) 格处，并且方向为 k 的情况下的最长线段长度
    int m = mat.size(), n = mat[0].size();
    // 初始化一个记忆化数组，用于记录已经查找过的结果，如果值为 -1，代表没有检查过这一结果
    vector<vector<vector<int>>> memo(m, vector<vector<int>>(n, vector<int>(4, -1)));
    // 四个方向数组，跟下面的 1234 四种情况一一对应
    const int dirs[4][2] = {{0, -1}, {-1, -1}, {-1, 0}, {1, -1}};
    function<int(int, int, int)> dfs = [&](int i, int j, int dir) -> int
    {
        if(memo[i][j][dir] != -1)
        {
            // 已经检查过了，直接返回结果即可
            return memo[i][j][dir];
        }
        if(mat[i][j] == 0)
        {
            return 0;
        }
        // 否则，还没检查过这一情况，我们需要进行递归检查
        // 我们考虑这样的检查方式：
        // 对于当前格子，无非有四种可以到达它的 "连续 1 序列"
        // 1. 从正左边到达
        // 2. 从左上方到达
        // 3. 从正上方到达
        // 4. 从右上方到达
        // 另外八种情况和上面这四种情况是重复的
        // 我们只检查上面这四种情况即可
        // 对于情况1. 我们检查当前格子的左上格是否为 1，如果是，那么我们可以对当前格的结果进行更新
        int res = 1;
        int nxtx = i+dirs[dir][0], nxty = j+dirs[dir][1];
        // 我们现在要做的就是对 (nxtx, nxty) 进行合法性和为 1 性进行检查
        if(nxtx < 0 || nxtx >= m || nxty < 0 || nxty >= n)
        {
            return res;
        }
        // 检查 (nxtx, nxty) 是否为 1
        if(mat[nxtx][nxty])
        {
            memo[nxtx][nxty][dir] = dfs(nxtx, nxty, dir);
            res = max(res, 1+memo[nxtx][nxty][dir]);
        }
        return res;
    };
    // 我们遍历检查每一个格子即可
    int ans = 0;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            for(int dir = 0; dir < 4; ++dir)
            {
                ans = max(ans, dfs(i, j, dir));
            }
        }
    }
    return ans;
}

// 第三版，记忆化 DFS 转 DP
int longestLine(vector<vector<int>>& mat)
{
    // 观察上面的递推关系式，会发现按层进行遍历就可以完成自顶向下到自底向上的转化
    // 定义一个 DP 数组，记录上面定义的三维 (实际是二维) 数组的信息
    int m = mat.size(), n = mat[0].size();
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(4, 0)));
    const int dirs[4][2] = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
    // 所有元素初始化为 0 
    int res = 0;
    // 把上边界、右边界所有为 1 的格子进行初始化，初始化为 1
    for(int i = 0; i < m; ++i)
    {
        if(mat[i][0] == 1)
        {
            dp[i][0][0] = dp[i][0][1] = dp[i][0][2] = dp[i][0][3] = 1;
            res = 1;
        }
    }
    for(int j = 0; j < n; ++j)
    {
        if(mat[0][j] == 1)
        {
            dp[0][j][0] = dp[0][j][1] = dp[0][j][2] = dp[0][j][3] = 1;
            res = 1;
        }
    }
    // 我们从左往右、从上到下逐步进行遍历，填表即可
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            // 对于每个元素，我们优先检查 mat[i][j] 是否为 1
            if(mat[i][j] == 0)
            {
                // 如果是 0，那么直接跳过即可，不用管了
                continue;
            }
            // 否则，从左、左上、正上以及右上四个方向检查可能的结果
            for(int k = 0; k < 4; ++k)
            {
                int nxtx = i+dirs[k][0], nxty = j+dirs[k][1];
                // 如果 (nxtx, nxty) 不是合法点，也可以跳过
                if(nxtx < 0 || nxtx >= m || nxty < 0 || nxty >= n)
                {
                    continue;
                }
                // 是合法点，那么我们进行 dp 检查
                dp[i][j][k] = dp[nxtx][nxty][k]+1;
                res = max(res, dp[i][j][k]);
            }
        }
    }
    // 返回结果
    return res; 
}