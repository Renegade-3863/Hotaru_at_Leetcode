#include "Solution.h"

vector<vector<int>> Leetcode601_700::Soltuion::imageSmoother(vector<vector<int>>& img)
{
    // 简单题，简单做
    // 直接模拟整个计算过程即可
    int m = img.size(), n = img[0].size();
    vector<vector<int>> res(m, vector<int>(n, 0));
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            // 计算 img[i][j] 的平滑值
            int sum = 0, div = 0;
            for(int p = i-1; p <= i+1; ++p)
            {
                for(int q = j-1; q <= j+1; ++q)
                {
                    if(p >= 0 && p < m && q >= 0 && q < n)
                    {
                        sum += img[p][q];
                        ++div;
                    }
                }
            }
            res[i][j] = sum/div;
        }
    }
    return res;
}