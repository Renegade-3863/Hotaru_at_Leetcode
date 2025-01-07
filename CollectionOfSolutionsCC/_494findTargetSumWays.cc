#include "Solution.h"

// 第一版：暴力 DFS，不加任何记忆化，没想到居然能通过，没 TLE。。
int Leetcode401_500::Soltuion::findTargetSumWays(vector<int>& nums, int target)
{
    // 乍一看，最容易想到的算法其实是回溯，不过本题有更高效的背包算法
    // 我们定义这样的函数：dfs(i, k)
    // 含义为：使用 nums 的前 i 个元素进行 "加/减" 的组合，我们得到 k 值的方法数
    // 那么，我们最后需要求的，无非就是 dfs(nums.size(), target) 这个子问题的解了
    // 考虑一下如何利用子问题进行推导
    // 对于当前第 i 个元素 nums[i-1]，我们无非有两种选择，加上它或者减去它
    // 这样就会有两个 "上一个子问题" 状态
    // 换句话说，就是：
    // dfs(i, k) = dfs(i-1, k-nums[i-1])+dfs(i-1, k+nums[i-1])
    function<int(int, int)> dfs = [&](int i, int k) -> int
    {
        // 定义一个基本情况
        // 当 i 等于 1 的时候，我们判断 nums[0] 是否等于 +k 或 -k，如果等于，返回 1 或者 2，否则返回 0 即可
        // 题目把 +0 和 -0 也考虑进来了，所以这里需要使用这种求和的方法。。
        if(i == 1)
        {
            return (nums[0] == k) + (nums[0] == -k);
        }
        // 其它情况下，我们可以利用上面的子问题进行递推
        // nums[i] 采用加法 + nums[i] 采用减法
        return dfs(i-1, k+nums[i-1]) + dfs(i-1, k-nums[i-1]);
    };
    // 调用这个函数即可
    return dfs(nums.size(), target);
}

// 第二版：对 DFS 算法添加一个记忆化哈希表，进行加速
int findTargetSumWays(vector<int>& nums, int target)
{
    // 乍一看，最容易想到的算法其实是回溯，不过本题有更高效的背包算法
    // 我们定义这样的函数：dfs(i, k)
    // 含义为：使用 nums 的前 i 个元素进行 "加/减" 的组合，我们得到 k 值的方法数
    // 那么，我们最后需要求的，无非就是 dfs(nums.size(), target) 这个子问题的解了
    // 考虑一下如何利用子问题进行推导
    // 对于当前第 i 个元素 nums[i-1]，我们无非有两种选择，加上它或者减去它
    // 这样就会有两个 "上一个子问题" 状态
    // 换句话说，就是：
    // dfs(i, k) = dfs(i-1, k-nums[i-1])+dfs(i-1, k+nums[i-1])
    // 添加一个记忆化哈希表
    // 因为 k 值的范围包含负数，所以我们可能需要一种能存储负下标的结构来保存对应的索引值
    // 这用一个嵌套在 vector 中的哈希表再合适不过了
    // 注意，memo 数组的那一个维度肯定是需要手动初始化的
    vector<unordered_map<int, int>> memo(nums.size(), unordered_map<int, int>());
    function<int(int, int)> dfs = [&](int i, int k) -> int
    {
        // 定义一个基本情况
        // 当 i 等于 1 的时候，我们判断 nums[0] 是否等于 +k 或 -k，如果等于，返回 1，否则返回 0 即可
        if(i == 1)
        {
            return (nums[0] == k) + (nums[0] == -k);
        }
        // 如果对应的结果已经计算过，我们就可以直接使用记忆的数据，而不用递归求解
        int addVal = 0, subVal = 0;
        if(memo[i-2].count(k+nums[i-1]) == 0)
        {
            memo[i-2][k+nums[i-1]] = dfs(i-1, k+nums[i-1]);
        }
        if(memo[i-2].count(k-nums[i-1]) == 0)
        {
            memo[i-2][k-nums[i-1]] = dfs(i-1, k-nums[i-1]);
        }
        // 其它情况下，我们可以利用上面的子问题进行递推
        // nums[i] 采用加法 + nums[i] 采用减法
        return memo[i-2][k+nums[i-1]] + memo[i-2][k-nums[i-1]];
    };
    // 调用这个函数即可
    return dfs(nums.size(), target);
}

// 至于各大题解中抄来抄去的那种奇怪的背包思路，个人认为，在面试高度紧张的情况下，想到那种奇怪的目标定义方法属实不现实，当然这是对大多数同学来说的
// 有兴趣的，可以去学习一下官解提到的那种可以压缩成一维的解法，这里本人不在赘述，意义不大
