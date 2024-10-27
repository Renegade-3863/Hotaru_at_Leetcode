#include "Solution.h"

Leetcode301_400::Solution::NumMatrix(vector<vector<int>>& matrix)
{
    // 因为数组不可变，所以我们依然可以通过简单的二维前缀数组来加速计算
    int m = matrix.size(), n = matrix[0].size();
    if(m > 0 && n > 0)
    {
        this->preSum.resize(m,vector<int>(n, 0));
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                int upLeft = 0, left = 0, up = 0;
                if(i > 0 && j > 0)
                {
                    upLeft = preSum[i-1][j-1];
                }
                if(i > 0)
                {
                    up = preSum[i-1][j];
                }
                if(j > 0)
                {
                    left = preSum[i][j-1];
                }
                // 更新 preSum[i][j]
                preSum[i][j] = matrix[i][j]+left+up-upLeft;
            }
        }
    }
}   

int Leetcode301_400::Solution::sumRegion(int row1, int col1, int row2, int col2)
{
    // 获取左边，上面，左上方的三个前缀值
    int upLeft = 0, up = 0, left = 0;
    if(row1 > 0 && col1 > 0)
    {
        upLeft = this->preSum[row1-1][col1-1];
    }
    if(row1 > 0)
    {
        up = this->preSum[row1-1][col2];
    }
    if(col1 > 0)
    {
        left = this->preSum[row2][col1-1];
    }
    // 返回结果
    return this->preSum[row2][col2]-up-left+upLeft;
}