#include "Solution.h"

// 第一版：暴力 DFS，不带记忆化，TLE
int Leetcode301_400::Solution::maxCoins(vector<int>& nums)
{
    // 本题需要稍微思考一下如何设计 DP/DFS 的子问题定义
    // 先思考这样一个问题：最后的结果是谁？
    // 不难想到，我们最后一步一定会是只剩下了一个数值，这个数值(气球)最后也被戳破，得到的最终结果就是我们得到的最后一次硬币数
    // 我们假设 dfs(i, j) 代表的是，我们戳破 nums[i] 到 nums[j] 之间所有气球(开区间) 所能拿到的最大硬币数
    // 那么，很显然我们会有这样的子问题：
    // 我们选定一个气球，最后戳破它(假设下标为 k)，在这之前，先戳破 nums[i] 到 nums[k-1] 和 nums[k+1] 到 nums[j] 之间(开区间)的所有气球，
    // 获得两个最大收入 dfs(i, k-1) 和 dfs(k+1, j)
    // 最后一步戳破下标为 k 的气球，再获得 nums[i]*nums[k]*nums[j] 枚硬币
    // 注意，我们这样做的底线在于：最后戳破的气球一定能跟 nums[i] 和 nums[j] 组合
    // 这其实就暗示了我们需要对 nums 进行修改，给左右边界填补上两个1
    // 因为如果和原来的 nums[0] 以及 nums[nums.size()-1] 组合，那么很显然组合出来的值并不是最后的结果，因为我们还剩下两个气球 (nums[0] 和 nums[nums.size()-1]) 没有戳爆
    int n = nums.size();
    vector<int> val(n+2, 1);
    for(int i = 1; i <= n; ++i)
    {
        val[i] = nums[i-1];
    }
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 定义递归的结束条件
        // 没有气球，我们就可以直接返回0，因为没有气球可以戳，我们没法获得任何硬币
        if(i >= j-1)
        {
            return 0;
        }
        int res = 0;
        for(int k = i+1; k < j; ++k)
        {
            res = max(res, dfs(i, k)+dfs(k, j)+val[i]*val[k]*val[j]);
        }
        return res;
    };
    // 直接调用即可
    return dfs(0, n+1);
}

// 第二版：DFS + 记忆化加速
int maxCoins(vector<int>& nums)
{
    // 本题需要稍微思考一下如何设计 DP/DFS 的子问题定义
    // 先思考这样一个问题：最后的结果是谁？
    // 不难想到，我们最后一步一定会是只剩下了一个数值，这个数值(气球)最后也被戳破，得到的最终结果就是我们得到的最后一次硬币数
    // 我们假设 dfs(i, j) 代表的是，我们戳破 nums[i] 到 nums[j] 之间所有气球(开区间) 所能拿到的最大硬币数
    // 那么，很显然我们会有这样的子问题：
    // 我们选定一个气球，最后戳破它(假设下标为 k)，在这之前，先戳破 nums[i] 到 nums[k-1] 和 nums[k+1] 到 nums[j] 之间(开区间)的所有气球，
    // 获得两个最大收入 dfs(i, k-1) 和 dfs(k+1, j)
    // 最后一步戳破下标为 k 的气球，再获得 nums[i]*nums[k]*nums[j] 枚硬币
    // 注意，我们这样做的底线在于：最后戳破的气球一定能跟 nums[i] 和 nums[j] 组合
    // 这其实就暗示了我们需要对 nums 进行修改，给左右边界填补上两个1
    // 因为如果和原来的 nums[0] 以及 nums[nums.size()-1] 组合，那么很显然组合出来的值并不是最后的结果，因为我们还剩下两个气球 (nums[0] 和 nums[nums.size()-1]) 没有戳爆
    int n = nums.size();
    vector<int> val(n+2, 1);
    for(int i = 1; i <= n; ++i)
    {
        val[i] = nums[i-1];
    }
    // 添加一个记忆化数组 memo
    vector<vector<int>> memo(n+2, vector<int>(n+2, -1));
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        if(memo[i][j] != -1)
        {
            return memo[i][j];
        }
        // 定义递归的结束条件
        // 没有气球，我们就可以直接返回0，因为没有气球可以戳，我们没法获得任何硬币
        if(i >= j-1)
        {
            return 0;
        }
        int res = 0;
        for(int k = i+1; k < j; ++k)
        {
            res = max(res, dfs(i, k)+dfs(k, j)+val[i]*val[k]*val[j]);
        }
        memo[i][j] = res;
        return res;
    };
    // 直接调用即可
    return dfs(0, n+1);
}

// 第三版：改为自底向上的 DP 方案
int maxCoins(vector<int>& nums)
{
    int n = nums.size();
    vector<int> val(n+2, 1);
    for(int i = 1; i <= n; ++i)
    {
        val[i] = nums[i-1];
    }
    vector<vector<int>> dp(n+2, vector<int>(n+2, 0));
    // 边界情况已经初始化完成，所以可以直接开始递推
    // 按区间长度进行遍历
    for(int len = 3; len <= n+2; ++len)
    {
        // 枚举区间起点
        for(int i = 0; i <= n+2-len; ++i)
        {
            // 取出区间右边界
            int j = i+len-1;
            // 按照上面的方式进行递推
            for(int k = i+1; k < j; ++k)
            {
                dp[i][j] = max(dp[i][j], dp[i][k]+dp[k][j]+val[i]*val[k]*val[j]);
            }
        }
    }
    return dp[0][n+1];
}