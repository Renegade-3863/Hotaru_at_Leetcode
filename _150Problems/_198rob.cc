class Solution
{
public:
    int rob(vector<int>& nums)
    {
        // 简单的 DP 类问题
        // 我们定义：
        // dp[i] 代表小偷从前 i 间房偷窃，可以拿到的最大利润
        // 很显然 dp[0] = 0
        int n = nums.size();
        vector<int> dp(n+1, 0);
        dp[1] = nums[0];
        // 进行递推
        for(int i = 2; i <= n; ++i)
        {
            // 对于第 i 间房，有两种选择
            // 1. 偷窃，第 i 间房，那么我们只能再从前 i-2 间房中偷
            dp[i] = dp[i-2]+nums[i-1];
            // 2. 不偷，那么我们还可以从前面 i-1 间房中偷
            dp[i] = max(dp[i-1], dp[i]);
        }
        return dp[n];
    }
}