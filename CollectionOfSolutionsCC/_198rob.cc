#include "Solution.h"

// 第一版：单纯的 DFS，不带记忆化，意料之中的超时
int Leetcode101_200::Solution::rob(vector<int>& nums)
{
    // 本题也是一个非常经典的 DP 问题系列的入口题
    // 我们还是先从 DFS 的角度入手思考
    // 考虑最终的问题是什么
    // 小偷从 nums 中的所有房子中偷窃，能偷到的最大金额
    // 可以把定义换一种格式：
    // int dfs(i) -> 从 nums 中的前 i 个房子中偷窃，能拿到的最大金额
    // 那么我们最后的答案就是 dfs(n) (n 为 nums.size())
    // 考虑递推关系：
    // 要求 dfs(i)，那么我们有两种可能能算出这个值
    // 1. 不偷第 i 间房，那么 dfs(i) 可以等于 dfs(i-1)
    // 2. 偷窃第 i 间房，那么 dfs(i) 可以等于 dfs(i-2)+nums[i-1]
    int n = nums.size();
    function<int(int)> dfs = [&](int i)
    {
        // 边界情况
        // 不偷任何房子，结果显然是0
        if(i == 0)
        {
            return 0;
        }
        // 只偷第一间房，结果显然是 nums[0]，因为我们保证了数组中一定都是非负元素
        if(i == 1)
        {
            return nums[0];
        }
        // 其它情况，按两种情况进行分类讨论即可
        return max(dfs(i-1), dfs(i-2)+nums[i-1]);
    };
    // 进行调用即可
    return dfs(n);
}

// 第二版：基于第一版的 DFS 增添一个记忆化数组，可以通过
int robMemo(vector<int>& nums)
{
    // 本题也是一个非常经典的 DP 问题系列的入口题
    // 我们还是先从 DFS 的角度入手思考
    // 考虑最终的问题是什么
    // 小偷从 nums 中的所有房子中偷窃，能偷到的最大金额
    // 可以把定义换一种格式：
    // int dfs(i) -> 从 nums 中的前 i 个房子中偷窃，能拿到的最大金额
    // 那么我们最后的答案就是 dfs(n) (n 为 nums.size())
    // 考虑递推关系：
    // 要求 dfs(i)，那么我们有两种可能能算出这个值
    // 1. 不偷第 i 间房，那么 dfs(i) 可以等于 dfs(i-1)
    // 2. 偷窃第 i 间房，那么 dfs(i) 可以等于 dfs(i-2)+nums[i-1]
    int n = nums.size();
    // 添加一个记忆化数组
    vector<int> memo(n+1, -1);
    function<int(int)> dfs = [&](int i)
    {
        // 边界情况
        // 不偷任何房子，结果显然是0
        if(i == 0)
        {
            return 0;
        }
        // 只偷第一间房，结果显然是 nums[0]，因为我们保证了数组中一定都是非负元素
        if(i == 1)
        {
            return nums[0];
        }
        if(memo[i] != -1)
        {
            return memo[i];
        }
        // 其它情况，按两种情况进行分类讨论即可
        memo[i] = max(dfs(i-1), dfs(i-2)+nums[i-1]);
        return memo[i];
    };
    // 进行调用即可
    return dfs(n);
}

// 第三版：改成完全优化的 DP 方案
int robDP(vector<int>& nums)
{
    // 基于第二版的记忆化 DFS 转成自底向上的 DP 即可
    int n = nums.size();
    // 避免后面 dp[1] = nums[0] 可能的溢出问题
    if(n == 0)
    {
        return 0;
    }
    vector<int> dp(n+1, -1);
    // 先处理两个边界情况
    dp[0] = 0; dp[1] = nums[0];
    // 进行递推
    for(int i = 2; i <= n; ++i)
    {
        dp[i] = max(dp[i-1], dp[i-2]+nums[i-1]);
    }
    return dp[n];
}

// 第四版：继续针对 DP 进行空间优化
int robDPOpt(vector<int>& nums)
{
    // 注意到我们填写一维数组的时候，每个格子只和它前面的两个格子有关
    // 那么显然可以进行滚动优化
    // 基于第二版的记忆化 DFS 转成自底向上的 DP 即可
    int n = nums.size();
    // 避免后面 dp1 = nums[0] 可能的溢出问题
    if(n == 0)
    {
        return 0;
    }
    // 先处理两个边界情况
    int dp0 = 0, dp1 = nums[0];
    // 进行递推
    for(int i = 2; i <= n; ++i)
    {
        int tmp = dp1;
        dp1 = max(dp1, dp0+nums[i-1]);
        dp0 = tmp;
    }
    return dp1;    
}

// 备注：本题其实本质上应该是一个区间 DP，递归定义应该类似下面这样：
// int dfs(i, j) -> 小偷偷窃下标 [i, j] 之间的房子，能拿到的最大金额
// 那么有 dfs(i, j) = 四种两端值的偷窃情况的最大值
// 1) i 房偷，j 房也偷
//      dfs(i, j) = dfs(i+2, j-2) + nums[i-1] + nums[j-1]
// 2) i 房偷，j 房不偷
//      dfs(i, j) = dfs(i+2, j-1) + nums[i-1]
// 3) i 房不偷，j 房偷
//      dfs(i, j) = dfs(i+1, j-2) + nums[j-1]
// 4) i 房不偷，j 房也不偷
//      dfs(i, j) = dfs(i+1, j-1)
// 通过这种区间定义，我们也可以拿到最终的结果，也可以转换出最后的 DP 方案
// 只不过这里我们略过了有关区间大小和线性 DP 之间的优化策略问题