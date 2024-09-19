#include "Solution.h"

int Leetcode1_100::Solution::maxSubArray(vector<int>& nums)
{
    // 本题是一道很经典的算法入门题目，几乎所有学过算法的人都会在最开始接触分治思想的时候接触到类似的题目，
    // 不过我们也应该认识到，分治算法并不是时间上最优的，也不是空间上最优的 O(nlogn)
    // 由于要检查的是子数组，所以这个数字序列一定是在原数组中连续的一串数
    // 因而我们可以应用一种分立的动态规递推方案
    // 设定 dp[i] 代表以 nums[i] 结尾的所有子数组中和最大的那一个的和值
    // 于是最终的结果就是 max(for all i in [0, nums.size()-1]，dp[i])
    // 关于递推过程，考虑求解 dp[i]
    // 如何从前面的结果递推到当前结果？
    // 很显然的是，我们只可能通过 dp[i-1] 递推过来，因为 dp 数组本身的定义，前面的所有值 j，dp[j] 代表的都是一个在
    // 前面就已经断开的子数组，也就是说，它们都无法和 nums[i] 连接形成一个子数组
    // 那么，这样考虑
    // 如果 dp[i-1] + nums[i] > nums[i] (或者说：dp[i-1] > 0)
    // 那么 dp[i-1] 就可以连接到 dp[i] 上，构成一个和更大的连续子数组(同时也是结尾于 nums[i] 的)
    // 同时，不要忘了，如果 dp[i-1] + nums[i] <= nums[i]
    // 此时我们不能简单的给 dp[i] 赋一个默认值或者直接跳过更新
    // 因为 nums[i] 本身也可以自成一个子数组，这个子数组的和值就是它本身的值
    // 综上 dp[i] = dp[i-1] > 0 ? dp[i-1]+nums[i] : nums[i]
    // 公式推导完成，剩下的代码部分就非常简单了
    // dp 数组可以优化为 O(1) 的变量
    int n = nums.size();
    // 边界情况：dp[0] = nums[0]
    int dp = nums[0];
    // 记录全局答案
    int res = max(INT_MIN, dp);
    for(int i = 1; i < n; ++i)
    {   
        dp = dp > 0 ? dp+nums[i] : nums[i];
        res = max(res, dp);
    }
    return res;
}