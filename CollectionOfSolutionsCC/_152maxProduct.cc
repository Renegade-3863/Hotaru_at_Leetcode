#include "Solution.h"

// 第一版：完全的 DFS，不加记忆化，会超时
int Leetcode101_200::Solution::maxProduct(vector<int>& nums)
{
    // 本题由于数组中可能存在负数，而且要求的是乘积最大的子数组，而不是和最大的子数组
    // 我们不能用常规的 DFS 思路
    // 因为可能会出现下面这样的情况：
    // 当前值是一个负数，前面存在一个乘积为很小负数的值，那么这两个值乘到一起反而会是一个很大的值，而如果我们只检查所有以某个元素结尾的子数组的最大乘积
    // 那么显然会丢失这种情况
    // 因而我们可以如下定义 DFS 规律
    // dfs(i, max)  (max 是一个 bool 类型变量)
    // 代表以下标 i 为结尾的子数组的最大/最小乘积子数组的乘积
    // 那么最后的结果就是 max(dfs(k, max == true)) where k from 0 to nums.size()-1
    function<int(int, bool)> dfs = [&](int k, bool maxOrmin) -> int
    {
        // 如果只要求求解结束于 nums[0] 的最大乘积子数组，那么结果就是它本身
        if(k == 0)
        {
            return nums[0];
        }
        // 否则，需要通过前面一个下标的相关结果进行求解
        // 如果 nums[k] 是一个正数
        if(nums[k] > 0)
        {
            // 如果需要的是一个最大值，那么就要检查以前一个下标结尾的最大乘积子数组
            if(maxOrmin)
            {
                return max(dfs(k-1, true) * nums[k], nums[k]);
            }
            else
            {
                return min(dfs(k-1, false) * nums[k], nums[k]);
            }
        }
        // 如果 nums[k] 是0，那么结果就一定是0，可以直接返回
        else if(nums[k] == 0)
        {
            return 0;
        }
        // 如果 nums[k] 是一个负数，那么就要检查以前一个下标结尾的最小乘积子数组

        // 如果需要的是一个最大值，那么就要检查以前一个下标结尾的最大乘积子数组
        if(maxOrmin)
        {
            return max(dfs(k-1, false) * nums[k], nums[k]);
        }
        return min(dfs(k-1, true) * nums[k], nums[k]);
    };
    // 进行调用即可
    int res = INT_MIN, n = nums.size();
    for(int i = 0; i < n; ++i)
    {
        res = max(res, dfs(i, true));
    }
    return res;
}

// 第二版：完全 DFS + 记忆化，可以通过，不过效率很低
int maxProductMemo(vector<int>& nums)
{
    // 本题由于数组中可能存在负数，而且要求的是乘积最大的子数组，而不是和最大的子数组
    // 我们不能用常规的 DFS 思路
    // 因为可能会出现下面这样的情况：
    // 当前值是一个负数，前面存在一个乘积为很小负数的值，那么这两个值乘到一起反而会是一个很大的值，而如果我们只检查所有以某个元素结尾的子数组的最大乘积
    // 那么显然会丢失这种情况
    // 因而我们可以如下定义 DFS 规律
    // dfs(i, max)  (max 是一个 bool 类型变量)
    // 代表以下标 i 为结尾的子数组的最大/最小乘积子数组的乘积
    // 那么最后的结果就是 max(dfs(k, max == true)) where k from 0 to nums.size()-1
    int res = INT_MIN, n = nums.size();
    vector<vector<int>> memo(n, vector<int>(2, 0x80000000));
    function<int(int, bool)> dfs = [&](int k, bool maxOrmin) -> int
    {
        if(memo[k][maxOrmin] != 0x80000000)
        {
            return memo[k][maxOrmin];
        }
        // 如果只要求求解结束于 nums[0] 的最大乘积子数组，那么结果就是它本身
        if(k == 0)
        {
            return nums[0];
        }
        // 否则，需要通过前面一个下标的相关结果进行求解
        // 如果 nums[k] 是一个正数
        if(nums[k] > 0)
        {
            // 如果需要的是一个最大值，那么就要检查以前一个下标结尾的最大乘积子数组
            if(maxOrmin)
            {
                memo[k][true] = max(dfs(k-1, true) * nums[k], nums[k]);
                return memo[k][true];
            }
            else
            {
                memo[k][false] = min(dfs(k-1, false) * nums[k], nums[k]);
                return memo[k][false];
            }
        }
        // 如果 nums[k] 是0，那么结果就一定是0，可以直接返回
        else if(nums[k] == 0)
        {
            return 0;
        }
        // 如果 nums[k] 是一个负数，那么就要检查以前一个下标结尾的最小乘积子数组

        // 如果需要的是一个最大值，那么就要检查以前一个下标结尾的最大乘积子数组
        if(maxOrmin)
        {
            memo[k][true] = max(dfs(k-1, false) * nums[k], nums[k]);
            return memo[k][true];
        }
        memo[k][false] = min(dfs(k-1, true) * nums[k], nums[k]);
        return memo[k][false];
    };
    // 进行调用即可
    for(int i = 0; i < n; ++i)
    {
        res = max(res, dfs(i, true));
    }
    return res;
}

// 第三版：完全优化的 DP，一样能通过，同时效率也很低
int maxProductDP(vector<int>& nums)
{
    // 修改记忆化数组为一个 DP 数组
    int n = nums.size(), res = INT_MIN;
    vector<vector<int>> dp(n, vector<int>(2, 0));
    dp[0][0] = nums[0];
    dp[0][1] = nums[0];
    res = max(res, dp[0][1]);
    for(int i = 1; i < n; ++i)
    {
        if(nums[i] > 0)
        {
            dp[i][1] = max(dp[i-1][1]*nums[i], nums[i]);
            dp[i][0] = min(dp[i-1][0]*nums[i], nums[i]);
        }
        else
        {
            dp[i][1] = max(dp[i-1][0]*nums[i], nums[i]);
            dp[i][0] = min(dp[i-1][1]*nums[i], nums[i]);
        }
        res = max(res, dp[i][1]);
    }
    return res;
}

// 第四版：完全优化的 DP，尝试优化空间复杂度
int maxProductDPOpt(vector<int>& nums)
{
    // 把 DP 数组优化为两个 DP 变量
    int n = nums.size(), res = INT_MIN;
    int dp0 = nums[0], dp1 = nums[0];
    res = max(res, dp1);
    for(int i = 1; i < n; ++i)
    {
        if(nums[i] > 0)
        {
            dp1 = max(dp1*nums[i], nums[i]);
            dp0 = min(dp0*nums[i], nums[i]);
        }
        else
        {
            int tmp = dp1;
            dp1 = max(dp0*nums[i], nums[i]);
            dp0 = min(tmp*nums[i], nums[i]);
        }
        res = max(res, dp1);
    }
    return res;
}