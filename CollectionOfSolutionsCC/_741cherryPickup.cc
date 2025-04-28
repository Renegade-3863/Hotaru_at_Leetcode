#include "Solution.h"

// 观前提醒：下面这种思路是错的，不过还是归档，记录一下错误的原因：
// 本题状态并不统一，换句话说，在回来的时候，我们没法知道某个格子上是否还有樱桃（只要理解了这句话，这道题就明白了）
int Leetcode701_800::Soltuion::cherryPickup(vector<vector<int>>& grid)
{
    // 思考一下如何定义 dfs 函数
    // 这道题有一种神奇的归纳性质：
    // 我们从 (0, 0) 走到 (n-1, n-1)，一定会走 n-1 步
    // 从这个角度来思考，我们可以尝试下面的定义方式：
    // dfs1(i, j) 表示从 (0, 0) 到 (i, j) 的情况下，可以拿到的最多樱桃数
    // 思考如何进行状态转移：
    // dfs(i, j) 可以从 (i-1, j) 或者 (i, j-1) 走过来
    // 所以，我们可以根据 grid[i][j] 此时的值来决定转移方程中的数值
    // 1. 如果 grid[i][j] == 0，那么当前是一个空地
    // 所以 dfs(i, j) = max(dfs(i-1, j), dfs(i, j-1))
    // 2. 如果 grid[i][j] == 1，那么当前是一个樱桃
    // 所以 dfs(i, j) = max(dfs(i-1, j), dfs(i, j-1)) + 1
    // 3. 如果 grid[i][j] == -1，那么当前格子里有荆棘，我们没法走这个格子
    // 那么我们返回 -1 即可，代表当前格子不能走
    // 结束条件为：i == n-1 && j == n-1
    int n = grid.size();
    vector<vector<int>> memo(n, vector<int>(n, -2));
    function<int(int, int)> = [&](int i, int j) -> int
    {
        // 结束条件
        if(i == 0 && j == 0)
        {
            // 从 (0, 0) 走到 (0, 0)，那么我们只需要检查 (0, 0) 格子是什么值即可
            memo[0][0] = grid[0][0];
            return grid[i][j];
        }
        // 其它边界条件
        fi(i < 0 || j < 0 || i >= n || j >= n)
        {
            // 超出边界，返回 -1
            return -1;
        }
        if(memo[i][j] != -2)
        {
            // 如果 memo[i][j] 已经被计算过了，那么直接返回即可
            return memo[i][j];
        }
        if(grid[i][j] == -1)
        {
            // 当前格子是荆棘，返回 -1
            memo[i][j] = -1;
            return -1;
        }
        int ret = 0;
        // if(grid[i][j] == 1)
        // {
        //     // 当前格子是樱桃，那么我们要摘下这个樱桃，这样一定是最优的
        //     ++ret;
        //     // 注意，如果 dfs(i-1, j) 和 dfs(i, j-1) 都是 -1，那么我们就不能走这个格子了
        //     // 此时返回值应该是 -1;
        //     ret += max(dfs(i - 1, j), dfs(i, j - 1));
        //     // 如果 ret 为 0，说明一定是因为当前格子走不到，原有的 1 被两个 dfs 取较大值后的 -1 给消掉了
        //     // 所以此时我们返回 -1 即可
        //     return ret == 0 ? -1 : ret;       
        // }
        // if(grid[i][j] == 0)
        // {
        //     // 正常空地，逻辑上和 grid[i][j] == 1 是一样的
        //     // 所以两部分的代码可以取出来进行整合
        // }
        if(grid[i][j] == 1)
        {
            ++ret;
        }
        int pre = max(dfs(i - 1, j), dfs(i, j - 1));
        memo[i][j] = pre == -1 ? -1 : ret + pre;
        return memo[i][j];
    };
    // 之后是从 (n-1, n-1) 返回 (0, 0) 的过程，我们定义为 dfs2
    // 注意，调用 dfs2 时，dfs1 已经处理完了正向的 memo 部分数值
    // 我们调用 dfs2 就是反向再填一次 memo 数组
    function<int(int, int)> = [&](int i, int j) -> int
    {
        // 结束条件
        if(i == n-1 && j == n-1)
        {
            // 此时我们只需要检查 memo 的 (n-1, n-1) 格子是什么值即可
            return memo[n-1][n-1]+grid[i][j];
        }
        // 其它边界条件
        if(i < 0 || j < 0 || i >= n || j >= n)
        {
            // 超出边界，返回 -1
            return -1;
        }
        if(memo[i][j] != -2)
        {
            // 如果 memo[i][j] 已经被计算过了，那么直接返回即可
            return memo[i][j];
        }
        if(grid[i][j] == -1)
        {
            // 当前格子是荆棘，返回 -1
            // 这里有必要更新吗？留一个疑问
            memo[i][j] = -1;
            return -1;
        }
        int ret = 0;
        if(grid[i][j] == 1)
        {
            ++ret;
        }
        int pre = max(dfs(i+1, j), dfs(i, j+1));
        memo[i][j] = pre == -1 ? -1 : ret+pre;
        return memo[i][j];
    };
    // 我们分别调用 dfs1 和 dfs2 即可
    dfs(n-1, n-1);
    // 上面的函数执行完成后，memo 的正向值就被记录完成了
    // 我们先检查 (n-1, n-1) 是否可达
    if(memo[n-1][n-1] == -1)
    {
        // 如果不可达，那么直接返回 0
        return 0;
    }
    // 否则我们就可以开始 dfs2 了
    dfs2(0, 0);
    // 结果就是 memo[0][0] 
    return memo[0][0];
}

