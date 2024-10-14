#include "Solution.h"

// 第一版：简单的纯 DFS，简单的直接 TLE
int Leetcode201_300::Solution::rob(vector<int>& nums)
{
    int n = nums.size();
    // 本题是打家劫舍类问题的第一种变体，在基础的条件上添加了一个额外条件
    // 整列房屋是成一个环的，也就是说，此时不能同时偷窃第一个房屋和最后一个房屋。
    // 我们依然可以考虑 DFS 的策略：
    // 定义一个递归的函数体：
    // 1. 当前没偷过第一间房屋，那么此时 dfs(i, false) 代表没偷过第一间房屋的情况下，偷窃前 i 间房屋可以获得的最大收益
    // 2. 当前偷过第一间房屋，那么此时 dfs(i, true) 代表偷过第一间房屋的情况下，偷窃前 i 间房屋可以获得的最大收益
    // 写出下面的递归函数：
    function<int(int, bool)> dfs = [&](int i, bool flag) -> int
    {
        // 边界情况1. 没有一间房子要偷，此时收益显然是0
        if(i == 0)
        {
            return 0;
        }
        // 边界情况2. 只有一间房子要偷，此时我们需要根据 flag 的值来判断是偷还是不偷
        if(i == 1)
        {
            return flag ? nums[0] : 0;
        }
        // 边界情况3. 当前检查的是前 n 间房子， 那么此时第一间房子偷窃与否就会和我们当前的判断有关了，需要考虑进来
        if(i == n)
        {
            // 如果第一间房子被偷了，那么这最后一间房子我们就一定不能偷，所以结果是 dfs(i-1, true)，即偷窃前 n-1 间房子，并且偷第一间房，可以拿到的最大收益
            // 如果不偷第一间房子，那么这最后一间房子我们也是可以偷的，所以结果是 max(dfs(i-1, false), dfs(i-2, false)+nums[i-1])
            // 即：此时决定不偷最后一间，而第一间房也不偷，可以偷到的最大收益
            // 和此时决定偷最后一间可以偷到的最大收益，二者的较大值
            return flag ? dfs(i-1, true) : max(dfs(i-1, false), dfs(i-2, false)+nums[i-1]);
        }
        // 正常递归情况：
        return max(dfs(i-1, flag), dfs(i-2, flag)+nums[i-1]);
    };
    // 明确了上面的递归过程，我们只需要在下面进行函数调用即可
    // 注意调用的时候，需要分第一间房是否偷分两种情况
    return max(dfs(n, false), dfs(n, true));
}

