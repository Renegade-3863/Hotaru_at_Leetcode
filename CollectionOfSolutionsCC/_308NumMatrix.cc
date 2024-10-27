#include "Solution.h"

Leetcode301_400::Solution::NumMatrix2::NumMatrix2(vector<vector<int>>& matrix)
{
    // 初始化这棵线段树
    int m = matrix.size(), n = matrix[0].size();
    this->root = new SegNode(0, m*n);
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            this->root->update(i*n+j, i*n+j, matrix[i][j]);
        }
    }
    this->cols = n;
}

void Leetcode301_400::Solution::NumMatrix2::update(int row, int col, int val)
{
    // 这里也是一样，直接调用线段树自带的更新函数即可
    this->root->update(row*this->cols+col, row*this->cols+col, val);
}

int Leetcode301_400::Solution::NumMatrix2::sumRegion(int row1, int col1, int row2, int col2)
{
    int res = 0;
    // 按要查的子矩阵，一行一行地遍历，累加对应行的元素和
    for(int i = row1; i <= row2; ++i)
    {
        res += this->root->query(i*this->cols+col1, i*this->cols+col2);
    }
    return res;
}