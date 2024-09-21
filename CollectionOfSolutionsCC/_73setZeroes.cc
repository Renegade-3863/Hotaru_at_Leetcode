#include "Solution.h"

void Leetcode1_100::Solution::setZeroes(vector<vector<int>>& matrix)
{
    // 对一个 mxn 的矩阵进行修改，如果某个位置 **原来** 是一个0，那么之后需要把它所在的行和列上所有的1都修改成0
    // 注意到这就需要我们记录原图中那些0的位置
    // 可以使用两个数组分别记录对应的行和列是否已经被置过零，同时用一个坐标数组记录所有原图上为零的位置坐标，之后遍历的时候用这个数组进行遍历即可
    // 坐标数组，记录原图上所有内容为零的坐标
    vector<pair<int, int>> cords;
    // 先过一遍整个矩阵，填充 cords 数组
    int m = matrix.size(), n = matrix[0].size();
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(matrix[i][j] == 0)
            {
                // 这个用法之前有提过，具体在第 37 题
                // 涉及到 C++ 模版和万能引用的知识
                cords.push_back(make_pair<int&, int&>(i, j));
                // 也可以直接写 cords.emplace_back(i, j);
            }
        }
    }
    // 使用两个单独数组分别标记对应的行和列是否已经被置过零
    vector<bool> rows(m, false);
    vector<bool> cols(n, false);
    int len = cords.size();
    for(int i = 0; i < len; ++i)
    {
        // 取出坐标
        auto [x, y] = cords[i];
        // 只有当对应行没有被置过零的时候，才执行置零操作
        if(!rows[x])
        {
            for(int _y = 0; _y < n; ++_y)
            {
                matrix[x][_y] = 0;
            }
            // 标记这一行为 "已置零"
            rows[x] = true;
        }
        // 只有当对应列没有被置过零的时候，才执行置零操作
        if(!cols[y])
        {
            for(int _x = 0; _x < m; ++_x)
            {
                matrix[_x][y] = 0;
            }
            // 标记这一列为 "已置零"
            cols[y] = true;
        }
    }
    // 无需任何返回值
    return;
}