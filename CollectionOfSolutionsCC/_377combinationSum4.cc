#include "Solution.h"

// 第一版：暴力 DFS，TLE
int Leetcode301_400::Solution::combinationSum4(vector<int>& nums, int target)
{
    // 本题要求找出所有组合出目标和的不同排列的总数
    // 抛开很多题解中说的那种所谓 "背包不背包" 的思路，我们着眼于这道题本身
    // 它说什么，我们就定义什么
    // 先从一维开始
    // 假设构成 subTarget 可行的总方案数为 dfs(subTarget)
    // 那么很明显我们最后要求的问题就是 dfs(target)
    // 思考是否可以进行递推：
    // 对于 dfs(subTarget)，我们枚举每一种可能的结果最后一个元素值
    // 假设结果的最后一个元素是 nums[0]
    // 那么 dfs(subTarget) 包含 dfs(subTarget-nums[0]) 个组分 (假设 subTarget >= nums[0])
    // 假设最后一个元素是 nums[1]
    // dfs(subTarget) 包含 dfs(subTarget-nums[1]) 个组分 (假设 subTarget >= nums[1])
    // 以此类推
    // 知道我们遍历完所有可能的排列末尾元素为止
    // 这样，我们就找出了所有能够构成 subTarget 的排列种类数
    // 剩下的就是写代码了
    function<int(int)> dfs = [&](int subTarget) -> int
    {
        // 思考递归的最小子问题：
        // subTarget == 0
        // 此时我们不需要任何的值，长度为 0 的集合即可构成这个结果
        // 注意，上面的断言并不适用题目思考里面给出的：nums 包含负数 的条件
        // 因为如果 nums 包含负数，那么我们要构成 0，就可能是同时包含正负数的情况了
        // 应该说允许负数出现，我们就不得不考虑无限长度的排列了
        // 此时就必须添加一个限定结果排列长度的要求，来避免求出无限长度的结果排列
        // 我们这里使用的这种单一变量的定义式也就没法定位到最小子问题了。。。
        if(subTarget == 0)
        {
            return 1;
        }
        // 其它情况：考虑枚举 nums 数组中的每一种不同元素作为构成 subTarget 的排列的最后一个元素
        int res = 0;
        for(const int& num : nums)
        {
            if(subTarget >= num)
            {
                res += dfs(subTarget-num);
            }
        }
        return res;
    };
    // 调用即可
    return dfs(target);
}

// 第二版：DFS + 记忆化加速
int combinationSum4(vector<int>& nums, int target)
{
    // 本题要求找出所有组合出目标和的不同排列的总数
    // 抛开很多题解中说的那种所谓 "背包不背包" 的思路，我们着眼于这道题本身
    // 它说什么，我们就定义什么
    // 先从一维开始
    // 假设构成 subTarget 可行的总方案数为 dfs(subTarget)
    // 那么很明显我们最后要求的问题就是 dfs(target)
    // 思考是否可以进行递推：
    // 对于 dfs(subTarget)，我们枚举每一种可能的结果最后一个元素值
    // 假设结果的最后一个元素是 nums[0]
    // 那么 dfs(subTarget) 包含 dfs(subTarget-nums[0]) 个组分 (假设 subTarget >= nums[0])
    // 假设最后一个元素是 nums[1]
    // dfs(subTarget) 包含 dfs(subTarget-nums[1]) 个组分 (假设 subTarget >= nums[1])
    // 以此类推
    // 知道我们遍历完所有可能的排列末尾元素为止
    // 这样，我们就找出了所有能够构成 subTarget 的排列种类数
    // 剩下的就是写代码了
    // 添加一个记忆化数组 memo
    vector<int> memo(target+1, -1);
    function<int(int)> dfs = [&](int subTarget) -> int
    {
        // 思考递归的最小子问题：
        // subTarget == 0
        // 此时我们不需要任何的值，长度为 0 的集合即可构成这个结果
        // 注意，上面的断言并不适用题目思考里面给出的：nums 包含负数 的条件
        // 因为如果 nums 包含负数，那么我们要构成 0，就可能是同时包含正负数的情况了
        // 应该说允许负数出现，我们就不得不考虑无限长度的排列了
        // 此时就必须添加一个限定结果排列长度的要求，来避免求出无限长度的结果排列
        // 我们这里使用的这种单一变量的定义式也就没法定位到最小子问题了。。。
        if(subTarget == 0)
        {
            return 1;
        }
        if(memo[subTarget] != -1)
        {
            return memo[subTarget];
        }
        // 其它情况：考虑枚举 nums 数组中的每一种不同元素作为构成 subTarget 的排列的最后一个元素
        int res = 0;
        for(const int& num : nums)
        {
            if(subTarget >= num)
            {
                res += dfs(subTarget-num);
            }
        }
        memo[subTarget] = res;
        return res;
    };
    // 调用即可
    return dfs(target);
}

// 第三版：修改为自底向上的 DP 方法
int combinationSum4(vector<int>& nums, int target)
{
    vector<int> dp(target+1, 0);
    dp[0] = 1;
    for(int i = 1; i <= target; ++i)
    {
        int res = 0;
        for(const int& num : nums)
        {
            // 正向递推需要注意一点：因为我们的限制不是从最后的结果往回推，可能会计算出一些更大的结果，这些值是不必要且不合法(会溢出)的，我们需要进行一些额外的限制
            if(i >= num && res < INT_MAX-dp[i-num])
            {
                res += dp[i-num];
            }
        }
        dp[i] = res;
    }
    return dp[target];
}