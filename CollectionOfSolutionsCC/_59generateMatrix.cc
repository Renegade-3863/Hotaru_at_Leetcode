#include "Solution.h"

vector<vector<int>> Leetcode1_100::Solution::generateMatrix(int n)
{
    // 本题要求我们自主构造一个螺旋型的矩阵，本质上和那道遍历螺旋矩阵的题目完全一致，只是遍历过程中做的事情从检出值变成了填入值而已
    // 这里不再赘述方法，直接给出代码
    // 四个标记，标记四条遍历边界
    int u = 0, d = n-1, l = 0, r = n-1;
    int idx = 1;
    // 最后返回的答案矩阵
    vector<vector<int>> res(n, vector<int>(n));
    while(u <= d && l <= r)
    {
        // 先向右填到最右
        for(int i = l; i <= r; ++i)
        {
            res[u][i] = idx++;
        }
        // 修改上界
        if(++u > d)
        {
            break;
        }
        // 再向下填到最下
        for(int i = u; i <= d; ++i)
        {
            res[i][r] = idx++;
        }
        // 修改右界
        if(--r < l)
        {
            break;
        }
        // 再向左填到最左
        for(int i = r; i >= l; --i)
        {
            res[d][i] = idx++;
        }
        // 修改下界
        if(--d < u)
        {
            break;
        }
        // 最后向上填到最上
        for(int i = d; i >= u; --i)
        {
            res[i][l] = idx++;
        }
        // 修改左界
        if(++l > r)
        {
            break;
        }
    }
    return res;
}