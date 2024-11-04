#include "Solution.h"

vector<vector<int>> Leetcode301_400::Solution::multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2)
{
    // 很奇怪的一道题，如果只是给出整个矩阵的话，那么无论是否稀疏，我们的计算方法都只能是模拟矩阵乘法规则。。。
    int res = 0;
    int m = mat1.size(), n = mat1[0].size(), k = mat2[0].size();
    // 初始化结果矩阵
    vector<vector<int>> res(m, vector<int>(k, 0));
    // 遍历 mat1 的 m 行乘以 mat2 的 k 列
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < k; ++j)
        {
            for(int t = 0; t < n; ++t)
            {
                res[i][j] += mat1[i][t]*mat2[t][j];
            }
        }
    }
    return res;
}