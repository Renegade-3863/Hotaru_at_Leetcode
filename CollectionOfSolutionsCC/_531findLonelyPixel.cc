#include "Solution.h"

int Leetcode501_600::Soltuion::findLonelyPixel(vector<vector<char>>& picture)
{
    // 简单的模拟题，按题目要求来就行
    // 基本来说，我们可以通过一个哈希表来记录哪些行存在黑色像素，哪些行不存在黑色像素
    // 以及哪些列存在黑色像素，哪些列不存在黑色像素
    // row 哈希表记录所有 "存在黑色像素" 的行
    unordered_map<int, int> row; 
    // col 哈希表记录所有 "存在黑色像素" 的列
    unordered_map<int, int> col;
    // 我们先遍历一遍整张图，填写 row 表和 col 表
    int m = picture.size(), n = picture[0].size();
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(picture[i][j] == 'B')
            {
                // 记录到对应的哈希表中
                ++row[i];
                ++col[j];
            }
        }
    }
    // 第二轮遍历，就是找出最后的孤独像素个数了
    int res = 0;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(picture[i][j] == 'B' && row[i] == 1 && col[j] == 1)
            {
                ++res;
            }
        }
    }
    return res;
}

// 根据官方题解的提示进行了第二轮遍历的 O(1) 时间优化
int findLonelyPixel(vector<vector<char>>& picture)
{
    // 简单的模拟题，按题目要求来就行
    // 基本来说，我们可以通过一个哈希表来记录哪些行存在黑色像素，哪些行不存在黑色像素
    // 以及哪些列存在黑色像素，哪些列不存在黑色像素
    // row 哈希表记录所有 "存在黑色像素" 的行
    unordered_map<int, int> row; 
    // col 哈希表记录所有 "存在黑色像素" 的列
    unordered_map<int, int> col;
    // 我们先遍历一遍整张图，填写 row 表和 col 表
    int m = picture.size(), n = picture[0].size();
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(picture[i][j] == 'B')
            {
                // 记录到对应的哈希表中
                ++row[i];
                ++col[j];
            }
        }
    }
    int res = 0;
    for(int i = 0; i < m; ++i)
    {
        if(row[i] == 1)
        {
            for(int j = 0; j < n; ++j)
            {
                if(picture[i][j] == 'B' && col[j] == 1)
                {
                    ++res;
                }
            }
        }
    }
    return res;
}