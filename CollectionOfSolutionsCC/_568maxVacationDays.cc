#include "Solution.h"

// 第一版，暴力 DFS，超时 TLE
int Leetcode501_600::Soltuion::maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days)
{
    /*
        0 1 1
        1 0 1
        1 1 0
    */
    // 我们按照状态机 DP 的方式来处理这个问题
    // 定义下面的子问题：
    // dfs(i, j) 代表，第 j 周结束停留在城市 i 的条件下，员工可以游玩的最大天数
    int n = flights.size(), m = days[0].size();
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 考虑递推关系和基本情况
        // 最基本的情况是：如果 j == m-1，此时我们直接返回 days[i][j] 即可
        if(j == m+1)
        {
            return 0;
        }
        // 考虑如何进行情况递推
        // 我们可以考虑下一周停留在了哪座城市
        // 我们遍历整个数组，检查 flights 的第 i 行，检查所有从城市 i 可达的下一座城市，取出下一座可能的城市 k，并递归检查 dfs(k, j+1) 的结果
        // 注意，flights 数组本身的下标相对 i 本身有位移，所以需要加上 offset
        int res = 0;
        for(int k = 0; k < n; ++k)
        {
            if(flights[i-1][k])
            {
                // 有航班，那么我们递归检查
                // 我们递归更新 res 的结果
                // 当前情况下的最大结果为：下一周 (j+1 周) 停留在第 k+1 座城市时，可以休息的最多天数，再加上当前这一周在城市 i 休息的情况
                res = max(res, dfs(k+1, j+1)+days[k][j-1]);
            }
        }
        // 还有额外一种情况，我们不飞，还留在本市
        res = max(res, dfs(i, j+1)+days[i-1][j-1]);
        return res;
    };
    return dfs(1, 1);
}

// 第二版：添加记忆化加速
int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days)
{
    /*
        0 1 1
        1 0 1
        1 1 0
    */
    // 我们按照状态机 DP 的方式来处理这个问题
    // 定义下面的子问题：
    // dfs(i, j) 代表，第 j 周结束停留在城市 i 的条件下，员工可以游玩的最大天数
    int n = flights.size(), m = days[0].size();
    // 添加一个记忆化数组
    vector<vector<int>> memo(n, vector<int>(m, -1));
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 考虑递推关系和基本情况
        // 最基本的情况是：如果 j == m-1，此时我们直接返回 days[i][j] 即可
        if(j == m+1)
        {
            return 0;
        }
        // 记忆化加速
        if(memo[i-1][j-1] != -1)
        {
            return memo[i-1][j-1];
        }
        // 考虑如何进行情况递推
        // 我们可以考虑下一周停留在了哪座城市
        // 我们遍历整个数组，检查 flights 的第 i 行，检查所有从城市 i 可达的下一座城市，取出下一座可能的城市 k，并递归检查 dfs(k, j+1) 的结果
        // 注意，flights 数组本身的下标相对 i 本身有位移，所以需要加上 offset
        int res = 0;
        for(int k = 0; k < n; ++k)
        {
            if(flights[i-1][k])
            {
                // 有航班，那么我们递归检查
                // 我们递归更新 res 的结果
                // 当前情况下的最大结果为：下一周 (j+1 周) 停留在第 k+1 座城市时，可以休息的最多天数，再加上当前这一周在城市 i 休息的情况
                res = max(res, dfs(k+1, j+1)+days[k][j-1]);
            }
        }
        // 还有额外一种情况，我们不飞，还留在本市
        res = max(res, dfs(i, j+1)+days[i-1][j-1]);
        memo[i-1][j-1] = res;
        return res;
    };
    return dfs(1, 1);
}

// 第三版：把自顶向下的 DFS 改成自底向上的 DP
int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days)
{
    int m = days[0].size(), n = flights.size();
    // dp[i][j] 代表的是，第 j+1 周停留在第 i+1 个城市的情况下，后续可以休息的最长时间
    vector<vector<int>> dp(n+2, vector<int>(m+2, 0));
    // 初始化完成，我们接下来要进行递推处理
    for(int j = m; j >= 1; --j)
    {
        for(int i = n; i >= 1; --i)
        {
            // 每一个 dp[i][j]，我们进行和上面 DFS 类似的处理方法
            for(int k = 0; k < n; ++k)
            {
                if(flights[i-1][k])
                {
                    dp[i][j] = max(dp[i][j], dp[k+1][j+1]+days[k][j-1]);
                }
            }
            dp[i][j] = max(dp[i][j], dp[i][j+1]+days[i-1][j-1]);
        }
    }
    return dp[1][1];
}
