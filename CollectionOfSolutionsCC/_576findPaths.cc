#include "Solution.h"

// 第一版：暴力 DFS，不加记忆化，会 TLE
int Leetcode501_600::Soltuion::findPaths(int m, int n, int maxMove, int startRow, int startColumn)
{
    // 这道题第一眼看，应该想到两种可行方案：
    // 1. BFS
    // 2. DFS/DP
    // 不过鉴于题目要求我们找出的是 "路径数量"，而不是 "最短路径"
    // 那么我们更倾向于使用 DP 方法
    // 既然要使用 DP 方案，我们先从基本的 DFS 角度入手，考虑如何定义子问题
    // 本着 "问什么，设什么" 的思想，我们设定下面的 DFS 子问题：
    // dfs(x, y, steps) 代表从 (x, y) 出发，最多走 steps 步，能够走出边界的路径数
    // 那么很明显，我们可以有四种递推的方式
    // 分别往上、下、左、右四个方向走即可
    // 即：往左走一步，到达 dfs(x, y-1, steps-1)
    // 往上走一步，到达 dfs(x-1, y, steps-1)
    // 往右走一步，到达 dfs(x, y+1, steps-1)
    // 往下走一步，到达 dfs(x+1, y, steps-1)
    // 这四种子问题的结果之和，就是最后的 dfs(x, y, steps)
    // 最后，我们要求的结果 (球最开始的位置坐标为 [startRow, startColumn])
    // 就是 dfs(startRow, startColumn, maxMove) 这个问题
    // 先把这个函数写出来
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    function<int(int, int, int)> dfs = [&](int x, int y, int steps) -> int
    {
        // 定义一个基本情况：
        // 如果当前点超出了边界范围，那么从边界处到达边界，只有一种走法，就是不走，因为本身就已经在边界中了
        if(x < 0 || x >= m || y < 0 || y >= n)
        {
            return 1;
        }
        // 否则，这是一个正常的格子，不过我们还需要判断，当前是否还有可走的步数
        if(steps <= 0)
        {
            // 如果没有步数了，那么我们直接返回 0 即可，没有步数可走，而又在一个不是边界的位置，那么我们没有任何走法可以走到边界上去
            // 直接返回 0 即可
            return 0;
        }
        // 其它情况下，这是一个正常的格子+还有剩余步数，那么我们递归地往其它四个方向走即可
        // 上面把全局的 "方向数组" 写出来
        // 尝试往四个方向走
        // res 代表总的方法数
        int res = 0;
        for(int i = 0; i < 4; ++i)
        {
            int nxtx = x+dirs[i][0], nxty = y+dirs[i][1];
            // 不用管 （nxtx, nxty) 是不是合法边界，也不用管 steps-1 是否还是一个正数，这些情况我们在上面的基本情况中都已经考虑到了
            // 我们只需要递归就行
            res += dfs(nxtx, nxty, steps-1);
        }
        // 检查完成，返回结果即可
        return res;
    };
    // 我们只需要调用 dfs(startRow, startColumn, maxMove)
    return dfs(startRow, startColumn, maxMove);
}

// 第二版：添加记忆化数组进行加速，可以通过
int findPaths(int m, int n, int maxMove, int startRow, int startColumn)
{
    // 这道题第一眼看，应该想到两种可行方案：
    // 1. BFS
    // 2. DFS/DP
    // 不过鉴于题目要求我们找出的是 "路径数量"，而不是 "最短路径"
    // 那么我们更倾向于使用 DP 方法
    // 既然要使用 DP 方案，我们先从基本的 DFS 角度入手，考虑如何定义子问题
    // 本着 "问什么，设什么" 的思想，我们设定下面的 DFS 子问题：
    // dfs(x, y, steps) 代表从 (x, y) 出发，最多走 steps 步，能够走出边界的路径数
    // 那么很明显，我们可以有四种递推的方式
    // 分别往上、下、左、右四个方向走即可
    // 即：往左走一步，到达 dfs(x, y-1, steps-1)
    // 往上走一步，到达 dfs(x-1, y, steps-1)
    // 往右走一步，到达 dfs(x, y+1, steps-1)
    // 往下走一步，到达 dfs(x+1, y, steps-1)
    // 这四种子问题的结果之和，就是最后的 dfs(x, y, steps)
    // 最后，我们要求的结果 (球最开始的位置坐标为 [startRow, startColumn])
    // 就是 dfs(startRow, startColumn, maxMove) 这个问题
    // 先把这个函数写出来
    const int MOD = 1e9+7;
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    vector<vector<vector<int>>> memo(m, vector<vector<int>>(n, vector<int>(maxMove+1, -1)));
    function<int(int, int, int)> dfs = [&](int x, int y, int steps) -> int
    {
        // 定义一个基本情况：
        // 如果当前点超出了边界范围，那么从边界处到达边界，只有一种走法，就是不走，因为本身就已经在边界中了
        if(x < 0 || x >= m || y < 0 || y >= n)
        {
            return 1;
        }
        // 否则，这是一个正常的格子，不过我们还需要判断，当前是否还有可走的步数
        if(steps <= 0)
        {
            // 如果没有步数了，那么我们直接返回 0 即可，没有步数可走，而又在一个不是边界的位置，那么我们没有任何走法可以走到边界上去
            // 直接返回 0 即可
            return 0;
        }
        // 记忆化加速
        if(memo[x][y][steps] != -1)
        {
            return memo[x][y][steps];
        }
        // 其它情况下，这是一个正常的格子+还有剩余步数，那么我们递归地往其它四个方向走即可
        // 上面把全局的 "方向数组" 写出来
        // 尝试往四个方向走
        // res 代表总的方法数
        int res = 0;
        for(int i = 0; i < 4; ++i)
        {
            int nxtx = x+dirs[i][0], nxty = y+dirs[i][1];
            // 不用管 （nxtx, nxty) 是不是合法边界，也不用管 steps-1 是否还是一个正数，这些情况我们在上面的基本情况中都已经考虑到了
            // 我们只需要递归就行
            res = (res + dfs(nxtx, nxty, steps-1)) % MOD;
        }
        // 检查完成，返回结果即可
        memo[x][y][steps] = res % MOD;
        return memo[x][y][steps];
    };
    // 我们只需要调用 dfs(startRow, startColumn, maxMove)
    return dfs(startRow, startColumn, maxMove);
}

