#include "Solution.h"

// 第一版：暴力 DFS，不带记忆化
int Leetcode301_400::Solution::wiggleMaxLength(vector<int>& nums)
{
    // 应该还算明显的 DP 类问题
    // 我们先从自顶向下的 DFS 问题开始考虑问题
    // 如果想按照 DP 的子问题递推性来设计子问题格式，我们需要进一步考虑
    // 什么样的母问题可以具有子问题性质
    // 首先考虑一维的定义方式，即只由一个性质进行递推
    // 那么我们可以设：dfs(i) 代表考虑前 i 个数据，我们可以获得的最长摆动子序列的长度
    // 但这样我们很难发现任何有用的子问题定义，所以需要更换问题定义
    // 换成：dfs(i) 代表以 nums[i] 结尾的最长摆动子序列长度可以吗？
    // 似乎是可行的，不过依然有一个小问题：我们如何知道一个新数据能不能接到前面的一个最长摆动序列的结尾？
    // 因为我们并不知道这个最长的摆动序列的最后一个元素 (也就是 nums[i]) 和它前面的元素的关系
    // 那么我们就需要再添加一个状态信息，dfs 定义修改为：
    // dfs(i, status) -> 代表以 nums[i] 结尾，并且这个元素和上一个位置处的元素是 (status == true -> 大于，status == false -> 小于) 关系
    // 的情况下，最长的摆动子序列长度
    // 那么我们可以像这样进行递推：
    // 检查 i 前面的所有下标 k，如果 status == true，那么选出 dfs(k, false) 的最大值(同时还需要满足 nums[k] < nums[i]) 进行加一操作，作为 dfs(i, true) 的结果即可    
    function<int(int, bool)> dfs = [&](int i, bool status)
    {
        // 思考递归的最小子问题：
        // 当 i == 0 的时候，我们直接返回1即可，因为以 nums[0] 结尾的摆动序列一定只包含它自己
        if(i == 0)
        {
            return 1;
        }
        // 一般情况：
        // 根据 status 进行递推即可
        int res = 1;
        if(status)
        {
            for(int k = 0; k < i; ++k)
            {
                if(nums[k] < nums[i])
                {
                    res = max(res, dfs(k, false)+1);
                }
            }
            return res;
        }
        for(int k = 0; k < i; ++k)
        {
            if(nums[k] > nums[i])
            {
                res = max(res, dfs(k, true)+1);
            }
        }
        return res;
    };  
    int ans = 1;
    int n = nums.size();
    for(int i = 0; i < n; ++i)
    {
        ans = max(ans, dfs(i, true));
        ans = max(ans, dfs(i, false));
    }
    return ans;
}

// 第二版：DFS + 记忆化加速
int wiggleMaxLength(vector<int>& nums)
{
    // 应该还算明显的 DP 类问题
    // 我们先从自顶向下的 DFS 问题开始考虑问题
    // 如果想按照 DP 的子问题递推性来设计子问题格式，我们需要进一步考虑
    // 什么样的母问题可以具有子问题性质
    // 首先考虑一维的定义方式，即只由一个性质进行递推
    // 那么我们可以设：dfs(i) 代表考虑前 i 个数据，我们可以获得的最长摆动子序列的长度
    // 但这样我们很难发现任何有用的子问题定义，所以需要更换问题定义
    // 换成：dfs(i) 代表以 nums[i] 结尾的最长摆动子序列长度可以吗？
    // 似乎是可行的，不过依然有一个小问题：我们如何知道一个新数据能不能接到前面的一个最长摆动序列的结尾？
    // 因为我们并不知道这个最长的摆动序列的最后一个元素 (也就是 nums[i]) 和它前面的元素的关系
    // 那么我们就需要再添加一个状态信息，dfs 定义修改为：
    // dfs(i, status) -> 代表以 nums[i] 结尾，并且这个元素和上一个位置处的元素是 (status == true -> 大于，status == false -> 小于) 关系
    // 的情况下，最长的摆动子序列长度
    // 那么我们可以像这样进行递推：
    // 检查 i 前面的所有下标 k，如果 status == true，那么选出 dfs(k, false) 的最大值(同时还需要满足 nums[k] < nums[i]) 进行加一操作，作为 dfs(i, true) 的结果即可    
    // 添加一个记忆化数组
    int n = nums.size();
    vector<vector<int>> memo(n, vector<int>(2, -1));
    function<int(int, bool)> dfs = [&](int i, bool status)
    {
        if(memo[i][status] != -1)
        {
            return memo[i][status];
        }
        // 思考递归的最小子问题：
        // 当 i == 0 的时候，我们直接返回1即可，因为以 nums[0] 结尾的摆动序列一定只包含它自己
        if(i == 0)
        {
            return 1;
        }
        // 一般情况：
        // 根据 status 进行递推即可
        int res = 1;
        if(status)
        {
            for(int k = 0; k < i; ++k)
            {
                if(nums[k] < nums[i])
                {
                    res = max(res, dfs(k, false)+1);
                }
            }
            memo[i][1] = res;
            return res;
        }
        for(int k = 0; k < i; ++k)
        {
            if(nums[k] > nums[i])
            {
                res = max(res, dfs(k, true)+1);
            }
        }
        memo[i][status] = res;
        return res;
    };  
    int ans = 1;
    for(int i = 0; i < n; ++i)
    {
        ans = max(ans, dfs(i, true));
        ans = max(ans, dfs(i, false));
    }
    return ans;
}

