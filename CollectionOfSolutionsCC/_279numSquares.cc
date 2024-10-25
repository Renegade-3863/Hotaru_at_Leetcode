#include "Solution.h"

// 第一版：暴力 DFS，不带记忆化，TLE
int Leetcode201_300::Solution::numSquares(int n)
{
    // 一道很明显的 DP 类问题，一点小细节在于，我们事先不知道任何可以用于组成 n 的完全平方数的信息
    // 我们需要预处理，获取所有小于 n 的完全平方数的信息
    vector<int> components;
    int check = 1;
    // 添加一个条件用于避免整形溢出
    while(check <= INT_MAX/check && check * check <= n)
    {
        components.push_back(check*check);
        ++check;
    }
    // for(int i = 0; i < components.size(); ++i)
    // {
    //     cout << components[i] << " ";
    // }
    // 循环结束后，我们就拿到了所有不大于 n 的完全平方数的板，可以使用这些数来执行算法了
    // 先考虑自顶向下的 DFS 过程
    // 定义这样一种过程
    // dfs(i, k)
    // 代表构成整数 i，并且用的最大的完全平方数是 components[k] 所需的最少完全平方数个数
    // 那么最后的结果就应该是：
    // min(dfs(n, k)) for all k from (0 to components.size()-1)
    function<int(int, int)> dfs = [&](int i, int k)
    {
        // 基本情况1：i == 0
        // 此时我们直接返回 0 即可，因为不需要任何完全平方数就可以组合出0这个值
        if(i == 0)
        {
            return 0;
        }
        // 基本情况2: i < components[k]
        // 此时我们也不可能拿到任何合法情况，返回一个 -1 代表不合法即可
        if(i < components[k])
        {
            return -1;
        }
        // 对于其它一般情况，我们可以针对 components[k] 被使用的次数来往回递推
        // 使用次数
        int cnt = 1;
        // 记录这个完全平方数
        int board = components[k];
        // 只有当前 i 值足够容纳 cnt 次 board 这个完全平方数的时候，我们才进行递归计算
        int ret = INT_MAX;
        while(i-cnt*board >= 0)
        {
            // 注意，这里我们需要提供的新的 k 值不能只有 k-1，还需要检查所有更小的 k 值
            // 比如我们要检查的大问题是 dfs(10, 2)
            // 那么这里会进入 dfs(1, 1) 这个子问题
            // 因为 components[1] 是 2，也就是说 board == 4，因而我们实际上不会进入这个循环，而是会直接返回 INT_MAX
            // 这样显然是有问题的，因为我们没有检查 dfs(1, 0)
            for(int j = 0; j <= k; ++j)
            {
                int prev = dfs(i-cnt*board, j);
                // 如果这个前驱结果是 "不合法"，那么我们没必要使用它进行结果更新
                if(prev == -1)
                {
                    continue;
                }
                ret = min(ret, prev+cnt);
            }
            ++cnt;
        }
        // 返回最终结果即可
        return ret;
    };
    int res = INT_MAX;
    for(int k = 0; k < components.size(); ++k)
    {
        res = min(res, dfs(n, k));
    }
    return res;
}

// 第二版：DFS + 记忆化，依旧 TLE
int numSquares(int n)
{
    // 一道很明显的 DP 类问题，一点小细节在于，我们事先不知道任何可以用于组成 n 的完全平方数的信息
    // 我们需要预处理，获取所有小于 n 的完全平方数的信息
    vector<int> components;
    int check = 1;
    // 添加一个条件用于避免整形溢出
    while(check <= INT_MAX/check && check * check <= n)
    {
        components.push_back(check*check);
        ++check;
    }
    // 添加一个记忆化数组
    vector<vector<int>> memo(n+1, vector<int>(components.size(), -1));
    // 循环结束后，我们就拿到了所有不大于 n 的完全平方数的板，可以使用这些数来执行算法了
    // 先考虑自顶向下的 DFS 过程
    // 定义这样一种过程
    // dfs(i, k)
    // 代表构成整数 i，并且用的最大的完全平方数是 components[k] 所需的最少完全平方数个数
    // 那么最后的结果就应该是：
    // min(dfs(n, k)) for all k from (0 to components.size()-1)
    function<int(int, int)> dfs = [&](int i, int k)
    {
        // 基本情况1：i == 0
        // 此时我们直接返回 0 即可，因为不需要任何完全平方数就可以组合出0这个值
        if(i == 0)
        {
            return 0;
        }
        // 基本情况2: i < components[k]
        // 此时我们也不可能拿到任何合法情况，返回一个 -1 代表不合法即可
        if(i < components[k])
        {
            return -1;
        }
        if(memo[i][k] != -1)
        {
            return memo[i][k];
        }
        // 对于其它一般情况，我们可以针对 components[k] 被使用的次数来往回递推
        // 使用次数
        int cnt = 1;
        // 记录这个完全平方数
        int board = components[k];
        // 只有当前 i 值足够容纳 cnt 次 board 这个完全平方数的时候，我们才进行递归计算
        int ret = INT_MAX;
        while(i-cnt*board >= 0)
        {
            // 注意，这里我们需要提供的新的 k 值不能只有 k-1，还需要检查所有更小的 k 值
            // 比如我们要检查的大问题是 dfs(10, 2)
            // 那么这里会进入 dfs(1, 1) 这个子问题
            // 因为 components[1] 是 2，也就是说 board == 4，因而我们实际上不会进入这个循环，而是会直接返回 INT_MAX
            // 这样显然是有问题的，因为我们没有检查 dfs(1, 0)
            for(int j = 0; j <= k; ++j)
            {
                int prev = dfs(i-cnt*board, j);
                // 如果这个前驱结果是 "不合法"，那么我们没必要使用它进行结果更新
                if(prev == -1)
                {
                    continue;
                }
                ret = min(ret, prev+cnt);
            }
            ++cnt;
        }
        // 返回最终结果即可
        memo[i][k] = ret;
        return ret;
    };
    int res = INT_MAX;
    for(int k = 0; k < components.size(); ++k)
    {
        res = min(res, dfs(n, k));
    }
    return res;
}

