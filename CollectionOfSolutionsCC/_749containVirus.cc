#include "Solution.h"

int Leetcode701_800::Soltuion::containVirus(vector<vector<int>>& isInfected)
{
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int m = isInfected.size(), n = isInfected[0].size();
    // 内核本质是一个 DFS 问题
    // 题目要求每一轮必须控制所有子感染区中下一轮影响最大（可感染新区域最多）的那一个
    // 所以我们需要一种机制来确定一个子感染区的下一步可感染格子个数
    // 这里定义一个 helper function
    // 假设有这个函数：
    // checkAdj(int i, int j)，用于检测以 (i, j) 为入点的子感染区，当前时间戳上下一步可以感染的最大新格子数量
    // 这个函数需要一个内置的哈希集合，防止多个格子均重复感染同一个非感染区格子的情况
    // 哈希集合
    // 内部存储的 idx 是 i*isInfected[0].size()+j 这个唯一的索引值
    unordered_set<int> memo;
    unordered_set<int> visited;
    vector<vector<int>> snapShot(m, vector<int>(n, 0));
    // 注意，每次更新 timestamp 之后，都要将 memo 清空
    // 探查出来的结果保存在 ret 中返还给调用者
    function<void(int, int, int&)> checkAdj = [&](int i, int j, int& ret) -> void
    {
        // nxt 数组记录下一步 dfs 需要走到的所有格子
        vector<pair<int, int>> nxt;
        // (i, j) 一定是一个感染格，我们先对它的四个相邻格子进行探查
        int idx = i*n+j;
        visited.insert(idx);
        for(const auto& dir : dirs)
        {
            int nxti = i+dir[0], nxtj = j+dir[1];
            // 别忘了检查坐标合法性
            if(nxti < 0 || nxti >= m || nxtj < 0 || nxtj >= n)
            {
                continue;
            }
            // 坐标合法，那么尝试进行处理
            idx = nxti*n+nxtj;
            // 如果这个相邻格是一个感染格，那么记录它，之后进行 DFS
            if(visited.count(idx))
            {
                continue;
            }
            if(isInfected[nxti][nxtj] == 1)
            {
                nxt.emplace_back(nxti, nxtj);
                // 注意，感染格不计入 ret
                continue;
            }
            if(memo.count(idx))
            {
                // 如果这个格子在当前探查层已经被标记过，那么就不再重复标记
                continue;
            }
            // 否则，这个节点还没有被标记，我们需要进行标记
            // 记录这个点为 "已标记"
            memo.insert(idx);
            // 注意，如果 isInfected[nxti][nxtj] 为 2，那么我们不能通过它进一步扩散病毒
            // 对 ret 进行递增
            if(isInfected[nxti][nxtj] == 0)
            {
                ++ret;
            }
        }
        // 当前格处理完成，检查 nxt，如果有相邻的未被标记的感染格，那么就进一步访问
        for(const auto& p : nxt)
        {
            checkAdj(p.first, p.second, ret);
        }
        // dfs 处理结束，直接返回即可
    };
    // 思考：如何表达一个病毒感染区已经被控制了？
    // 我们可以新设定一个标记值，例如 2，代表这个区域中的病毒无法进一步向外扩散
    // 这个标记流程也需要一个额外的 helper function 来进行处理
    // markPts 函数用于把 (i, j) 代表的整个病毒感染区都标记成 2
    function<void(int, int, int&)> markPts = [&](int i, int j, int& res) -> void
    {
        // 先标记 (i, j)
        isInfected[i][j] = 2;
        // 之后递归标记四个相邻格子，如果相邻格子是感染格的话
        for(const auto& dir : dirs)
        {
            int nxti = i+dir[0], nxtj = j+dir[1];
            if(nxti < 0 || nxti >= m || nxtj < 0 || nxtj >= n)
            {
                continue;
            }
            if(isInfected[nxti][nxtj] == 1)
            {
                markPts(nxti, nxtj, res);
            }
            // 否则，这个方向上要安装一面隔离墙，给 res 加 1
            else if(isInfected[nxti][nxtj] == 0)
            {
                ++res;
            }
        }
        // 标记结束，返回即可
    };
    // 注意，我们还需要一个感染逻辑，所有在当前 timestp 没有被隔离的区域，下一个 timestp 上都会向外扩散一轮
    // 这个逻辑很好实现，在每个 timestp 上，处理完了所有的 checkAdj 和 markPts 函数后
    // 再遍历一遍整张图，把所有 1 的相邻格子都标记为 1 即可 （注意，这里要用开始标记前的数组快照）
    // 之后是主循环逻辑
    // timestp 时间戳标记当前所处的时间，每递增 1，病毒感染一轮
    // res 存储最后的结果
    int timestp = 0, res = 0;
    // 主循环，遍历整张图
    // 用一个死循环来做外层循环，模拟病毒不断扩散的过程
    while(true)
    {
        // 每一轮循环对应一个 timestp
        // 故每一轮 for 开始前，我们要清空 visited
        visited.clear();
        int tmp = 0, ret = 0;
        // (marki, markj) 代表要标记的区间的代表格
        int marki = 0, markj = 0;
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                // 检查 (i, j)，如果 (i, j) 没在 memo 中出现过，并且是一个感染格，那么对这个区间下一轮可以感染的格子个数进行统计
                if(visited.find(i*n+j) == visited.end() && isInfected[i][j] == 1)
                {
                    tmp = 0;
                    checkAdj(i, j, tmp);
                    // 每一次探查开始前，我们要清空 memo
                    memo.clear();
                    if(tmp >= ret)
                    {
                        marki = i; markj = j;
                        ret = tmp;
                    }
                }
            }
        }
        // 全部检查完成，需要对 (marki, markj) 代表的范围进行标记
        markPts(marki, markj, res);
        // 最后保存一个 isInfected 此时的快照，用这个快照执行病毒的感染逻辑
        snapShot = isInfected;
        // 注意：如果某一轮 "感染流程" 发现已经没有新的 1 格，即 "可继续感染格" 时，循环就可以整个退出了
        int cntOne = 0;
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(snapShot[i][j] == 1)
                {
                    ++cntOne;
                    for(const auto& dir : dirs)
                    {
                        int nxti = i+dir[0], nxtj = j+dir[1];
                        if(nxti < 0 || nxti >= m || nxtj < 0 || nxtj >= n)
                        {
                            continue;
                        }
                        // 将有效的相邻格标记为 1
                        if(isInfected[nxti][nxtj] == 0)
                        {
                            isInfected[nxti][nxtj] = 1;
                        }
                    }
                }
            }
        }
        // 标记完成，时间戳 + 1 即可
        ++timestp;

        if(cntOne == 0)
        {
            break;
        }
    }
    // 最后，timestp 的值就是我们安装的防火墙数量
    return res;
}

