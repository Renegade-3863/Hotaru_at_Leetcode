#include "Solution.h"

// 第一版：暴力 DFS，不加任何记忆化，只通过了 17 个样例就 TLE 了
vector<int> Leetcode601_700::Soltuion::cheapestJump(vector<int>& coins, int maxJump)
{
    // 很明显的 DP 类问题
    // 我们思考如何定义最优子问题
    // 定义 dfs(cur, idx) 代表在 idx 下标，并且已经走出了 cur 这个成本的情况下，走完全程需要的最少成本
    // 那么我们可以进行这样的递推：
    // 1. 如果 idx 为 n，那么直接返回 cur 即可，因为我们现在就在结尾处
    // 2. 如果 coins[idx-1] 为 -1，那么我们应该返回 INT_MAX，代表从这个位置无论如何也没法到达最后的目标
    // 3. 如果 1 和 2 都不成立，那么进入这个分支
    // 遍历所有可能的下一步 j，计算 dfs(cur+coins[j], idx+j)
    // 检查结果最小、并且下一步成本也最小的那一个
    // 把这个路径结点记录到我们的 "下一步数组" res 中即可
    // 我们最后要求的最大子问题就是 dfs(coins[0], 1)
    int n = coins.size();
    vector<int> res(n, -1);
    function<int(int, int)> dfs = [&](int cur, int idx) -> int
    {
        // 情况1
        if(idx == n)
        {
            return cur;
        }
        // 情况2
        if(coins[idx-1] == -1)
        {
            return INT_MAX;
        }
        // 情况3
        // ans 记录本轮循环找出的最小结果
        // nxtStep 记录本轮找出的最优下一步
        int ans = 0x3f3f3f3f, nxtStep = n+1;
        for(int j = 1; idx+j <= n && j <= maxJump; ++j)
        {
            int tmp = INT_MAX;
            // 根据题目要求，这里如果 coins[idx+j-1] 为 -1，那么我们其实是没法跳过去的。。错了几个样例才明白。。
            if(coins[idx+j-1] != -1)
            {
                tmp = dfs(cur+coins[idx+j-1], idx+j);
            }
            if(tmp < ans)
            {
                ans = tmp;
                nxtStep = idx+j;
            }
            else if(tmp == ans)
            {
                // 如果是成本相同的一步，那么我们考虑选择字典序更小的那一步
                nxtStep = coins[nxtStep-1] > coins[idx+j-1] ? idx+j : nxtStep;
            }
        }
        // 遍历完成，如果我们找到了可行的下一步，那么我们把 nxtStep 记录到 "下一步数组" 中即可
        if(nxtStep != n+1)
        {
            res[idx-1] = nxtStep;
        }
        // cout << nxtStep << endl;
        return ans;
    };
    dfs(coins[0], 1);
    // 处理完成后，我们针对 res 数组，按顺序走出这个路径即可
    for(int k = 0; k < n; ++k)
    {
        if(res[k] != -1)
        {
            --res[k];
        }
    }
    res[n-1] = n;
    vector<int> ret;
    int curIdx = 0;
    for(int i = 0; i < n; ++i)
    {
        if(i == curIdx && res[curIdx] != -1)
        {
            ret.push_back(curIdx+1);
            curIdx = res[curIdx];
        }
    }
    return ret;
}

