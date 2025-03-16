#include "Solution.h"

int Leetcode601_700::Soltuion::cutOffTree(vector<vector<int>>& forest)
{
    // 比较经典的 BFS 类问题
    // 因为题目要找出的是 "最小步数"
    // 不过注意一个细节，题目要求完成的是 "从低到高的顺序砍倒所有的树"
    // 所以我们在 BFS 的时候需要维护一个 "当前砍倒的最高树的高度"
    // 而同时，题目限定了：没有两棵树的高度会是相同的
    // 这就给我们提供了一种思路：
    // 我们维护一个有序集合，这个集合保存每一个可能需要被删除的元素的值 (按从小到大的顺序排列)
    // 我们在 BFS 遍历的过程中，只有遍历到当前最矮的，还没被砍掉的树的时候，才砍倒这棵树，并移动上面集合的指针
    // 直到我们砍光所有的树，才结束 BFS 遍历
    // 换句话说，如果 BFS 某一步遍历到了一棵不是最矮未被砍倒的树的树，我们不能砍它，因为这样就不满足从低到高砍的要求了
    // 明确了这一点，之后就是看代码的实现细节了
    // 首先，完整遍历一轮 forest 数组，填充一个数组 memo
    vector<int> memo;
    int m = forest.size(), n = forest[0].size();
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            // 只有是一棵树的时候，我们才进行插入
            if(forest[i][j] != 0 && forest[i][j] != 1)
            {
                memo.push_back(forest[i][j]);
            }
        }
    }
    // 排序
    sort(memo.begin(), memo.end());
    // 插入完成，考虑开始执行 BFS
    // q 内保存所有可以走出去的下一步格子坐标 (x, y)
    queue<pair<int, int>> q;
    // 初始，只能走到 (0, 0)，而这一步不算总步数
    // down 记录砍倒的树的总数
    int steps = -1, down = 0, tot = memo.size();
    q.push(make_pair<int, int>(0, 0));
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    while(!q.empty() && down < tot)
    {
        int len = q.size();
        for(int k = 0; k < len; ++k)
        {
            // 取出一个点坐标
            auto& [x, y] = q.front();
            // 检查当前格子的值，如果是一棵树，考虑把它砍倒
            if(forest[x][y] > 1)
            {
                // 但是只有 forest[x][y] == memo[down] 的时候，我们才能砍这棵树
                if(forest[x][y] == memo[down])
                {
                    // 砍树+移动 down 指针
                    forest[x][y] = 1;
                    ++down;
                }
                // 否则，这棵树不能砍倒
                // 我们什么也不能做
            }
            // 之后考虑如何移动
            // 我们往四个方向探查，检查是否有可以移动的下一步格子 (非 0) 的即可
            for(int i = 0; i < 4; ++i)
            {
                int nxtx = x+dirs[i][0], nxty = y+dirs[i][1];
                // 取出下一步的可能坐标，检查合法性
                if(nxtx >= 0 && nxtx < m && nxty >= 0 && nxty < n && forest[nxtx][nxty] >= 1)
                {
                    // 可以走，我们把这个坐标添加到 q 中即可
                    q.emplace(nxtx, nxty);
                }
            }
            // 当前结点处理完成，弹出即可
            q.pop();
        }
        // 多走了一层，步数加一
        ++steps;
    }
    // 一共有 memo.size() 棵树，我们只需要检查 down 是否等于 memo.size() 即可
    // 如果不等，那说明没有全部砍倒，返回 -1 即可
    return tot == down ? steps : -1;
}