// 第三版：进一步时间复杂度优化，纯 DFS，无记忆化
int numSquares(int n)
{
    // 一道很明显的 DP 类问题，一点小细节在于，我们事先不知道任何可以用于组成 n 的完全平方数的信息
    // 我们需要预处理，获取所有小于 n 的完全平方数的信息
    vector<int> components;
    int check = 1;
    // 添加一个条件用于避免整形溢出
    while(check <= INT_MAX/check && check * check <= n)
    {
        components.push_back(check*check);
        ++check;
    }
    // 我们上面递归问题的定义方式有些问题，导致递归过程中进行了多次循环，考虑对定义本身进行优化
    // 换用下面的定义方法
    // dfs(i, k) 代表的是，用前 k 个完全平方数，构成结果 i，所需的最少完全平方数个数
    // 那么，递归问题可以转化成：
    // if(i >= components[k-1])
    // 那么此时我们可以选择：
    // 1. 取一个 components[k-1]，剩下的 i-components[k-1] 用前 k 个继续构造
    // 2. 不取 components[k-1]，直接用前 k-1 个构造 i
    // 即：dfs(i, k) = min(dfs(i-components[k-1], k), dfs(i, k-1))
    // if(i < components[k-1])
    // 那么此时我们只能选择不取 components[k-1]，直接用前 k-1 个构造 i
    // 即：dfs(i, k) = dfs(i, k-1)
    // 这样定义，最后的结果就是：
    // dfs(n, components.size())
    // 即：用所有可行的完全平方数构造出 n 的最小所需数字个数
    // 至于 "取多少个" 的问题
    // 我们会发现，取多个的时候，dfs(i-cnt*components[k-1], k) 这个问题是包含在 dfs(i-components[k-1], k) 中的
    // 因为我们在计算 dfs(i-components[k-1], k) 的步骤中一定会调用到 dfs(i-2*components[k-1], k), dfs(i-3*components[k-1], k), ..., dfs(i-cnt*components[k-1], k) 这些子问题
    // 而最后这些值的最小值就是 dfs(i-components[k-1], k)
    // 因而我们没必要再用一轮循环去检查这些值
    function<int(int, int)> dfs = [&](int i, int k)
    {
        // 定义基本情况
        // 意思是，如果我们取到了前一种完全平方数，这里其实就是 1 这个数，我们只能是拿 i 个 1，所以返回 i 
        if(k == 1)
        {
            return i;
        }
        // 一般情况
        if(i < components[k-1])
        {
            return dfs(i, k-1);
        }
        else
        {
            return min(dfs(i-components[k-1], k)+1, dfs(i, k-1));
        }
    };
    // 调用
    return dfs(n, components.size());
}