// 借鉴了题解区灵茶大佬的思路，同步了两轮移动流程，把 "先去再回" 的过程转换成 "两个人同时去" 的过程
// 定义下面的 dfs 函数
// dfs(t, i, j) 代表一共走 t 步，其中第一个人走到了 (i, t-i) 这一格，第二个人走到了 (t-j, j) 这一格的情况下，我们可以拿到的最多樱桃数
// 这种定义下，整张图的状态就统一了，所有状态值都是在同样的前提下计算出来的
// 考虑如何进行递推
// 1.1 如果 grid[i][t-i] == -1，那么当前第一个人在的位置没法走到，那么我们返回 -1 即可
// 1.2 如果 grid[t-j][j] == -1，那么当前第二个人在的位置没法走到，我们也返回 -1 
// 2. 1.1 和 1.2 都不成立，那么我们可以走到这个格子，也就是说，我们需要根据 grid[i][t-i] 和 grid[t-j][j] 来进行计算
// 定义一个 ret 值
// 2.1 grid[i][t-i] == 1，那么我们需要取上这个樱桃，并修改 grid 的状态，ret 增加1
// 2.2 grid[i][t-i] == 0，那么我们没法取到樱桃
// 2.3 grid[t-j][j] == 1，那么我们需要取上这个樱桃，并修改 grid 的状态，ret 增加1
// 2.4 grid[t-j][j] == 0，那么我们没法取到樱桃
// 3. 最后，考虑前序状态的递推
// 无非是下面四种情况取最大值：
// 1) 两个人都向下走到达当前位置：
// 那么就是从 dfs(t-1, i-1, j) 走到 dfs(t, i, j)
// 2) 第一个人向下走，第二个人向右走到达当前位置：
// 那么就是从 dfs(t-1, i-1, j-1) 走到 dfs(t, i, j)
// 3) 第一个人向右走，第二个人向下走到达当前位置：
// 那么就是从 dfs(t-1, i, j) 走到 dfs(t, i, j)
// 4) 两个人都向右走到达当前位置：
// 那么就是从 dfs(t-1, i, j-1) 走到 dfs(t, i, j)
// 我们从四个值中取最大的那一个，累加到 ret 中即可
// 也就是 dfs(t, i, j) = max(dfs(t-1, i-1, j), dfs(t-1, i-1, j-1), dfs(t-1, i, j), dfs(t-1, i, j-1)) + ret
// 4. 结束条件：
// 如果 t == 0，那么说明此时两个人都在原点，那么我们只需要检查 grid[0][0] 的值即可
// 如果 grid[0][0] == -1，那么我们返回 0
// 否则我们返回 grid[0][0] 的值即可
// 最后一个小细节：如果某一时刻 (i, t-i) 和 (t-j, j) 重合了，那么我们只能取一次樱桃，此时两个人在同一个格子上
// 最后，写代码就不难了
int cherryPickup(vector<vector<int>>& grid)
{
    int n = grid.size();
    function<int(int, int, int)> dfs = [&](int t, int i, int j) -> int 
    {
        // 结束条件
        if(t == 0)
        {
            return grid[0][0] == -1 ? 0 : grid[0][0];
        }
        // 其它边界条件
        if(i < 0 || t-i < 0 || j < 0 || t-j < 0)
        {
            // 超出边界，返回 -1
            return -1;
        }
        if(grid[i][t-i] == -1 || grid[t-j][j] == -1)
        {
            // 当前格子是荆棘，返回 -1
            return -1;
        }
        int ret = 0;
        if(grid[i][t-i] == 1)
        {
            ++ret;
        }
        if(grid[t-j][j] == 1)
        {
            if(i != t-j || t-i != j)
            {
                ++ret;
            }
            // 否则，重合，我们只取一次樱桃
        }
        // 递推
        int pre = max(dfs(t-1, i-1, j), dfs(t-1, i, j-1));
        pre = max(pre, dfs(t-1, i-1, j-1));
        pre = max(pre, dfs(t-1, i, j));
        if(pre == -1)
        {
            // 如果前序状态不可达，那么我们返回 -1
            return -1;
        }
        // 否则我们就可以返回 ret + pre
        return ret + pre;
    };
    // 结果就是 dfs(2*n-2, n-1, n-1)
    int ans = dfs(2*n-2, n-1, n-1);
    return ans == -1 ? 0 : ans;
}

