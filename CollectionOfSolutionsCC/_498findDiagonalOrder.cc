#include "Solution.h"

vector<int> Leetcode401_500::Soltuion::findDiagonalOrder(vector<vector<int>>& mat)
{
    // 模拟细节类问题
    // 我们需要一种合适的方法来便利代码的结构，coding 之前需要先想一下架构，这种模拟题急不得
    // 提取一下题目的要求，基本的顺序是，按副对角线，从左上到右下，对角线内从左下到右上，逐个元素进行遍历即可
    // 初始化一个 res 数组，存储最后的遍历结果
    int m = mat.size(), n = mat[0].size();
    // 答案数组的大小实际上已经确定了，和原矩阵的总大小是一样的，都是 m*n
    vector<int> res(m*n, 0);
    // 定义一个 flag，代表当前遍历的是奇数序号的副对角线还是偶数序号的副对角线
    // 第一个副对角线定义为奇数序号的副对角线
    bool flag = true;
    // 定义一对变量，代表当前要遍历的坐标
    // k 代表的是当前添加的元素的下标，当 k 到达 m*n 的时候，说明填数已经完成了
    int x = 0, y = 0, k = 0;
    while(k < m*n)
    {
        // 把 mat[x][y] 放到 res 中
        res[k++] = mat[x][y];
        if(flag)
        {
            if(x == 0)
            {
                if(y == n-1)
                {
                    ++x;
                }
                else
                {
                    ++y;
                }
                flag = false;
            }
            else if(y == n-1)
            {
                ++x;
                flag = false;
            }
            else
            {
                // 其它情况下，可以正常挪 x 和 y
                --x; ++y;
            }
        }
        else
        {
            if(y == 0)
            {
                if(x == m-1)
                {
                    ++y;
                }
                else
                {
                    ++x;
                }
                flag = true;
            }
            else if(x == m-1)
            {
                ++y;
                flag = true;
            }
            else
            {
                ++x; --y;
            }
        }
    }
    return res;
}