// 第四版：使用记忆化对 DFS 进行加速
int numSquares(int n)
{
    // 一道很明显的 DP 类问题，一点小细节在于，我们事先不知道任何可以用于组成 n 的完全平方数的信息
    // 我们需要预处理，获取所有小于 n 的完全平方数的信息
    vector<int> components;
    int check = 1;
    // 添加一个条件用于避免整形溢出
    while(check <= INT_MAX/check && check * check <= n)
    {
        components.push_back(check*check);
        ++check;
    }
    vector<vector<int>> memo(n+1, vector<int>(components.size()+1, -1));
    // 我们上面递归问题的定义方式有些问题，导致递归过程中进行了多次循环，考虑对定义本身进行优化
    // 换用下面的定义方法
    // dfs(i, k) 代表的是，用前 k 个完全平方数，构成结果 i，所需的最少完全平方数个数
    // 那么，递归问题可以转化成：
    // if(i >= components[k-1])
    // 那么此时我们可以选择：
    // 1. 取一个 components[k-1]，剩下的 i-components[k-1] 用前 k 个继续构造
    // 2. 不取 components[k-1]，直接用前 k-1 个构造 i
    // 即：dfs(i, k) = min(dfs(i-components[k-1], k), dfs(i, k-1))
    // if(i < components[k-1])
    // 那么此时我们只能选择不取 components[k-1]，直接用前 k-1 个构造 i
    // 即：dfs(i, k) = dfs(i, k-1)
    // 这样定义，最后的结果就是：
    // dfs(n, components.size())
    // 即：用所有可行的完全平方数构造出 n 的最小所需数字个数
    // 至于 "取多少个" 的问题
    // 我们会发现，取多个的时候，dfs(i-cnt*components[k-1], k) 这个问题是包含在 dfs(i-components[k-1], k) 中的
    // 因为我们在计算 dfs(i-components[k-1], k) 的步骤中一定会调用到 dfs(i-2*components[k-1], k), dfs(i-3*components[k-1], k), ..., dfs(i-cnt*components[k-1], k) 这些子问题
    // 而最后这些值的最小值就是 dfs(i-components[k-1], k)
    // 因而我们没必要再用一轮循环去检查这些值
    function<int(int, int)> dfs = [&](int i, int k)
    {
        if(memo[i][k] != -1)
        {
            return memo[i][k];
        }
        // 定义基本情况
        // 意思是，如果我们取到了前一种完全平方数，这里其实就是 1 这个数，我们只能是拿 i 个 1，所以返回 i 
        if(k == 1)
        {
            memo[i][k] = i;
            return i;
        }
        // 一般情况
        if(i < components[k-1])
        {
            memo[i][k] = dfs(i, k-1);
            return memo[i][k];
        }
        else
        {
            memo[i][k] = min(dfs(i-components[k-1], k)+1, dfs(i, k-1));
            return memo[i][k];
        }
    };
    // 调用
    return dfs(n, components.size());
}

// 第四版：转换成自底向上的 DP 写法
int numSquares(int n)
{
    // 一道很明显的 DP 类问题，一点小细节在于，我们事先不知道任何可以用于组成 n 的完全平方数的信息
    // 我们需要预处理，获取所有小于 n 的完全平方数的信息
    vector<int> components;
    int check = 1;
    // 添加一个条件用于避免整形溢出
    while(check <= INT_MAX/check && check * check <= n)
    {
        components.push_back(check*check);
        ++check;
    }
    vector<vector<int>> dp(n+1, vector<int>(components.size(), 0));
    // 边界情况设定
    for(int i = 0; i <= n; ++i)
    {
        dp[i][0] = i;
    }
    // 进行递推
    for(int k = 1; k < components.size(); ++k)
    {
        for(int i = 0; i <= n; ++i)
        {
            if(i < components[k])
            {
                dp[i][k] = dp[i][k-1];
            }
            else
            {
                dp[i][k] = min(dp[i-components[k]][k]+1, dp[i][k-1]);
            }
        }
    }
    return dp[n][components.size()-1];
}

// 第五版：对 DP 进行空间优化
int numSquares(int n)
{
    // 一道很明显的 DP 类问题，一点小细节在于，我们事先不知道任何可以用于组成 n 的完全平方数的信息
    // 我们需要预处理，获取所有小于 n 的完全平方数的信息
    vector<int> components;
    int check = 1;
    // 添加一个条件用于避免整形溢出
    while(check <= INT_MAX/check && check * check <= n)
    {
        components.push_back(check*check);
        ++check;
    }
    vector<int> dp(n+1, 0);
    // 初始化第一层
    for(int i = 0; i <= n; ++i)
    {
        dp[i] = i;
    }
    // 进行递推
    for(int k = 1; k < components.size(); ++k)
    {
        for(int i = 0; i <= n; ++i)
        {
            if(i < components[k])
            {
                dp[i] = dp[i];
            }
            else
            {
                dp[i] = min(dp[i-components[k]]+1, dp[i]);
            }
        }
    }
    return dp[n];
}
// 个人总结：DP 的子问题定义方法很有讲究，背包类问题是 DP 问题很经典的一个分支，它的定义模版可能需要进行一些理解性记忆，不然如果定义子问题的角度出错，可能会导致整个代码复杂度上升很多