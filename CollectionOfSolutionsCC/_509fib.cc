#include "Solution.h"

int Leetcode501_600::Soltuion::fib(int n)
{
    // 算法入门题，这题不会的可以放弃学算法了
    // 定义递归子问题：
    // dfs(i) 代表斐波那契数列的下标为 i 的项，也可以叫 "第i+1项"
    // 这题就不再从 DFS 入手了，直接给出最终结果
    if(n == 0 || n == 1)
    {
        return n;
    }
    int dp0 = 0, dp1 = 1;
    int cur = 2;
    while(cur++ <= n)
    {
        int tmp = dp1;
        dp1 += dp0;
        dp0 = tmp;
    }
    return dp1;
}