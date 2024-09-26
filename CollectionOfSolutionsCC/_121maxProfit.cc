#include "Solution.h"

// 暴力 DFS，直接超时
int Leetcode101_200::Solution::maxProfit(vector<int>& prices)
{
    // 本题是一道经典的动态规划类题目，不过还是那句话，直接思考转移方程会比较困难，我们先从 DFS 入手
    // 问题是：计算出我们如果只能选择在某一天买入这支股票，并在未来某一天卖出，这样能获取的最大利润是多少？
    // 我们不难发现，如果按照题目问题的这种方式定义递归问题，那么显然比较难进行递归
    // 假设我们定义 dfs(i, j) 代表我们在第 i 天买入这支股票，并在第 j 天卖出这支股票，能够获得的利润
    // 这样我们显然没有利用到任何子问题的信息，我们只是简单地对整个数组进行一次二维遍历，对这个结果进行计算，这样 O(n^2) 的解法显然不够好
    // 换句话说，这个方案根本不是 DFS，它只是暴力算法
    // 那么如何更换定义方案呢？
    // 我们转换一下问题的问法：
    // 计算出我们如果在某一天手上不持有股票，并且已经对股票买卖完成了一次，此时该天能够获取利润的最大值是多少？
    // 这样，我们可以定义出下面的回调函数：
    // dfs(i, hold, cnt)
    // 代表的是第 i 天，我们手上 (hold == true -> 持有股票，hold == false -> 不持有股票)，并且已经对股票买卖完成了 cnt 次，此时该天能够获取利润的最大值
    // 我们想知道的就是，min(i from 1 to prices.size()) dfs(i, false, 1) 这个结果
    // 考虑这种递归方案能否使用子问题的解：
    // 如果我们要求解 dfs(i, hold, cnt)
    // 那么考虑分 hold 的情况进行讨论：
    // 1. hold == true，即我们手上第 i 天持有这支股票，那么我们前一天的状态可以是持有或者不持有这支股票，且买卖股票的次数应该和当天(第 i 天)是一样的，因为我们无论如何都只多只会涉及一次新的买入
    // 即有 dfs(i, true, cnt) = max(dfs(i-1, true, cnt), dfs(i-1, false, cnt)-prices[i-1])
    // 上面注意下标和顺序序号之间的转换，要有一个-1
    // 2. hold == false，即我们手上第 i 天不持有这支股票，那么我们前一天的状态也可以是持有或者不持有这支股票，切买卖股票的次数可能会小于当天的买卖次数，因为我们可能前一天手里还持有着股票，当前卖掉了
    // 即有 dfs(i, false, cnt) = max(dfs(i-1, true, cnt-1)+prices[i-1], dfs(i-1, false, cnt))
    // 最后根据上面总结的公式输出最终的全局答案即可
    // 全局的最终答案
    int res = 0;
    vector<int> preMax(prices.size(), INT_MAX);
    preMax[0] = prices[0];
    for(int i = 1; i < prices.size(); ++i)
    {
        preMax[i] = min(preMax[i-1], prices[i]);
    }
    function<int(int, bool, int)> dfs = [&](int i, bool hold, int cnt)
    {
        // 递归结束情况1：i == 1
        // 此时我们知道我们处在第一天，如果我们手里持有股票，那么最大的利润就是买了今天的股票
        // 如果我们手里不持有股票，那么最大的利润就是0，因为我们没买任何股票
        if(i == 1)
        {
            return (hold ? -prices[i-1] : 0);
        }
        // cnt == 0，此时我们还没有做任何的交易，理论上需要分 hold 为 true 或 false 进行讨论
        if(cnt == 0)
        {
            if(hold)
            {
                // 这里赋值的时候需要取的是当前位置以及左侧所有位置上相反数最大的那个值，这可以用一个前缀数组做到
                return -preMax[i-1];
            }
            return 0;
        }
        if(hold)
        {
            // 手里持有股票的情况
            return max(dfs(i-1, true, cnt), dfs(i-1, false, cnt)-prices[i-1]);
        }
        // 手里不持有股票的情况
        return max(dfs(i-1, true, cnt-1)+prices[i-1], dfs(i-1, false, cnt));
    };
    // 对函数进行调用即可
    for(int i = 1; i <= prices.size(); ++i)
    {
        res = max(res, dfs(i, false, 1));
    }
    return res;
}

