#include "Solution.h"

bool Leetcode201_300::Solution::searchMatrix(vector<vector<int>>& matrix, int target)
{
    // 可以把整个矩阵从右上到左下视作一棵类似二叉搜索树的结构
    // 我们从最右上的格子开始入手搜索即可
    // 假设当前格子坐标为 (i, j)
    // 如果 matrix[i][j] > target，那么很显然 matrix[i][j] 这个位置下方一整列的元素都不可能是 target 了
    // 我们可以直接对 j 减1
    // 如果 matrix[i][j] < target，那么很显然 matrix[i][j] 这个位置左侧一整行的元素都不可能是 target 了
    // 我们可以直接对 i 加1
    // 如果 matrix[i][j] == target，那么直接返回 true 即可
    // 写代码！
    int m = matrix.size(), n = matrix[0].size();
    int upRighty = n-1, upRightx = 0;
    while(upRighty >= 0 && upRightx < m)
    {
        if(matrix[upRightx][upRighty] > target)
        {
            // 往左走一列
            --upRighty;
        }
        else if(matrix[upRightx][upRighty] < target)
        {
            // 往下走一行
            ++upRightx;
        }
        // 找到结果了，返回 true
        else
        {
            return true;
        }
    }
    // 没找到，返回 false
    return false;
}