#include "Solution.h"

vector<vector<int>> Leetcode501_600::Soltuion::matrixReshape(vector<vector<int>>& mat, int r, int c)
{
    // 简单的模拟题
    // 我们先检查 mat.size() * mat[0].size() 是否等于 r*c
    // 如果不等于，那么我们就直接返回原数组即可，这个新的矩阵没法恰好放下原矩阵中的所有元素
    int m = mat.size(), n = mat[0].size();
    if(m*n != r*c)
    {
        return mat;
    }
    vector<vector<int>> res(r, vector<int>(c, 0));
    // (x, y) 代表 res 中下一个可填的空位位置
    int x = 0, y = 0;
    // 否则，恰好可以放下，我们模拟填数即可
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            // 尝试把 mat[i][j] 填入新矩阵的对应下一个空位中
            res[x][y] = mat[i][j];
            // 把 x 与 y 挪到下一个空位上
            if(y == c-1)
            {
                ++x;
                y = 0;
            }
            else
            {
                ++y;
            }
        }
    }
    return res;
}