#include "Solution.h"

// 下面这种错误答案记录一下，本质上是有问题的
// 1. 2+min(dfs((n+i-1)%n, j+1), dfs((i+1)%n, j+1)); 这句递推在 j == m-1 的时候就是错的
// 2. 没有很好的避免无限递归的机制，因为递推流程是带 %n 部分的，所以下面的代码理论上会无限递归下去，导致栈溢出
int Leetcode501_600::Soltuion::findRotateSteps(string ring, string key)
{
    // 很好玩的一道题，本质是动态规划，至于是怎么想到的，我们先来考察一下本题的描述：
    // 首先，题目要求的答案是 "拼写出关键词中所有字符的最少步数"，我们学过的，能用于求解这种 "最少方案" 的算法，无非就是：贪心、BFS以及动态规划
    // BFS 和 DP 在本质上区别不大，而这道题又不具备那么明显的状态结点属性
    // 而贪心本质上是由动态规划优化而来的算法，所以我们以 DP 的角度入手这道题是完全合理的
    // 不过在正式开始实现前，还是需要确认这道题是真的可以用子问题递推的模式来解决
    // 我们考察一下题目细节：
    // 不难看出，可以定义出下面的子问题：
    // dfs(i, j) 代表从当前状态：ring 中 ring[i] 指向 12:00 方向，而 key[j] 是下一个要填写的字符
    // 上面这种情况下，完成拼写操作需要的最少操作步数
    // 这种定义模式很方便递推：
    // 题目给我们的两种操作步骤，一种是顺时针旋转，另一种是逆时针旋转
    // 第一种对应的就是新状态 dfs((n+i-1)%n, j+1)，这里，n 指代的是 ring 的长度，因为 i-1 可能会导致下标变为负数，我们进行 +n 和 %n 操作来标准化下标值到 [0, n-1] 之间
    // 第二种对应的就是新状态 dfs((i+1)%n, j+1)，这里 n 指代的是 ring 的长度
    // 反过来考虑，假设我们想求解出 dfs(i, j)
    // 那么无非就是上面两种情况构成了 dfs(i, j) 的子问题
    // 只不过从定义上反过来了而已
    // 我们定义子问题函数即可
    int m = key.size(), n = ring.size();
    function<int(int, int)> dfs = [&](int i, int j) -> int 
    {
        // 决定一下基本情况：
        // 当 j >= m，m 为 key 的长度时，我们就不用进一步计算，可以直接返回了
        // 因为此时整体的 key 字符串已经处理完毕了
        if(j >= m)
        {
            // 不需要任何步数，返回 0 即可
            return 0;
        }
        // 其它情况下，需要考虑如何通过子问题递推
        // 注意，如果当前指向 12:00 的这个字符，也就是 ring[i]，等于我们要处理的这个字符 key[j]
        // 那么我们返回 2+min(dfs((n+i-1)%n, j+1), dfs((i+1)%n, j+1));
        // 也就是：按下一次按钮，处理掉当前这个字符，之后考虑旋转，并继续处理下一个字符 key[j+1]
        // 否则，当前这个 ring[i] 不等于 key[j]，那么我们不能按下按钮并结束 key[j] 的处理，需要考虑旋转转盘
        // 也就是返回 1+min(dfs((n+i-1)%n, j), dfs((i+1)%n), j);
        if(ring[i] == key[j])
        {
            return 2+min(dfs((n+i-1)%n, j+1), dfs((i+1)%n, j+1));
        }
        // 别忘了旋转的那一步！
        return 1+min(dfs((n+i-1)%n, j), dfs((i+1)%n, j));
    };
    return dfs(0, 0);
}

// DP 的路子没走通，结合上面出现无限递归的原因，考虑是因为没有记录 "访问过的结点" 这一情况
// 我们考虑记录这一状态，之后重新规划整个算法
// 我们标记一个数组 memo[i][j]，代表：当前有 ring[i] 指向 12:00
int findRotateSteps(string ring, string key)
{
    int m = key.size(), n = ring.size();
    // visited 用于记录某个状态 (ring[i] 和 key[j]) 是否已经在 BFS 中访问过了
    vector<vector<int>> visited(n, vector<int>(m, 0));
    // 使用一个队列，存储所有当前活跃的 "状态"
    queue<pair<int, int>> q;
    // 压入第一种状态，从 ring[0] 对准 12:00，key[j] 为当前要匹配的字符的情况开始
    q.push(make_pair<int, int>(0, 0));
    // steps 用于记录最终的步骤数
    int steps = 0;
    // 当没有活跃状态时结束循环
    while(!q.empty())
    {
        int len = q.size();
        ++steps;
        for(int i = 0; i < len; ++i)
        {
            // 取出队头状态
            auto& cur = q.front();
            // 根据当前状态进行后续递推
            // 两种情况
            // 1. 当前字符可以匹配
            // 那么新状态是 (i, j+1)
            // 2. 当前字符不可以匹配
            // 那么我们有两种旋转转盘的方法
            // 1) 逆时针旋转
            // 2) 顺时针旋转
            // 我们在遇到 (i, m) 时退出即可
            if(ring[cur.first] == key[cur.second])
            {
                if(cur.second+1 < m && !visited[cur.first][cur.second+1])
                {
                    visited[cur.first][cur.second+1] = true;
                    q.emplace(cur.first, cur.second+1);
                }
                // 同步移动已经到达了结果，直接返回 steps 作为结果即可，因为移动是同步的
                else if(cur.second+1 == m)
                {
                    return steps;
                }
            }
            else
            {
                // 不能匹配，需要旋转
                // 第一种，逆时针旋转一格
                if(!visited[(cur.first+n-1)%n][cur.second])
                {
                    visited[(cur.first+n-1)%n][cur.second] = true;
                    q.emplace((cur.first+n-1)%n, cur.second);
                }
                if(!visited[(cur.first+1)%n][cur.second])
                {
                    visited[(cur.first+1)%n][cur.second] = true;
                    q.emplace((cur.first+1)%n, cur.second);
                }
            }
            q.pop();
        }
    }
    // 不存在对应解法，返回 -1 (理论上不会执行到这一行)
    return -1;
}