// 先看这里：第一版的代码没法处理无法砍倒所有树的情况，因为 BFS 内部允许往一个值为 1 的格子走，即使这样走已经没法在后续砍倒任何一棵树了
// 归根结底，原因在于 BFS 过程并不了解整张图的当前状态，所以做出了不断运动，但永远无法结束的选择
// 我们需要一种机制来完成对是否可全砍倒这件事的检查
// 换句话说，需要检查 "是否存在一条二分了整张图的 0 链"
// 我们可以再引入一个单纯的 BFS，确认整张图中是否存在任何一个 "孤岛"
// 如果存在孤岛，那么直接返回 -1 即可
int cutOffTree(vector<vector<int>>& forest)
{
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    vector<int> memo;
    // 额外记录四个数组 row, col, dia, anti_dia
    int m = forest.size(), n = forest[0].size();
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            // 只有是一棵树的时候，我们才进行插入
            if(forest[i][j] != 0 && forest[i][j] != 1)
            {
                memo.push_back(forest[i][j]);
            }
        }
    }
    int tot = memo.size();
    // 在进行后续处理之前，我们确保大前提：可以走通
    queue<pair<int, int>> check;
    check.emplace(0, 0);
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    visited[0][0] = true;
    int cnt = 0;
    while(!check.empty())
    {
        auto& [x, y] = check.front();
        // 这轮 BFS，不回头，我们用一个 visited 数组记录所有已经访问过的结点信息
        for(int k = 0; k < 4; ++k)
        {
            int nxtx = x+dirs[k][0], nxty = y+dirs[k][1];
            // 检查合法性
            if(nxtx >= 0 && nxtx < m && nxty >= 0 && nxty < n && forest[nxtx][nxty] > 0 && !visited[nxtx][nxty])
            {
                check.emplace(nxtx, nxty);
                visited[nxtx][nxty] = true;
                if(forest[nxtx][nxty] > 1)
                {
                    ++cnt;
                }
            }
        }
        check.pop();
    }
    // 不可全部访问，那么直接返回 -1 即可
    if(cnt < tot)
    {
        return -1;
    }
    // 排序
    sort(memo.begin(), memo.end());
    // 插入完成，考虑开始执行 BFS
    // q 内保存所有可以走出去的下一步格子坐标 (x, y)
    queue<pair<int, int>> q;
    // 初始，只能走到 (0, 0)，而这一步不算总步数
    // down 记录砍倒的树的总数
    int steps = -1, down = 0;
    q.push(make_pair<int, int>(0, 0));
    while(!q.empty() && down < tot)
    {
        int len = q.size();
        for(int k = 0; k < len; ++k)
        {
            // 取出一个点坐标
            auto& [x, y] = q.front();
            // 检查当前格子的值，如果是一棵树，考虑把它砍倒
            if(forest[x][y] > 1)
            {
                // 但是只有 forest[x][y] == memo[down] 的时候，我们才能砍这棵树
                if(forest[x][y] == memo[down])
                {
                    // 砍树+移动 down 指针
                    forest[x][y] = 1;
                    ++down;
                }
                // 否则，这棵树不能砍倒
                // 我们什么也不能做
            }
            // 之后考虑如何移动
            // 我们往四个方向探查，检查是否有可以移动的下一步格子 (非 0) 的即可
            for(int i = 0; i < 4; ++i)
            {
                int nxtx = x+dirs[i][0], nxty = y+dirs[i][1];
                // 取出下一步的可能坐标，检查合法性
                if(nxtx >= 0 && nxtx < m && nxty >= 0 && nxty < n && forest[nxtx][nxty] >= 1)
                {
                    // 可以走，我们把这个坐标添加到 q 中即可
                    q.emplace(nxtx, nxty);
                }
            }
            // 当前结点处理完成，弹出即可
            q.pop();
        }
        // 多走了一层，步数加一
        ++steps;
    }
    // 一共有 memo.size() 棵树，我们只需要检查 down 是否等于 memo.size() 即可
    // 如果不等，那说明没有全部砍倒，返回 -1 即可
    return tot == down ? steps : -1;
}

