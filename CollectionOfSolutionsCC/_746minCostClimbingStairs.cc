#include "Solution.h"

int Leetcode701_800::Soltuion::minCostClimbingStairs(vector<int>& cost)
{
    // 简单的 DP 基础题，我们就不写 DFS 版本了
    // 定义 dp[i] 代表爬到第 i 个台阶所需的最少费用
    // 题目允许我们从下标为 0 或者下标为 1 的台阶开始爬
    // 所以我们可以考虑跑两次 DP 算法
    // 第一次计算下标 0 开始的结果
    // 第二次计算下标 1 开始的结果
    int n = cost.size();
    vector<int> dp(n+1, 0);
    // 初始化边界值
    // dp[0] 应该就是 0，因为我们一开始就在下标 0 上，不需要任何费用就可以达到
    // dp[1] 应该是 cost[0]，因为我们一开始在下标 0 上，而要到达下标 1，只能从下标 0 爬过来
    dp[1] = cost[0];
    // 如何递推？
    // 很明显：下标 i 可以从 i-2 和 i-1 爬过来
    // 故 dp[i] = min(dp[i-2]+cost[i-2], dp[i-1]+cost[i-1])
    for(int i = 2; i <= n; ++i)
    {
        dp[i] = min(dp[i-2]+cost[i-2], dp[i-1]+cost[i-1]);
    }
    vector<int> dp2(n+1, 0);
    // 初始化边界值
    dp2[2] = cost[1];
    for(int i = 3; i <= n; ++i)
    {
        dp2[i] = min(dp2[i-2]+cost[i-2], dp2[i-1]+cost[i-1]);
    }
    return min(dp[n], dp2[n]);
}