// 第二版：尝试给 dfs 加上记忆化
int cherryPickup(vector<vector<int>>& grid)
{
    int n = grid.size();
    vector<vector<vector<int>>> memo(2*n-1, vector<vector<int>>(n, vector<int>(n, -2)));
    memo[0][0][0] = grid[0][0];
    function<int(int, int, int)> dfs = [&](int t, int i, int j) -> int 
    {
        // 边界条件
        if(i < 0 || t-i < 0 || j < 0 || t-j < 0)
        {
            // 超出边界，返回 -1
            return -1;
        }
        if(memo[t][i][j] != -2)
        {
            // 如果 memo[t][i][j] 已经被计算过了，那么直接返回即可
            return memo[t][i][j];
        }
        // 结束条件
        if(t == 0)
        {
            return grid[0][0] == -1 ? 0 : grid[0][0];
        }
        if(grid[i][t-i] == -1 || grid[t-j][j] == -1)
        {
            // 当前格子是荆棘，返回 -1
            return -1;
        }
        int ret = 0;
        if(grid[i][t-i] == 1)
        {
            ++ret;
        }
        if(grid[t-j][j] == 1)
        {
            if(i != t-j || t-i != j)
            {
                ++ret;
            }
            // 否则，重合，我们只取一次樱桃
        }
        // 递推
        int pre = max(dfs(t-1, i-1, j), dfs(t-1, i, j-1));
        pre = max(pre, dfs(t-1, i-1, j-1));
        pre = max(pre, dfs(t-1, i, j));
        if(pre == -1)
        {
            memo[t][i][j] = -1;
            // 如果前序状态不可达，那么我们返回 -1
            return -1;
        }
        // 记忆化
        memo[t][i][j] = ret + pre;
        // 否则我们就可以返回 ret + pre
        return memo[t][i][j];
    };
    // 结果就是 dfs(2*n-2, n-1, n-1)
    int ans = dfs(2*n-2, n-1, n-1);
    return ans == -1 ? 0 : ans;
}