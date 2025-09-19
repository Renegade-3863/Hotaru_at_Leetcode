#include "Solution.h"

bool Leetcode701_800::Solution::isToeplitzMatrix(vector<vector<int>>& matrix)
{
    // 简单模拟题
    // 我们跑一遍检查流程就行了
    int m = matrix.size(), n = matrix[0].size();
    int x = 0, y = n-1;
    // 结束循环的条件为：x 已经执行到最后一行
    // 我们遍历的 (x, y) 为每一条对角线的左上端点
    while(x < m)
    {
        // 每一次循环，(x, y) 都指向一条新的对角线的左上端点
        // 那么此时我们就可以开始遍历了
        bool isSame = true;
        int first = matrix[x][y];
        int ox = x, oy = y;
        while(x < m)
        {
            // 往右下走一步
            ++x; ++y;
            // 如果走了一步后，出范围了，那么说明我们已经遍历完了这条对角线，调整 x 和 y 后跳出当前循环
            if(x >= m || y >= n)
            {
                // 如果原来的对角线顶点在左上角结点右侧，那么我们往左挪一格
                // 否则，往下挪一格
                x = oy == 0 ? ox+1 : ox;
                y = oy == 0 ? 0 : oy-1;
                // 跳出当前对角线
                break;
            }
            // 否则，我们可以正常继续检查
            if(matrix[x][y] != first)
            {
                // 发现不满足题意，直接返回 false 即可
                return false;
            }
        }
    }
    // 整体遍历完成，我们返回 true 即可
    return true;
}