// 第二版：DFS + 记忆化优化，几乎是压线通过的
int maxProfitMemo(vector<int>& prices)
{
    // 本题是一道经典的动态规划类题目，不过还是那句话，直接思考转移方程会比较困难，我们先从 DFS 入手
    // 问题是：计算出我们如果只能选择在某一天买入这支股票，并在未来某一天卖出，这样能获取的最大利润是多少？
    // 我们不难发现，如果按照题目问题的这种方式定义递归问题，那么显然比较难进行递归
    // 假设我们定义 dfs(i, j) 代表我们在第 i 天买入这支股票，并在第 j 天卖出这支股票，能够获得的利润
    // 这样我们显然没有利用到任何子问题的信息，我们只是简单地对整个数组进行一次二维遍历，对这个结果进行计算，这样 O(n^2) 的解法显然不够好
    // 换句话说，这个方案根本不是 DFS，它只是暴力算法
    // 那么如何更换定义方案呢？
    // 我们转换一下问题的问法：
    // 计算出我们如果在某一天手上不持有股票，并且已经对股票买卖完成了一次，此时该天能够获取利润的最大值是多少？
    // 这样，我们可以定义出下面的回调函数：
    // dfs(i, hold, cnt)
    // 代表的是第 i 天，我们手上 (hold == true -> 持有股票，hold == false -> 不持有股票)，并且已经对股票买卖完成了 cnt 次，此时该天能够获取利润的最大值
    // 我们想知道的就是，min(i from 1 to prices.size()) dfs(i, false, 1) 这个结果
    // 考虑这种递归方案能否使用子问题的解：
    // 如果我们要求解 dfs(i, hold, cnt)
    // 那么考虑分 hold 的情况进行讨论：
    // 1. hold == true，即我们手上第 i 天持有这支股票，那么我们前一天的状态可以是持有或者不持有这支股票，且买卖股票的次数应该和当天(第 i 天)是一样的，因为我们无论如何都只多只会涉及一次新的买入
    // 即有 dfs(i, true, cnt) = max(dfs(i-1, true, cnt), dfs(i-1, false, cnt)-prices[i-1])
    // 上面注意下标和顺序序号之间的转换，要有一个-1
    // 2. hold == false，即我们手上第 i 天不持有这支股票，那么我们前一天的状态也可以是持有或者不持有这支股票，切买卖股票的次数可能会小于当天的买卖次数，因为我们可能前一天手里还持有着股票，当前卖掉了
    // 即有 dfs(i, false, cnt) = max(dfs(i-1, true, cnt-1)+prices[i-1], dfs(i-1, false, cnt))
    // 最后根据上面总结的公式输出最终的全局答案即可
    // 全局的最终答案
    int res = 0;
    vector<int> preMax(prices.size(), INT_MAX);
    preMax[0] = prices[0];
    // 记忆化数组
    vector<vector<vector<int>>> memo(prices.size()+1, vector<vector<int>>(2, vector<int>(2, INT_MIN)));
    for(int i = 1; i < prices.size(); ++i)
    {
        preMax[i] = min(preMax[i-1], prices[i]);
    }
    function<int(int, bool, int)> dfs = [&](int i, bool hold, int cnt)
    {
        // 递归结束情况1：i == 1
        // 此时我们知道我们处在第一天，如果我们手里持有股票，那么最大的利润就是买了今天的股票
        // 如果我们手里不持有股票，那么最大的利润就是0，因为我们没买任何股票
        if(i == 1)
        {
            return (hold ? -prices[i-1] : 0);
        }
        // cnt == 0，此时我们还没有做任何的交易，理论上需要分 hold 为 true 或 false 进行讨论
        if(cnt == 0)
        {
            if(hold)
            {
                // 这里赋值的时候需要取的是当前位置以及左侧所有位置上相反数最大的那个值，这可以用一个前缀数组做到
                return -preMax[i-1];
            }
            return 0;
        }
        if(memo[i][hold][cnt] != INT_MIN)
        {
            return memo[i][hold][cnt];
        }
        if(hold)
        {
            // 手里持有股票的情况
            memo[i][hold][cnt] = max(dfs(i-1, true, cnt), dfs(i-1, false, cnt)-prices[i-1]);
            return memo[i][hold][cnt];
        }
        memo[i][hold][cnt] = max(dfs(i-1, true, cnt-1)+prices[i-1], dfs(i-1, false, cnt));
        // 手里不持有股票的情况
        return memo[i][hold][cnt];
    };
    // 对函数进行调用即可
    for(int i = 1; i <= prices.size(); ++i)
    {
        res = max(res, dfs(i, false, 1));
    }
    return res;
}

