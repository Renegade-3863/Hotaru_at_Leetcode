#include "Solution.h"

bool Leetcode301_400::Solution::canMeasureWater(int x, int y, int target)
{
    // 依然是很简单的 DFS 问题
    // 定义子问题：
    // dfs(i, j, subTarget) 代表第一个水壶中有 x 升水，第二个水壶中有 y 升水的情况下，能否构造出 subTarget 这个结果水量
    // 为了避免回头导致的死循环，我们记忆一个已经访问过的结点数组
    vector<vector<bool>> visited(x+1, vector<bool>(y+1, false));
    function<bool(int, int, int)> dfs = [&](int i, int j, int subTarget) -> int
    {
        visited[i][j] = true;
        // 结束条件是：subTarget == 0
        // 此时说明我们不用再添加任何水了，直接返回 true 即可
        if(subTarget == 0)
        {
            return true;
        }
        // 否则，剩余的目标值还不是0，我们需要进一步探讨下一步怎么做
        // 下一步按照题目给出的要求进行
        // 1. 把第一个水壶装满，注意，已经满了的情况下我们不能继续深入，不然会死循环
        if(i < x && !visited[x][j] && dfs(x, j, subTarget-(x-i)))
        {
            return true;
        }
        // 2. 把第二个水壶装满，注意，已经满了的情况下我们不能继续深入，不然会死循环
        if(j < y && !visited[i][j] && dfs(i, y, subTarget-(y-j)))
        {
            return true;
        }
        // 3. 清空第一个水壶
        if(i > 0 && !visited[0][j] && dfs(0, j, subTarget+i))
        {
            return true;
        }
        // 4. 清空第二个水壶
        if(j > 0  && !visited[i][0] && dfs(i, 0, subTarget+j))
        {
            return true;
        }
        // 5. 如果第一个水壶中还有水，把水从第一个水壶中倒入第二个水壶中
        // 注意：对于情况5、6，我们还需要注意不能陷入：第一个倒入第二个，第二个又倒入第一个这样的死循环中，我们需要记忆所有已经检查过的情况，不能重复检查
        int nxti = y-j >= i ? 0 : i-(y-j);
        int nxtj = y-j >= i ? i+j : y;
        if(i > 0 && !visited[nxti][nxtj] && dfs(nxti, nxtj, subTarget))
        {
            // 我们尽力把第一个水壶中的水转移到第二个水壶中，直到第二个水壶被装满/第一个水壶被清空
            return true;
        }
        nxti = x-i >= j ? i+j : x;
        nxtj = x-i >= j ? 0 : j-(x-i);
        // 6. 如果第二个水壶中还有水，把水从第二个水壶中倒入第一个水壶中
        if(j > 0 && !visited[nxti][nxtj] && dfs(nxti, nxtj, subTarget))
        {
            return true;
        }
        // 四种下一步都试过了，没有成功，那么我们就只能返回 false 了
        return false;
    };
    // 调用函数即可
    return dfs(0, 0, target);
}