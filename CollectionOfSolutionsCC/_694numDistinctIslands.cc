#include "Solution.h"

int Leetcode601_700::Soltuion::numDistinctIslands(vector<vector<int>>& grid)
{
    // 正常的 DFS 问题，不难做，思路理清即可顺利完成
    // 我们定义一个从一个值为 1 (陆地) 切入，遍历完所有与它同属于一个岛屿的陆地的函数 dfs
    // 定义四个延伸方向
    const int dirs[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    int m = grid.size(), n = grid[0].size();
    function<void(int, int)> dfs = [&](int i, int j) -> void
    {
        if(grid[i][j] == 0)
        {
            // 如果当前格是一个 0，那么我们直接返回即可，不用进一步处理了
            return;
        }
        // 否则，当前格是一个 1，那么我们可以考虑把当前格子从 1 修改成 0，之后往四个方向扩散
        grid[i][j] = 0;
        for(int k = 0; k < 4; ++k)
        {
            int nxti = i+dirs[k][0], nxtj = j+dirs[k][1];
            // 只有合法的，并且为 1 的下一个格子，我们才对它继续调用 dfs 函数
            if(nxti >= 0 && nxti < m && nxtj >= 0 && nxtj < n && grid[nxti][nxtj])
            {
                dfs(nxti, nxtj);
            }
        }
        // 四个方向均已遍历完成，我们返回即可
        return;
    };
    int res = 0;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            // 如果 grid[i][j] 为 1，我们就找到了一个新的岛屿，对它调用 dfs 即可
            if(grid[i][j])
            {
                ++res;
                dfs(i, j);
            }
        }
    }
    // res 就是答案
    return res;
}

// 第一版写的时候想当然了，漏掉了题目中的一个关键信息：
// 我们要找的是：形状不同的岛屿数量
// 那么我们就需要一种机制，来检查一个岛屿的形状之前是否出现过，有几种可能可行的思路：
// 1. 哈希
// 我们可以尝试记录 dfs 函数遍历每个岛屿的路径形式
// 假设：
// 两个岛屿如果形状相同，那么 dfs 从保证从最左侧进入这种岛屿的话，我们可以保证 dfs 遍历它们的路径都是相同的
// 感谢评论区大佬 @xiumao 的提醒
// 反应过来这里路径编码起始和二叉树的 BFS 编码类似
// 我们需要记录那些 "尝试过，但没法走通" 的方向
// 比如下面两个图像：
/*
    1 1 0
    0 1 1
    0 0 0
    1 1 1
    0 1 0

    这两个图像，我们只需要记录 dfs，在它访问到一个走不通的路径时，添加一个标记即可
    这个思想和之前判断相同二叉树的哈希编码思想是完全一致的
*/

int numDistinctIslands(vector<vector<int>>& grid)
{
    // 定义遍历顺序
    const int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    // 固定的四个方向，右、下、左、上
    const char syms[4] = {'R', 'D', 'L', 'U'};
    int m = grid.size(), n = grid[0].size();
    // 暂存路径的数组，存储的是 "L/R" 序列，所以我们存字符串即可
    string path;
    unordered_set<string> memo;
    int res = 0;
    // dfs(i, j)，把从 (i, j) 开始的路径上的结点标记为 0，并把相对路径存到 path 中
    function<void(int, int)> dfs = [&](int i, int j) -> void
    {
        grid[i][j] = 0;
        for(int k = 0; k < 4; ++k)
        {
            int nxti = i+dirs[k][0], nxtj = j+dirs[k][1];
            // 只有合法的，并且为 1 的下一个格子，我们才对它继续调用 dfs 函数
            if(nxti >= 0 && nxti < m && nxtj >= 0 && nxtj < n && grid[nxti][nxtj])
            {
                // 把对应的方向字符添加到 path 中即可
                path.push_back(syms[k]);
                dfs(nxti, nxtj);
            }
            // 否则，这个方向走不通，我们需要添加一个特殊字符来进行区分
            else
            {
                // 我们用星号 
                path.push_back('*');
            }
        }
    };
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(grid[i][j])
            {
                // 重置 path 字符串
                path = "";
                dfs(i, j);
                // 检查 path 是否存在于记录哈希表 memo 中
                if(memo.count(path) == 0)
                {
                    ++res;
                    memo.insert(path);
                }
            }
        }
    }
    return res;
}