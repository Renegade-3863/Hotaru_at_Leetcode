#include "Solution.h"
void Leetcode1_100::Solution::rotate(vector<vector<int>>& matrix)
{
    // 本题给定一个矩阵，要求我们把这个矩阵顺时针旋转90度
    // 这道题对于不会的人，就是一道比较复杂的模拟题，对于会的人，其实就是一种很特殊的几何转换题
    // 要实现90度的旋转，其实类比到几何中，就是先沿 y = x 做一次轴对称，再沿 y = 0 做一次上下翻转
    // 代码实现只涉及到数学关系，没有任何数据结构和高级算法
    // 先沿 y = x 翻转
    int m = matrix.size();
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < m-i; ++j)
        {
            swap(matrix[i][j], matrix[m-1-j][m-1-i]);
        }
    }
    // 再沿 y = 0 翻转
    for(int i = 0; i < m/2; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            swap(matrix[i][j], matrix[m-1-i][j]);
        }
    }
    return;
}