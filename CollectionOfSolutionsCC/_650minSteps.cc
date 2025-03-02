#include "Solution.h"

int Leetcode601_700::Soltuion::minSteps(int n)
{
    // 一眼看就知道是 DP 类问题
    // 问题是如何定义状态子问题
    // 我们可以定义：
    // dfs(i, j) 代表要构建出 i 个 'A'，而当前粘贴板上有 j 个 'A' 的状态
    // 所需要的最少步数
    // 那么我们可以有两种递推的方法
    // 1. 如果 i == j，那么我们可以探讨上一步是 "Copy All" 的情况
    // 也就是 dfs(i, j) = {for all k from 0 to i, min(dfs(i, k))} +1
    // 注意：情况 1 我们只有在 i == j 的情况下才能考虑这种情况
    // 2. 我们可以讨论上一步是 "Paste" 的情况
    // 那么递推关系就是：dfs(i, j) = min(dfs(i, j), dfs(i-j, j)+1)
    // 综合考虑上述两种情况，我们取最小值，就拿到了最后的结果
    // 最后，我们的综合结果就是
    // 枚举所有 j 值的最小值
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 考虑基本情况：
        // i < j 的情况是不合法的，返回 0x3f3f3f3f 即可
        if(i < j)
        {
            return 0x3f3f3f3f;
        }
        // 如果 i == 1 或者 i == 0，那么我们直接返回 j 即可
        // 因为最开始就有一个 'A'
        if(i == 1 || i == 0)
        {
            return j;
        }
        // 如果 j == 0，那么我们只在 i == 1 的时候能返回 0，其它情况下只能返回 0x3f3f3f3f 这个极大值
        if(j == 0)
        {
            return i == 1 ? 0 : 0x3f3f3f3f;
        }
        // 其它情况下，我们考虑上面讨论的两种递推关系即可
        int res = 0x3f3f3f3f;
        if(i == j)
        {
            // 此时讨论情况 1.
            for(int k = 0; k < i; ++k)
            {
                res = min(res, dfs(i, k)+1);
            }
        }
        // 之后，讨论情况 2.
        res = min(res, dfs(i-j, j)+1);
        return res;
    };
    // 枚举所有可能的 j
    int ans = 0x3f3f3f3f;
    for(int j = 0; j < n; ++j)
    {
        ans = min(ans, dfs(n, j));
    }
    return ans;
}

// 第二版：给方案加上记忆化模块
int minSteps(int n)
{
    
}