// 第三版：完全优化的 DP 方案
int maxProfitDP(vector<int>& prices)
{
     // 全局答案
    int res = 0;
    // 根据上面的 DFS 逻辑定义的 DP 数组，后面或许可以压缩空间
    vector<vector<vector<int>>> dp(prices.size()+1, vector<vector<int>>(2, vector<int>(2, 0)));
    // 边界情况直接计算，不能应用下面的递推逻辑
    // 这里对应 DFS 中所有 i == 1 的情况
    for(int hold = 0; hold <= 1; ++hold)
    {
        for(int cnt = 0; cnt <= 1; ++cnt)
        {
            dp[1][hold][cnt] = (hold ? -prices[0] : 0);
        }
    }
    // 这里对应的是上面 DFS 方法中 cnt == 0 的情况
    // 注意到上面 DFS 方法中用到的前缀数组可以在初始化 dp 数组的时候同时计算出来
    // 我们相当于直接用 dp[k][true][0] 本身作为了一个前缀数组，存储的是前 k 个元素中花销最小的那一个的值的相反数
    // 注意 i == 1 的情况已经计算完成了，这里不需要再次计算，可以直接从 i == 2 进行递推
    for(int i = 2; i <= prices.size(); ++i)
    {
        dp[i][true][0] = max(dp[i-1][true][0], -prices[i-1]);
    }
    // 这里主体递推的时候就可以省去 i == 1 和 cnt == 0 的两个分支了
    for(int i = 2; i <= prices.size(); ++i)
    {
        for(int hold = 0; hold <= 1; ++hold)
        {
            // 这里之所以写成一个循环，是为了后面拓展到可以多次交易的情况，比如最多允许5次交易，只需要把这里的 cnt <= 1 改成 cnt <= 5 就可以了
            for(int cnt = 1; cnt <= 1; ++cnt)
            {
                if(hold)
                {
                    dp[i][hold][cnt] = max(dp[i-1][true][cnt], dp[i-1][false][cnt]-prices[i-1]);
                }
                else
                {
                    dp[i][hold][cnt] = max(dp[i-1][true][cnt-1]+prices[i-1], dp[i-1][false][cnt]);
                    // 只有当 hold == false 并且 cnt == 1 时，这个结果才是我们想要的可能为答案的结果，对全局的 res 进行更新
                    if(cnt == 1)
                    {
                        res = max(res, dp[i][hold][1]);
                    }
                }
            }
        }
    }
    return res;
}

// 第四版：完全优化的 DP 方案 + 空间压缩优化
int maxProfitDPOpt(vector<int>& prices)
{
    // 第三版的三维数组一看更新策略其实就应该感觉到，不是最优的空间利用率，肯定是可以从立方体压缩到平面的(对于本题的要求，压缩到平面其实就只剩下常数个结点了)
    // 我们画一个三维的坐标系，模拟一下填写立方体的过程就不难看出哪些变量需要临时存储，哪些可以更新过后就丢弃了
    // 最后可以压缩到只剩一个平面内的四个变量
    // 两个记忆化的临时变量
    int memo0 = 0, memo1 = 0;
    int res = 0;
    // 其实只有四个变量
    vector<vector<int>> dp(2, vector<int>(2, 0));
    // 初始情况，对应 i == 1 的情况
    for(int hold = 0; hold < 2; ++hold)
    {
        for(int cnt = 0; cnt < 2; ++cnt)
        {
            dp[hold][cnt] = (hold ? -prices[0] : 0);
        }
    }
    // 初始情况，对应 cnt == 0 的情况，鉴于第三版中的经验，初始情况下我们不需要进行任何计算了
    // 主体进行递推
    for(int i = 2; i <= prices.size(); ++i)
    {
        // 每次记录值从上一层的两个边界值开始记录
        // 想要理解记录这两个变量的原因的可以画一个三维坐标系模拟一下递推的过程
        memo0 = dp[true][0];
        memo1 = dp[false][1];
        // 对应第三版代码中 cnt == 0 的情况，由于我们是在滚动一个平面，这个边界值需要在每次更新面坐标的时候进行更新
        dp[true][0] = max(dp[true][0], -prices[i-1]);
        for(int cnt = 1; cnt <= 1; ++cnt)
        {
            for(int hold = 0; hold < 2; ++hold)
            {
                if(hold)
                {
                    // 画出三维坐标系模拟一下递推过程即可理解这里更新的逻辑
                    memo0 = dp[true][cnt];
                    dp[hold][cnt] = max(dp[true][cnt], memo1-prices[i-1]);
                }
                else
                {
                    // 画出三维坐标系模拟一下递推过程即可理解这里更新的逻辑
                    memo1 = dp[false][cnt];
                    dp[hold][cnt] = max(memo0+prices[i-1], dp[false][cnt]);
                    if(cnt == 1)
                    {
                        res = max(res, dp[hold][1]);
                    }
                }
            }
        }
    }
    return res;
}