// 第二版：优化 DFS，加上一个记忆化数组
vector<int> cheapestJump(vector<int>& coins, int maxJump)
{
    // 很明显的 DP 类问题
    // 我们思考如何定义最优子问题
    // 定义 dfs(cur, idx) 代表在 idx 下标，并且已经走出了 cur 这个成本的情况下，走完全程需要的最少成本
    // 那么我们可以进行这样的递推：
    // 1. 如果 idx 为 n，那么直接返回 cur 即可，因为我们现在就在结尾处
    // 2. 如果 coins[idx-1] 为 -1，那么我们应该返回 INT_MAX，代表从这个位置无论如何也没法到达最后的目标
    // 3. 如果 1 和 2 都不成立，那么进入这个分支
    // 遍历所有可能的下一步 j，计算 dfs(cur+coins[j], idx+j)
    // 检查结果最小、并且下一步成本也最小的那一个
    // 把这个路径结点记录到我们的 "下一步数组" res 中即可
    // 我们最后要求的最大子问题就是 dfs(coins[0], 1)
    int n = coins.size();
    vector<int> res(n, -1);
    // 用一个二维哈希表模拟 [cur][idx] 这种记录
    unordered_map<int, unordered_map<int, int>> memo;
    function<int(int, int)> dfs = [&](int cur, int idx) -> int
    {
        // 情况1
        if(idx == n)
        {
            return cur;
        }
        // 情况2
        if(coins[idx-1] == -1)
        {
            return INT_MAX;
        }
        if(memo.count(cur) && memo[cur].count(idx))
        {
            return memo[cur][idx];
        }
        // 情况3
        // ans 记录本轮循环找出的最小结果
        // nxtStep 记录本轮找出的最优下一步
        int ans = 0x3f3f3f3f, nxtStep = n+1;
        for(int j = 1; idx+j <= n && j <= maxJump; ++j)
        {
            int tmp = INT_MAX;
            // 根据题目要求，这里如果 coins[idx+j-1] 为 -1，那么我们其实是没法跳过去的。。错了几个样例才明白。。
            if(coins[idx+j-1] != -1)
            {
                tmp = dfs(cur+coins[idx+j-1], idx+j);
            }
            if(tmp < ans)
            {
                ans = tmp;
                nxtStep = idx+j;
            }
            else if(tmp == ans)
            {
                // 如果是成本相同的一步，那么我们考虑选择字典序更小的那一步
                nxtStep = coins[nxtStep-1] > coins[idx+j-1] ? idx+j : nxtStep;
            }
        }
        // 遍历完成，如果我们找到了可行的下一步，那么我们把 nxtStep 记录到 "下一步数组" 中即可
        if(nxtStep != n+1)
        {
            res[idx-1] = nxtStep;
        }
        memo[cur][idx] = ans;
        return ans;
    };
    dfs(coins[0], 1);
    // 处理完成后，我们针对 res 数组，按顺序走出这个路径即可
    for(int k = 0; k < n; ++k)
    {
        if(res[k] != -1)
        {
            --res[k];
        }
    }
    res[n-1] = n;
    vector<int> ret;
    int curIdx = 0;
    for(int i = 0; i < n; ++i)
    {
        if(i == curIdx && res[curIdx] != -1)
        {
            ret.push_back(curIdx+1);
            curIdx = res[curIdx];
        }
    }
    return ret;
}

// 第三版，去除不必要的冗余维度
vector<int> cheapestJump(vector<int>& coins, int maxJump)
{
    // 这一版就不写 DFS 模式了，直接用 DP 来写
    // 上面两种方法，我们都引入了 cur 这个值
    // 实际上我们会发现，在后续计算的过程中，我们的 cur 并没有起到任何独特的作用，在比较过程中，不等号两侧如果同时减去这个 cur 值，结果完全等价
    // 所以我们可以优化掉 dfs 的一个维度
    // 定义 dfs(idx) 为从 idx 开始运动，到达 n 所需的最小字典序的成本值
    // 在这个过程中填写 res 数组，最后回溯即可，整体的流程和前两种方法完全一致
    int n = coins.size();
    vector<int> res(n, -1);
    vector<int> memo(n, -1);
    function<int(int)> dfs = [&](int idx) -> int
    {
        if(idx == n)
        {
            return 0;
        }
        if(memo[idx-1] != -1)
        {
            return memo[idx-1];
        }
        int ans = 0x3f3f3f3f, nxtStep = n+1;
        for(int j = 1; idx+j <= n && j <= maxJump; ++j)
        {
            int tmp = INT_MAX;
            if(coins[idx+j-1] != -1)
            {
                tmp = coins[idx+j-1]+dfs(idx+j);
            }
            if(tmp < ans)
            {
                ans = tmp;
                nxtStep = idx+j;
            }
            else if(tmp == ans)
            {
                nxtStep = coins[nxtStep-1] > coins[idx+j-1] ? idx+j : nxtStep;
            }
        }
        // 遍历完成，如果我们找到了可行的下一步，那么我们把 nxtStep 记录到 "下一步数组" 中即可
        if(nxtStep != n+1)
        {
            res[idx-1] = nxtStep;
        }
        memo[idx-1] = ans;
        return ans;
    };
    dfs(1);
    // 处理完成后，我们针对 res 数组，按顺序走出这个路径即可
    for(int k = 0; k < n; ++k)
    {
        if(res[k] != -1)
        {
            --res[k];
        }
    }
    res[n-1] = n;
    vector<int> ret;
    int curIdx = 0;
    for(int i = 0; i < n; ++i)
    {
        if(i == curIdx && res[curIdx] != -1)
        {
            ret.push_back(curIdx+1);
            curIdx = res[curIdx];
        }
    }
    return ret;
}