// 第二版：添加记忆化数组，避免重复递归，可以正常通过
int robMemo(vector<int>& nums)
{
    int n = nums.size();
    // 本题是打家劫舍类问题的第一种变体，在基础的条件上添加了一个额外条件
    // 整列房屋是成一个环的，也就是说，此时不能同时偷窃第一个房屋和最后一个房屋。
    // 我们依然可以考虑 DFS 的策略：
    // 定义一个递归的函数体：
    // 1. 当前没偷过第一间房屋，那么此时 dfs(i, false) 代表没偷过第一间房屋的情况下，偷窃前 i 间房屋可以获得的最大收益
    // 2. 当前偷过第一间房屋，那么此时 dfs(i, true) 代表偷过第一间房屋的情况下，偷窃前 i 间房屋可以获得的最大收益
    // 写出下面的递归函数：
    // 把 "未记忆" 的情况设定为 -1，代表当前这个情况我们还没记忆过，因为本题不可能出现负收益，所以我们用-1来指代
    vector<vector<int>> memo(n+1, vector<int>(2, -1));
    function<int(int, bool)> dfs = [&](int i, bool flag) -> int
    {
        if(memo[i][flag] != -1)
        {
            return memo[i][flag];
        }
        // 边界情况1. 没有一间房子要偷，此时收益显然是0
        if(i == 0)
        {
            memo[0][flag] = 0;
            return memo[0][flag];
        }
        // 边界情况2. 只有一间房子要偷，此时我们需要根据 flag 的值来判断是偷还是不偷
        if(i == 1)
        {
            memo[1][flag] = flag ? nums[0] : 0;
            return memo[1][flag];
        }
        // 边界情况3. 当前检查的是前 n 间房子， 那么此时第一间房子偷窃与否就会和我们当前的判断有关了，需要考虑进来
        if(i == n)
        {
            // 如果第一间房子被偷了，那么这最后一间房子我们就一定不能偷，所以结果是 dfs(i-1, true)，即偷窃前 n-1 间房子，并且偷第一间房，可以拿到的最大收益
            // 如果不偷第一间房子，那么这最后一间房子我们也是可以偷的，所以结果是 max(dfs(i-1, false), dfs(i-2, false)+nums[i-1])
            // 即：此时决定不偷最后一间，而第一间房也不偷，可以偷到的最大收益
            // 和此时决定偷最后一间可以偷到的最大收益，二者的较大值
            memo[n][flag] = flag ? dfs(n-1, true) : max(dfs(n-1, false), dfs(n-2, false)+nums[n-1]);
            return memo[n][flag];
        }
        // 正常递归情况：
        memo[i][flag] = max(dfs(i-1, flag), dfs(i-2, flag)+nums[i-1]);
        return memo[i][flag];
    };
    // 明确了上面的递归过程，我们只需要在下面进行函数调用即可
    // 注意调用的时候，需要分第一间房是否偷分两种情况
    return max(dfs(n, false), dfs(n, true));
}

// 第三版：把 DFS + 记忆化转换成完全优化的 DP 数组
int robDP(vector<int>& nums)
{
class Solution {
public:
    int rob(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> dp(n+1, vector<int>(2, -1));
    // 先设定边界情况
    // 对应边界情况1
    dp[0][true] = dp[0][false] = 0;
    // 对应边界情况2
    dp[1][true] = nums[0]; dp[1][false] = 0;
    // 注意，边界情况3，我们没法直接在这里先进行计算，根据上面 DFS 的逻辑，它还需要子情况的结果，所以我们只能在循环结束后才能进行计算
    // 先开始执行循环
    for(int i = 2; i < n; ++i)
    {
        dp[i][true] = max(dp[i-1][true], dp[i-2][true]+nums[i-1]);
        dp[i][false] = max(dp[i-1][false], dp[i-2][false]+nums[i-1]);
    }
    // 对应边界情况3
    // 注意加上条件判断防止数组越界
    if(n == 1)
    {
        return nums[0];
    }
    dp[n][true] = dp[n-1][true];
    dp[n][false] = max(dp[n-1][false], dp[n-2][false]+nums[n-1]);
    return max(dp[n][true], dp[n][false]);
    }
};
}

// 第四版：滚动优化二维数组(实际是一维)
int robDPOpt(vector<int>& nums)
{
    int n = nums.size();
    // 考虑上面的递推过程，我们依然会发现，每个新状态最多只会依赖它前面的两个状态信息，所以对于上面的问题，我们只需要维护四个变量即可
    int dp00 = -1, dp01 = -1, dp10 = -1, dp11 = -1;
    // 对应边界情况1
    dp00 = dp01 = 0;
    // 对应边界情况2
    // 注意加上条件判断，这里是为了防止返回值从定义上出问题
    if(n == 0)
    {
        return 0;
    }
    dp10 = 0; dp11 = nums[0];
    // 进行滚动的递推
    for(int i = 2; i < n; ++i)
    {
        int tmp1 = dp10, tmp2 = dp11;
        dp10 = max(dp10, dp00+nums[i-1]);
        dp11 = max(dp11, dp01+nums[i-1]);
        dp00 = tmp1; dp01 = tmp2;
    }
    // 对应边界情况3
    // 注意加上条件判断，这里是为了防止返回值从定义上出问题
    if(n == 1)
    {
        return nums[0];
    }
    dp10 = max(dp10, dp00+nums[n-1]);
    dp11 = dp11;
    return max(dp11, dp10);
}