// 第三版：把自顶向下的 DFS 转换成自底向上的 DP 方案 (典型错误答案)
// 为什么这么做不对？
// 有兴趣的可以看一下本人的检讨：
// 实际上 "从某个点出发，只往左或上走的总步骤数" + "从某个点出发，只往右或下走的总步骤数" != "从某个点出发，可以同时往四个方向走的总步骤数"
// 这二者并不是等价关系！！！
int findPaths(int m, int n, int maxMove, int startRow, int startColumn)
{
    // 按照上面两种 DFS 的写法，我们会发现，如果依然按照那个从四个方向递推的式子，我们不能确保求解 dp[x][y][steps] 的时候，四个方向的结果都已经确定
    // 但是，我们可以确保其中的两个 (比如从左上往右下填，我们可以确定左和上两个值)
    // 那么我们就可以搞两轮 DP，一轮统计左上两个方向的结果，另一轮统计右下两个方向的结果
    // 简单证明一下这样做的正确性
    // 1. 从左上往右下递推的时候，我们求解出来的，是 "从当前位置开始，只往左侧或上方走，可以到达边界的总方法数，给定最多走 steps 步"
    // 2. 从右下往左上递推的时候，我们求解出来的，才是 "从当前位置开始，往四个方向走，可以到达边界的总方法数"
    // 因为第一轮的递推，我们已经求解出了那些往左上走的结果值，第二轮累加上往右下走的结果值，就是最终的答案
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(maxMove+1, 0)));
    // 这个是存储最后答案的数组，定义上不同于上面的 dp 数组
    vector<vector<vector<int>>> res(m, vector<vector<int>>(n, vector<int>(maxMove+1, 0)));
    // 四个顺序，依次是 "左、上、右、下"
    const int dirs[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    const int MOD = 1e9+7;
    // 初始化，我们可以把左边界和上边界的值直接求出来，因为此时我们规定只能往左侧和上方走，那么这两条边界的结果就相当于可以直接求出来
    // 左边
    // 左上角的这个格子只有两种走法，一种是往左走，一种是往上走
    for(int steps = 1; steps <= maxMove; ++steps)
    {
        // 无论最多可以走几步，我们都可以断定这个格子只有两种走法 (当前只能往左和上走的假设下)
        dp[0][0][steps] = 2;
        res[0][0][steps] = dp[0][0][steps];
    }
    for(int i = 1; i < m; ++i)
    {
        for(int steps = 1; steps <= maxMove; ++steps)
        {
            // 两种走法，一种是往上走，一种是往左走
            // 注意，往上走，最大可走的步数需要减 1，而 dp[x][y][0] 我们已经初始化为了 0，所以从定义上来说是没问题的
            dp[i][0][steps] = dp[i-1][0][steps-1]+1;
            res[i][0][steps] = dp[i][0][steps];
        }
    }
    // 上边
    for(int j = 1; j < n; ++j)
    {
        for(int steps = 1; steps <= maxMove; ++steps)
        {
            // 两种走法，一种是往左走，一种是往上走
            dp[0][j][steps] = dp[0][j-1][steps-1]+1;
            res[0][j][steps] = dp[0][j][steps];
        }
    }
    // 初始化完成，接下来我们可以从左上往右下先递推一轮
    for(int i = 1; i < m; ++i)
    {
        for(int j = 1; j < n; ++j)
        {
            for(int steps = 1; steps <= maxMove; ++steps)
            {
                // 根据我们上面的修正，这次的递推式丢弃了右和下两个累加项
                // 只找左和上的结果进行累加
                for(int k = 0; k < 2; ++k)
                {
                    int nxti = i+dirs[k][0], nxtj = j+dirs[k][1];
                    dp[i][j][steps] = (dp[i][j][steps]+dp[nxti][nxtj][steps-1])%MOD;
                    // 结果累计到 res 数组中
                    res[i][j][steps] = dp[i][j][steps];
                }
            }
        }
    }
    // 第一轮遍历完成，我们进行第二次初始化，注意，这次进行初始化的时候，对右和下两条边界上的值，需要采用 "累加"，而不是 "直接赋值"，因为原来的值也是答案的一部分，不能进行覆盖
    for(int steps = 1; steps <= maxMove; ++steps)
    {
        // 同样的道理，对于右下角的这个格子，无论最大允许走多少步，我们都可以断定，它一定有两种走法
        dp[m-1][n-1][steps] = 2;
        res[m-1][n-1][steps] += dp[m-1][n-1][steps];
    }
    // 之后，是对右边和下边两条边界的初始化
    // 右边
    // 注意，根据定义关系，我们需要反过来遍历右边和下边
    for(int i = m-2; i >= 0; --i)
    {
        for(int steps = 1; steps <= maxMove; ++steps)
        {
            // 两种走法，一种是往右走，一种是往下走
            // 注意是累加，不要覆盖！！！
            dp[i][n-1][steps] = dp[i+1][n-1][steps-1]+1;
            res[i][n-1][steps] += dp[i][n-1][steps];
        }
    }
    // 下边
    for(int j = n-2; j >= 0; --j)
    {
        for(int steps = 1; steps <= maxMove; ++steps)
        {
            // 两种走法，一种是往下走，一种是往右走
            // 注意是累加，不要覆盖！
            dp[m-1][j][steps] = dp[m-1][j+1][steps-1]+1;
            res[m-1][j][steps] += dp[m-1][j][steps]; 
        }
    }
    // 初始化完成，我们可以进行第二轮遍历
    // 这次需要从右下往左上遍历，注意遍历顺序
    for(int i = m-2; i >= 0; --i)
    {
        for(int j = n-2; j >= 0; --j)
        {
            for(int steps = 1; steps <= maxMove; ++steps)
            {
                for(int k = 2; k < 4; ++k)
                {
                    // 这次只累计右和下两个方向
                    int nxti = i+dirs[k][0], nxtj = j+dirs[k][1];
                    dp[i][j][steps] = (dp[i][j][steps]+dp[nxti][nxtj][steps-1])%MOD;
                    res[i][j][steps] = (res[i][j][steps]+dp[i][j][steps])%MOD;
                }
            }
        }
    }
    // 全部处理完成，返回题目要求我们算的答案即可，可以加一步取模
    return res[startRow][startColumn][maxMove]%MOD;
}