// 第三版：把 DFS 变为自底向上的 DP
int wiggleMaxLength(vector<int>& nums)
{
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(2, 1));
    int ans = 1;
    // 边界情况已经在初始化的时候设定完成
    for(int i = 1; i < n; ++i)
    {
        for(int k = 0; k < 2; ++k)
        {
            int res = 1;
            for(int j = 0; j < i; ++j)
            {
                if(k && nums[j] < nums[i])
                {
                    res = max(res, dp[j][!k]+1);
                }
                if(!k && nums[j] > nums[i])
                {
                    res = max(res, dp[j][!k]+1);
                }
            }
            dp[i][k] = res;
            ans = max(ans, dp[i][k]);
        }
    }
    return ans;
}

// 第四版：时间优化：O(n^2) -> O(n)
// 我们对于递推的定义需要进行修改
// dp[i][0] 代表区间 [0, i] 之间的元素中，可以找出的最长的，最后一对元素是大于关系的摆动序列的长度
// dp[i][1] 是最后一对元素成小于关系的最长摆动序列长度
int wiggleMaxLength(vector<int>& nums)
{
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(2, 1));
    int ans = 1;
    for(int i = 1; i < n; ++i)
    {
        // 我们检查上一个子问题的最后一个元素和当前元素之间的关系
        // 如果当前元素比上一个元素大，那么 [0, i] 之间的元素所能形成的下降摆动子序列，和 [0, i-1] 之间的元素所能形成的下降摆动子序列没有本质区别
        // 因为对于所有以 nums[i] 结尾的下降摆动序列，我们都可以用 nums[i-1] 简单代替 nums[i]，所以从长度上说，二者的结果没有本质区别
        // 而对于所有以 nums[i] 结尾的上升摆动序列，它应该是 [0, i-1] 序列中所有下降摆动序列中最长的那一个，加上 nums[i] 本身构成的
        // 这里证明一下这一论断的正确性：
        // 1. [0, i-1] 之间的最长下降摆动序列是以 nums[i-1] 结尾的，那么此时由于 nums[i-1] < nums[i]
        // 我们显然可以这样进行递推
        // 2. [0, i-1] 之间的最长下降摆动序列不是以 nums[i-1] 结尾的，那么此时假设它以 nums[k] (0 <= k < i-1) 结尾
        // 我们必然有 nums[k] <= nums[i-1]，否则，我们可以把 nums[i-1] 接到 nums[k] 后面，形成一个更长的摆动序列
        // 所以 nums[i] > nums[i-1] >= nums[k]
        // 因而我们就必然可以确定：nums[k] 后面可以接 nums[i]，构成更长的摆动序列
        // 如果当前元素等于上一个元素，那么 [0, i] 之间的元素能形成的下降摆动子序列很明显和 [0, i-1] 是完全一样的
        // 如果当前元素比上一个元素小，那么和上面第一种情况的分析是正好镜像的 
        if(nums[i] > nums[i-1])
        {
            dp[i][0] = dp[i-1][0];
            dp[i][1] = dp[i-1][0]+1;
        }
        else if(nums[i] < nums[i-1])
        {
            dp[i][0] = dp[i-1][1]+1;
            dp[i][1] = dp[i-1][1];
        }
        else
        {
            dp[i][0] = dp[i-1][0];
            dp[i][1] = dp[i-1][1];
        }
        ans = max({ans, dp[i][0], dp[i][1]});
    }
    return ans;
}