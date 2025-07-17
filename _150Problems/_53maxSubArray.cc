// 写错了，这个是求最大子序列的。。。
class Solution
{
public:
    int maxSubArray(vector<int>& nums)
    {
        // 依然是一个简单的 DP 问题（套了个 Kadane 算法的壳子罢了) 
        // 我们给出如下定义：
        // dp[i] 代表 nums[0..i] 这个子数组中具有最大和的连续子数组的和
        // 那么对于 dp[i]
        // 我们无非有两种可能的结果：
        // 1. 结果包含 nums[i]
        // 此时 dp[i] = max(dp[i-1]+nums[i], nums[i])
        // 2. 结果不包含 nums[i]
        // 此时 dp[i] = dp[i-1]
        // 综上：
        // dp[i] = max(max(dp[i-1]+nums[i], nums[i]), dp[i-1])
        int res = INT_MIN, n = nums.size();
        vector<int> dp(n, 0);
        // 初始化边界条件：
        dp[0] = nums[0];
        res = max(res, dp[0]);
        for(int i = 1; i < n; ++i)
        {
            dp[i] = max(max(dp[i-1]+nums[i], nums[i]), dp[i-1]);
            res = max(res, dp[i]);
        }
        return res;
    }
};

// 重新写
class Solution
{
public:
    int maxSubArray(vector<int>& nums)
    {
        // 依然是一个简单的 DP 问题（套了个 Kadane 算法的壳子罢了) 
        // 我们给出如下定义：
        // dp[i] 代表以 nums[i] 结尾，并且具有最大和的连续子数组的和
        // 那么 dp[i] 就等于 
        // 如果 dp[i-1] 为正，那么 dp[i] 可以等于 dp[i-1]+nums[i]
        // 否则，dp[i] 就等于 nums[i] 自己
        int n = nums.size(), res = INT_MIN;
        vector<int> dp(n, 0);
        dp[0] = nums[0];
        res = max(res, dp[0]);
        for(int i = 1; i < n; ++i)
        {
            dp[i] = dp[i-1] > 0 ? dp[i-1]+nums[i] : nums[i];
            res = max(res, dp[i]);
        }
        return res;
    }
};