// 依然超时：个人认为原因在于第二个 BFS 遍历没有使用 visited 数组，导致进行了太多实际上没用的 BFS 遍历
// 实在没办法了，求助了下三叶姐的题解 。。。
// 大佬们的思路总是清奇的
// 他们绕开了题目本身具备的这种 "回头" 特性
// 个人认为他们可能相关的题目做的比较多，知道 BFS 带上回头一定会超时
// 所以转而进一步分析题目的特点
// 从本质上来说，因为题目限制了 "每棵树的高度都不相同"，并且 "需要按从低到高的顺序砍树"
// 所以实际上砍树的最终路径 (如果存在) 就一定是唯一固定的了
// 那么我们可以用 BFS 的方式找出每一对数值上相邻的树下标之间的最短路径
// 并把这些子路径长度累加，就是最终路径的长度了
// 不过对树高度进行排序的部分代码依然可以挪过来用
int cutOffTree(vector<vector<int>>& forest)
{
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int m = forest.size(), n = forest[0].size();
    // 考虑实现一个这样的 BFS 函数：
    // bfs(x1, y1, x2, y2) -> int，用于返回从坐标 (x1, y1) -> (x2, y2) 之间的最短路径长度的 bfs 函数
    function<int(int, int, int, int)> bfs = [&](int x1, int y1, int x2, int y2) -> int
    {
        // 依然是用一个队列来完成操作
        queue<pair<int, int>> q;
        // 压入起点坐标
        q.emplace(x1, y1);
        // steps 记录总步数
        int steps = 0;
        // visited 保证 bfs 不会回头
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        visited[x1][y1] = true;
        while(!q.empty())
        {
            int len = q.size();
            for(int i = 0; i < len; ++i)
            {
                // 取出一条路径的尾结点
                auto& [x, y] = q.front();
                // 如果这个结点就是 (x2, y2)，那么直接退出循环即可
                if(x == x2 && y == y2)
                {
                    return steps;
                }
                // 否则，检查这个结点的四个相邻格子是否合法，如果合法并且可以挪动过去，那么我们就压队
                for(int k = 0; k < 4; ++k)
                {
                    int nxtx = x+dirs[k][0], nxty = y+dirs[k][1];
                    if(nxtx >= 0 && nxtx < m && nxty >= 0 && nxty < n && forest[nxtx][nxty] >= 1 && !visited[nxtx][nxty])
                    {
                        q.emplace(nxtx, nxty);
                        visited[nxtx][nxty] = true;
                    }
                }
                q.pop();
            }
            ++steps;
        }
        // 如果不是因为 x == x2 && y == y2 而退出，反而是因为 q.empty() 退出，那么说明我们没有找到任何的可以从 (x1, y1) -> (x2, y2) 的路径，此时返回 -1 即可
        return -1;
    };
    // mapping 记录每棵树对应的结点位置
    unordered_map<int, pair<int, int>> mapping;
    vector<int> memo;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            // 只有是一棵树的时候，我们才进行插入
            if(forest[i][j] != 0 && forest[i][j] != 1)
            {
                memo.push_back(forest[i][j]);
                mapping[forest[i][j]] = make_pair<int&, int&>(i, j);
            }
        }
    }
    // 排序
    sort(memo.begin(), memo.end());
    // 之后遍历 memo 中的每一对树，使用上面定义好的 bfs 函数检查它们之间的最短距离
    // 累加所有距离之后，结果就计算完成了
    int res = 0;
    int length = memo.size();
    // 注意：如果 (0, 0) 位置上不是数值最小的一棵树，我们需要先找出这个起点到第一棵树的最短距离
    if(forest[0][0] != memo[0])
    {
        res = bfs(0, 0, mapping[memo[0]].first, mapping[memo[0]].second);
    }
    for(int i = 1; i < length; ++i)
    {
        int dist = bfs(mapping[memo[i-1]].first, mapping[memo[i-1]].second, mapping[memo[i]].first, mapping[memo[i]].second);
        if(dist == -1)
        {
            return -1;
        }
        res += dist;
    }
    return res;
}