/*
[[0,0,0,0,0,0,0,0,0,0],
 [0,0,0,0,0,0,0,1,0,0],
 [1,0,0,0,0,0,0,0,0,0],
 [0,0,1,0,0,0,1,0,0,0],
 [0,0,0,0,0,0,1,0,0,0],
 [0,0,0,0,0,0,0,0,0,0],
 [0,0,0,0,0,0,0,0,0,0],
 [0,0,0,0,0,0,0,0,1,0],
 [0,0,0,0,1,0,1,0,0,0],
 [0,0,0,0,0,0,0,0,0,0]]
*/

/*
[[1,0,0,1,0,1,1,0,0,0],
 [1,1,0,0,1,0,0,0,1,0],
 [0,1,1,0,1,0,0,0,1,0],
 [1,0,0,1,1,1,1,0,0,0],
 [0,0,1,1,1,0,0,0,1,0],
 [1,0,1,1,0,0,0,1,1,0],
 [1,0,0,0,1,0,1,1,1,0],
 [1,0,0,0,0,0,1,0,0,0],
 [0,0,0,1,0,0,0,0,0,0],
 [1,0,0,0,0,0,1,0,0,0]]
*/

/*
[[0,0,1,1,1,0,1,0,0,0],
 [1,1,1,0,0,0,1,1,0,1],
 [0,0,0,0,0,0,1,0,0,0],
 [0,0,0,0,1,0,1,0,0,0],
 [1,0,0,0,1,1,1,0,0,0],
 [0,0,0,1,0,1,1,0,0,0],
 [1,0,0,0,0,1,0,0,0,1],
 [1,0,0,0,0,0,0,0,0,1],
 [0,1,0,0,0,0,0,0,1,0],
 [1,1,0,0,0,1,0,1,0,0]]
*/