// 第四版：DP 解法修正
int findPaths(int m, int n, int maxMove, int startRow, int startColumn)
{
    if(maxMove == 0)
    {
        return 0;
    }
    const int MOD = 1e9+7;
    // 上面第三版的代码是典型的错误答案，我们这里考虑对其进行修正
    // 我们应该从递推关系式入手：
    // dfs(x, y, steps) = dfs(x-1, y, steps-1)+dfs(x, y+1, steps-1)+dfs(x+1, y, steps-1)+dfs(x, y-1, steps-1)
    // 不难发现，实际上，我们只需要最外层遍历 steps 这个变量，就可以满足前置已知条件了
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(maxMove+1, 0)));
    // 我们按照 "先 steps，再 x 和 y" 的顺序进行遍历即可
    // 所有的边界条件的初始化均已完成 (所有 steps == 0 的情况，结果均为 0)
    // 之后就是按照上面的逻辑进行实际的遍历了
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    // 先初始化所有 steps 为 1 的情况，这是基本情况
    // 同时，很明显，这种情况下，只有四条边上的格子可能有结果需要更新
    // 初始化完成，可以开始进行一般性的遍历了
    for(int steps = 1; steps <= maxMove; ++steps)
    {
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                // 注意，如果是边界上的格子，我们还需要对这个格子的结果值手动进行累加！！！
                if(i == 0)
                {
                    // 是上边的格子，那么我们可以一步往上，走出边界
                    ++dp[i][j][steps];
                }
                if(i == m-1)
                {
                    // 是下边的格子，那么我们可以一步往下，走出边界
                    ++dp[i][j][steps];
                }
                if(j == 0)
                {
                    // 是左边的格子
                    ++dp[i][j][steps];
                }
                if(j == n-1)
                {
                    ++dp[i][j][steps];
                }
                for(int k = 0; k < 4; ++k)
                {
                    int nxti = i+dirs[k][0], nxtj = j+dirs[k][1];
                    // 注意，这里我们需要额外检查 (nxti, nxtj) 是不是一个合法的位置
                    if(nxti < 0 || nxti >= m || nxtj < 0 || nxtj >= n)
                    {
                        // 不合法的点，直接跳过即可
                        continue;
                    }
                    // 是合法的点，累加结果
                    dp[i][j][steps] = (dp[i][j][steps]+dp[nxti][nxtj][steps-1])%MOD;
                }
            }
        }
    }
    // 全部遍历完成，返回题目要求的结果即可
    return dp[startRow][startColumn][maxMove];
}