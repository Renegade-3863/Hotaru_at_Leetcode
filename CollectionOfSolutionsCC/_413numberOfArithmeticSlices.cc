#include "Solution.h"

// 第一版：DFS 不带记忆化
int Leetcode401_500::Solution::numberOfArithmeticSlices(vector<int>& nums)
{
    // 定义一个子问题：以 nums[i] 结尾的，长度为 k 的，等差为 d 等差数列的个数
    // dfs(i, k, d)
    // 考虑如何进行递推
    // dfs(i, k, d) = dfs(i-1, k-1, d);
    // 想法很简单：以当前数据结尾的，长度为 k 的，等差为 d 的等差数列
    // 等于 以上一个数据结尾的，长度为 k-1 的，等差同样为 d 的等差数列的个数
    // 想明白了递推过程，我们就可以写函数了
    int n = nums.size();
    function<int(int, int)> dfs = [&](int i, int k) -> int 
    {
        // 下一个难点是处理基本情况
        // 考虑什么样的子问题是可以直接解决，不用递归的
        // 1. k == 3，此时我们只需要检查 nums[i-1]
        if(k == 3)
        {
            // 我们需要检查 i 是否大于 1，因为 i <= 1 的时候不存在合法的等差数列
            if(i > 1 && nums[i]-nums[i-1] == nums[i-1] - nums[i-2])
            {
                return 1;
            }
            return 0;
        }
        // 其它情况下，我们正常递推即可
        int ret = nums[i] - nums[i-1] == nums[i-1]-nums[i-2] && dfs(i-1, k-1);
        return ret;
    };
    // 我们对每一个元素调用上面的函数即可
    int res = 0;
    for(int i = 2; i < n; ++i)
    {
        for(int j = 3; j <= i+1; ++j)
        {
            res += dfs(i, j);
        }
    }
    return res;
}

// 第二版：DFS + 记忆化
int numberOfArithmeticSlices(vector<int>& nums)
{
    // 定义一个子问题：以 nums[i] 结尾的，长度为 k 的等差数列的个数
    // dfs(i, k)
    // 考虑如何进行递推
    // dfs(i, k) = nums[i] - nums[i-1] == nums[i-1] - nums[i-2] && dfs(i-1, k-1);
    // 想法很简单：以当前数据结尾的，长度为 k 的，等差为 d 的等差数列
    // 等于 以上一个数据结尾的，长度为 k-1 的，等差同样为 d 的等差数列的个数
    // 想明白了递推过程，我们就可以写函数了
    int n = nums.size();
    // 添加一个记忆化数组
    vector<vector<int>> memo(n, vector<int>(n+1, -1));
    function<int(int, int)> dfs = [&](int i, int k) -> int 
    {
        if(memo[i][k] != -1)
        {
            return memo[i][k];
        }
        // 下一个难点是处理基本情况
        // 考虑什么样的子问题是可以直接解决，不用递归的
        // k == 3，此时我们只需要检查 nums[i-1]
        if(k == 3)
        {
            // 我们需要检查 i 是否大于 1，因为 i <= 1 的时候不存在合法的等差数列
            if(i > 1 && nums[i]-nums[i-1] == nums[i-1] - nums[i-2])
            {
                memo[i][k] = 1;
                return 1;
            }
            memo[i][k] = 0;
            return 0;
        }
        // 其它情况下，我们正常递推即可
        memo[i][k] = nums[i] - nums[i-1] == nums[i-1]-nums[i-2] && dfs(i-1, k-1);
        return memo[i][k];
    };
    // 我们对每一个元素调用上面的函数即可
    int res = 0;
    for(int i = 2; i < n; ++i)
    {
        for(int j = 3; j <= i+1; ++j)
        {
            res += dfs(i, j);
        }
    }
    return res;
}

// 第三版：转换成 DP 的自底向上解法
int numberOfArithmeticSlices(vector<int>& nums)
{
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n+1, 0));
    // 处理边界情况
    int res = 0;
    for(int i = 2; i < n; ++i)
    {
        dp[i][3] = nums[i]-nums[i-1] == nums[i-1] - nums[i-2];  
        res += dp[i][3];
    }
    // 之后是正常的递推过程
    for(int i = 3; i < n; ++i)
    {
        for(int j = 4; j <= i+1; ++j)
        {
            dp[i][j] = nums[i]-nums[i-1] == nums[i-1]-nums[i-2] && dp[i-1][j-1];
            res += dp[i][j];
        }
    }
    return res;
}

// 第四版：对 DP 的递推逻辑进行优化
int numberOfArithmeticSlices(vector<int>& nums)
{
    // 我们还是想复杂了，我们应该先考虑一维的 DP 应该如何做
    // 定义 dp[i] 为以 nums[i] 结尾的等差序列的个数
    // 那么对于 dp[i] 无非有两种可能：
    // 1. nums[i]-nums[i-1] == nums[i-1]-nums[i-2]
    // 那么此时我们可以把所有结束于 nums[i-1] 的等差数列 "接成" 一个以 nums[i] 结尾的等差数列
    // 那么我们就可以获得 dp[i-1] 个新的等差数列，以及一个 {nums[i-2], nums[i-1], nums[i]} 的新等差数列
    // 此时 dp[i] = dp[i-1]+1
    // 2. nums[i]-nums[i-1] != nums[i-1]-nums[i-2]
    // 那么很明显不存在以 nums[i] 结尾的等差数列
    // dp[i] = 0
    int n = nums.size();
    if(n <= 2)
    {
        return 0;
    }
    vector<int> dp(n, 0);
    // 边界情况设定
    dp[2] = nums[2]-nums[1] == nums[1]-nums[0];
    int res = dp[2];
    for(int i = 3; i < n; ++i)
    {
        if(nums[i]-nums[i-1] == nums[i-1]-nums[i-2])
        {
            dp[i] = dp[i-1]+1;
        }
        res += dp[i];
    }
    return res;
}

// 第五版：空间优化
// 很简单，就不写了。。。