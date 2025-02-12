#include "Solution.h"

vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click)
{
    // BFS/DFS 模拟题，我们先读题
    // 我们使用 DFS 的方式来解决这道题，注意记录 "已经被揭开" 的那些格子
    // 不过根据题目本身的属性，我们用 board 本身进行记录即可
    // 本质上是需要定义一个 "揭开" 函数，命名为 reveal
    // 这个函数接受一个坐标参数 (x, y)，代表接管 "揭开坐标 (x, y) 处的元素以及之后的效果的事件"
    // 记录八个方向，方便遍历
    const int dirs[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    int m = board.size(), n = board[0].size();
    // "游戏进行中标志"，初始值为 true，代表 "游戏可继续"
    bool valid = true;
    // 定义一个检查下标是否合法的 helper 函数
    function<bool(int, int)> check = [&](int x, int y) -> bool
    {
        return x >= 0 && x < m && y >= 0 && y < n;
    };
    // 定义两个分离的函数，下面的 reveal 代表初次点击的效果，上面这个 dfs 代表的是后续深入的效果
    // 因为二者对于地雷格 'M' 的处理逻辑不同，所以我们分开写  
    function<void(int, int)> dfs = [&](int x, int y) -> void
    {
        // dfs 函数并不会在遇到地雷的时候修改 valid 变量，它只会在遇到地雷时返回，不再深入递归
        if(board[x][y] == 'M' || board[x][y] == 'B' || isdigit(board[x][y]))
        {
            // 遇到了地雷，或者一个没必要再检查后续的格子，不再深入，返回即可
            return;
        }
        // 其它情况下，board[x][y] 是一个 'E' 空格
        else if(board[x][y] == 'E')
        {
            // 我们把它标记为 'B'，并继续深入检查其它八个方向的合法相邻格
            int cnt = 0;
            for(int i = 0; i < 8; ++i)
            {
                int nxtx = x+dirs[i][0], nxty = y+dirs[i][1];
                if(check(nxtx, nxty) && board[nxtx][nxty] == 'M')
                {
                    ++cnt;
                }
            }
            if(cnt == 0)
            {
                board[x][y] = 'B';
                // 继续深入其它八个方向
                for(int i = 0; i < 8; ++i)
                {
                    int nxtx = x+dirs[i][0], nxty = y+dirs[i][1];
                    if(check(nxtx, nxty))
                    {
                        dfs(nxtx, nxty);
                    }
                }
                return;
            }
            // 在当前格记录 cnt，返回即可
            board[x][y] = '0'+cnt;
        }
        return;
    };
    function<void(int, int)> reveal = [&](int x, int y) -> void
    {
        // 情况 1. 当前是一个地雷位
        if(board[x][y] == 'M')
        {
            board[x][y] = 'X';
            // 游戏结束，我们修改 "游戏进行中标志"，并返回即可
            valid = false;
            return;
        }
        // 情况 2. 和 3. 我们需要先对当前格子周围八个格子进行检查
        else if(board[x][y] == 'E')
        {
            // 记录当前空格四周的地雷数量
            int cnt = 0;
            for(int i = 0; i < 8; ++i)
            {
                int nxtx = x+dirs[i][0], nxty = y+dirs[i][1];
                if(check(nxtx, nxty) && board[nxtx][nxty] == 'M')
                {
                    // 如果 board[nxtx][nxty] 是地雷，对 cnt 加 1
                    ++cnt;
                }
            }
            // 结束检查，检视 cnt 的值
            if(cnt == 0)
            {
                // 没有地雷，那么我们调用 dfs 对四周八个格子进行递归检查
                board[x][y] = 'B';
                for(int i = 0; i < 8; ++i)
                {
                    int nxtx = x+dirs[i][0], nxty = y+dirs[i][1];
                    if(check(nxtx, nxty))
                    {
                        dfs(nxtx, nxty);
                    }
                }
                // 结束递归，返回
                return;
            }
            // 否则，周围有地雷，我们把周围地雷数记录到当前格子中，不再深入递归
            board[x][y] = '0'+cnt;
            return;
        }
        // 其它情况，比如 'B'，或者一个数字字符，代表周围的地雷数，此时我们不需要做任何操作，因为之前把这个格子修改成 'B' 的操作就已经把它后续的格子探查完了，我们直接返回即可
        return;
    };
    reveal(click[0], click[1]);
    if(!valid)
    {
        // 游戏已经结束，返回 board 即可
        return board;
    }
    return board;
}