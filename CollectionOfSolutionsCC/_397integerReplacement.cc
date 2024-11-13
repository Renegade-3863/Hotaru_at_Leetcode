#include "Solution.h"

int Leetcode301_400::Solution::integerReplacement(int n)
{
    // 更明显的 DP 问题了，我们先考虑用 DFS 写
    // 我们定义子问题：
    // dfs(i) 代表把 i 这个数变换成 1 所需的最少替换次数
    // 那么如果 i 是偶数，我们有 dfs(i) = dfs(n/2) + 1;
    // 如果 i 是奇数，我们有 dfs(i) = min(dfs(n+1), dfs(n-1))+1;
    // 写代码！
    function<int(int)> dfs = [&](int i) -> int
    {
        // 基本情况：i == 1
        // 此时返回零即可
        if(i == 1)
        {
            return 0;
        }
        if(i % 2)
        {
            // 奇数
            // 这里傻瓜式写法会溢出，看了眼题解，学到了很巧妙的 "多走一步" 方法来避免溢出
            // return min(dfs(i+1), dfs(i-1))+1;
            // 因为奇数探查的下一个数一定是偶数，这个偶数一定会走 dfs((i+1)/2) 或 dfs((i-1)/2)
            // 所以我们可以考虑进行转换：
            return 1+min(dfs(i/2+1)+1, dfs(i/2)+1);
        }
        // 偶数
        return dfs(i/2)+1;
    };
    return dfs(n);
}

// 第二版：DFS + 记忆化
int integerReplacement(int n)
{
    // 更明显的 DP 问题了，我们先考虑用 DFS 写
    // 我们定义子问题：
    // dfs(i) 代表把 i 这个数变换成 1 所需的最少替换次数
    // 那么如果 i 是偶数，我们有 dfs(i) = dfs(n/2) + 1;
    // 如果 i 是奇数，我们有 dfs(i) = min(dfs(n+1), dfs(n-1))+1;
    // 写代码！
    // 记忆化数组
    unordered_map<int, int> memo;
    function<int(int)> dfs = [&](int i) -> int
    {
        // 基本情况：i == 1
        // 此时返回零即可
        if(i == 1)
        {
            return 0;
        }
        if(memo.find(i) != memo.end())
        {
            return memo[i];
        }
        if(i % 2)
        {
            // 奇数
            // 这里傻瓜式写法会溢出，看了眼题解，学到了很巧妙的 "多走一步" 方法来避免溢出
            // return min(dfs(i+1), dfs(i-1))+1;
            // 因为奇数探查的下一个数一定是偶数，这个偶数一定会走 dfs((i+1)/2) 或 dfs((i-1)/2)
            // 所以我们可以考虑进行转换：
            memo[i] = 1+min(dfs(i/2+1)+1, dfs(i/2)+1);
            return memo[i];
        }
        // 偶数
        memo[i] = dfs(i/2)+1;
        return memo[i];
    };
    return dfs(n);
}

