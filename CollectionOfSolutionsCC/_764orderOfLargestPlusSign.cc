#include "Solution.h"

int Leetcode701_800::Solution::orderOfLargestPlusSign(int n, vector<vector<int>>& mines)
{
    // 思路并不难的一道题
    // 我们可以这样来处理这道题
    // 首先，预处理出一个信息数组 info
    // 这个数组保存这样的信息：
    // 从 (i, j) 开始，往 dir 方向，能够走出的最远距离
    // 知道了这个信息后，我们便可以按下面的方法进行遍历：
    // 我们定义一个 "已知的最大加号臂长" 值 len
    // 对于每一个格子 (i, j)
    // 先检查 (i, j, 0), (i, j, 1), (i, j, 2), (i, j, 3) 四个方向是否都能延伸到 len 那么长
    // 如果能，那么我们进一步尝试 len+1，如果可以进一步延展，那么更新 len
    // 直到不能再扩展 len 为止
    // 最后遍历完成后，最终的 len 值就是我们要的答案
    // 初始时，info 中每一结点的每个方向上的最远距离值都初始化为 0
    vector<vector<vector<int>>> info(n, vector<vector<int>>(n, vector<int>(4, 0))); 
    // 之后我们可以对这个数组进行初始化
    // 写到这里：怎么初始化？？
    // 我们可以这样来做
    // 两轮遍历
    // 第一轮从左上到右下，处理每个结点的 0 和 1 方向（也就是 left 和 up 两个方向）
    // 这种情况下，我们可以保证遍历到的每一个结点 (i, j) 的左侧和上方结点的 left 和 up 方向上都包含了正确的数据
    // 但是在开始处理前，我们会发现，题目给出的数据使用起来并不方便
    // 我们可以考虑使用哈希表进行转储
    unordered_map<int, unordered_set<int>> memo;
    for(const auto& mine : mines)
    {
        // 遍历每一个为 0 的格子，把它保存到 memo 中
        memo[mine[0]].insert(mine[1]);
    }
    // 转储完成，我们可以开始进行预处理了
    // 如果 (0, 0) 格子上是个 0，那么我们初始化 info(0, 0, 0) 为 0，即经过 (0, 0) 往上直着走没有可行的 1 路径
    // 否则，我们初始化为 1，代表有长度为 1 的结果
    if(memo.count(0) && memo[0].count(0))
    {
        info[0][0][0] = 0;
    }
    else
    {
        info[0][0][0] = 1;
    }
    for(int i = 1; i < n; ++i)
    {
        // 先处理第一列
        // 只有当前格子为 1 的时候，我们才能从上方接 1 过来
        if(memo.count(i) && memo[i].count(0))
        {
            continue;
        }
        info[i][0][0] = info[i-1][0][0]+1;
        info[i][0][1] = 1;
    }
    if(memo.count(0) && memo[0].count(0))
    {
        info[0][0][1] = 0;
    }
    else
    {
        info[0][0][1] = 1;
    }
    for(int j = 1; j < n; ++j)
    {
        // 再处理第一行
        // 只有当前格子为 1 的时候，我们才能从左侧接 1 过来
        if(memo.count(0) && memo[0].count(j))
        {
            continue;
        }
        info[0][j][1] = info[0][j-1][1]+1;
        info[0][j][0] = 1;
    }
    // 之后从左上到右下进行遍历
    for(int i = 1; i < n; ++i)
    {
        for(int j = 1; j < n; ++j)
        {
            if(memo.count(i) && memo[i].count(j))
            {
                continue;
            }
            info[i][j][0] = info[i-1][j][0]+1;
            info[i][j][1] = info[i][j-1][1]+1;
        }
    }
    // 处理完成，我们考虑再进行从右下到左上的遍历
    // 先处理 (n-1, n-1) 这个格子
    if(memo.count(n-1) && memo[n-1].count(n-1))
    {
        info[n-1][n-1][2] = 0;
        info[n-1][n-1][3] = 0;
    }
    else
    {
        info[n-1][n-1][2] = 1;
        info[n-1][n-1][3] = 1;
    }
    // 之后处理最后一行和最后一列
    for(int i = n-2; i >= 0; --i)
    {
        if(memo.count(i) && memo[i].count(n-1))
        {
            continue;
        }
        info[i][n-1][2] = info[i+1][n-1][2]+1;
        info[i][n-1][3] = 1;
    }
    for(int j = n-2; j >= 0; --j)
    {
        if(memo.count(n-1) && memo[n-1].count(j))
        {
            continue;
        }
        info[n-1][j][2] = 1;
        info[n-1][j][3] = info[n-1][j+1][3]+1;
    }
    // 再从右下往左上处理一遍
    for(int i = n-2; i >= 0; --i)
    {
        for(int j = n-2; j >= 0; --j)
        {
            if(memo.count(i) && memo[i].count(j))
            {
                continue;
            }
            info[i][j][2] = info[i+1][j][2]+1;
            info[i][j][3] = info[i][j+1][3]+1;
        }
    }
    // 至此，预处理完成，我们可以最后一轮遍历了
    // 当前，我们知道的最优结果就是 0
    int len = 0;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            // 对于 (i, j) 这个格子
            // 首先检查四个方向上对应距离为 len 的格子是否可以访问到
            // 也就是 (i-len, j), (i, j+len), (i+len, j), (i, j-len)
            if(i-len < 0 || j+len >= n || i+len >= n || j-len < 0)
            {
                // 只要有一个方向不合法，我们就可以跳过这个格子了，它一定不会有更优的解
                continue;
            }
            // 同时，如果 (i, j) 本身是 0，那么我们也可以跳过
            if(memo.count(i) && memo[i].count(j))
            {
                continue;
            }
            // 否则，这个格子可能可以扩展到对应的这四个格子上
            // 我们可以尝试进行扩展
            // 检查这四个格子对应的 "可继续扩展值" 中最小的那一个，作为阈值
            int dist = INT_MAX;
            dist = min(dist, info[i][j][0]);
            dist = min(dist, info[i][j][3]);
            dist = min(dist, info[i][j][2]);
            dist = min(dist, info[i][j][1]);
            // 如果 dist 为 0，那么说明我们同样没法得到更优的解
            // 而如果 dist 非 0，那么我们可以把 len 往外面再延展对应长度
            len = max(len, dist);
        }
    }
    return len;
}