class Solution
{
public:
    int maxSubarraySumCircular(vector<int>& nums)
    {
        // 也是一道方法不是那么普适的题目
        // 非环的子数组最大和问题很好做，Kadane 算法可以 O(n) 高效求解
        // 如果是带环的数组，那么无非就是多了一种情况：
        // 子数组越过数组边界，连接首尾
        // 此时的最大子数组和
        // 但是求解两段子数组和的最大值有些困难
        // 最关键也是最难想到的一步观察是：
        // 假设 nums 中的元素和为 sum
        // 那么我们要求的首尾两段和的最大值，等同于寻找一个中间的单一段，这个子数组的和满足全局最小
        // 这个观察问题同样可以用调整的 Kadane 算法来求解
        // 我们返回两种情况下的最大结果即可
        int n = nums.size();
        vector<int> dp(n, 0);
        // max1 用来保存原始无环数组的最大结果
        int max1 = nums[0], sum = nums[0];
        dp[0] = nums[0];
        for(int i = 1; i < n; ++i)
        {
            dp[i] = dp[i-1] > 0 ? dp[i-1]+nums[i] : nums[i];
            max1 = max(max1, dp[i]);
            sum += nums[i];
        }
        // 之后我们可以清空 dp，用它再来计算第二个问题
        dp = vector<int>(n, 0);
        dp[0] = nums[0];
        // max1 用来保存原始无环数组的最小结果
        int min1 = nums[0];
        for(int i = 1; i < n; ++i)
        {
            dp[i] = dp[i-1] < 0 ? dp[i-1]+nums[i] : nums[i];

            min1 = min(min1, dp[i]);
        }
        // 实际实现时还有一种额外情况需要考虑：
        // 如果最小子数组覆盖了整个 nums 数组，此时我们怎么办？
        // 我们这里用 sum == min1 来进行判断
        // 给出下面的证明：
        // 1. sum == min1 仅在 min1 代表的子数组等于 nums 数组的时候成立
        // 那么此时很显然不存在跨越首尾的最大子数组，我们返回 max1 是正确的
        // 2. sum == min1 不仅在 min1 代表的子数组等于 nums 数组的时候成立
        // 那么即使这个 min1 代表的子数组覆盖的是中间的一个（不与两侧边界重合）的子数组，这样我们找到了一个跨越首尾的最大子数组（和为 0）
        // 那么很明显首尾的这两段中必然一段为负数，另一端为正数；或者两段均为 0
        // 无论哪种情况，max1 的正确性都依然成立
        if(sum == min1)
        {
            return max1;
        }
        // 如果 sum != min1，那么很显然 min1 代表的子数组也就不可能是整个 nums 了
        return max(max1, sum-min1);
    }
};