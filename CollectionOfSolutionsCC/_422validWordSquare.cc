#include "Solution.h"

bool Leetcode401_500::Solution::validWordSquare(vector<string>& words)
{
    // 简单判断这个矩阵是否关于主对角线对称即可
    int n = words.size();
    for(int i = 0; i < n; ++i)
    {
        int m = words[i].size();
        for(int j = 0; j < m; ++j)
        {
            // 注意，本题的字符串数组可能本身并不是完美的矩阵，因而我们需要额外判断这些特殊情况
            if(j >= n || words[j].size() <= i || words[i][j] != words[j][i])
            {
                return false;
            }
        }
    }
    return true;
}