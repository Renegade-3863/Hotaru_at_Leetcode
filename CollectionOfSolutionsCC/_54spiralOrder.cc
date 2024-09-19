#include "Solution.h"

vector<int> Leetcode1_100::Solution::spiralOrder(vector<vector<int>>& matrix)
{
    // 一道常规的模拟类题目，只是需要注意的细节性问题比较多
    // 考虑这样的事实：我们遍历矩阵，一定是一次检查完一条边
    // 在我们检查完这条边之后，这个方向上我们需要检查的长度就减少了1
    // 比如我们遍历完矩阵的第一行
    // 此时我们后续向上探查时的上界就要增加1，从0变成1(因为第一行整体我们都已经遍历过了)，其它行/列也与此类似
    // 明确了这一点，其实变量设置和遍历流程都变得清晰了起来
    int m = matrix[0].size(), n = matrix.size();
    // 设定四个变量，分别标志四个边界值 (向右的右界，向下的下界，向左的左界，向上的上界)
    int r = m-1, l = 0, u = 0, d = n-1;
    vector<int> res;
    // 随着遍历流程逐步更新上面的四个边界
    // 需要设定遍历循环的退出条件？
    // 考虑什么情况下整个矩阵就已经被遍历完成了：
    // 我们可以得出一个充要条件：r < l || d < u
    // 也就是说，只要两对边界中有任意一对反序了，说明这对边界所夹的区间已经没有任何元素了，那么不论另一对还有没有剩余的中间值，都无法再继续找出可行元素了
    while(1)
    {
        // 按四个方向进行遍历即可
        for(int i = l; i <= r; ++i)
        {
            res.push_back(matrix[u][i]);
        }
        // 遍历完最上行后，要更新对应的 u 值
        if(++u > d)
        {
            return res;
        }
        // 再向下遍历
        for(int i = u; i <= d; ++i)
        {
            res.push_back(matrix[i][r]);
        }
        // 遍历完右列后，要更新对应的 r 值
        if(l > --r)
        {
            return res;
        }
        // 再向左遍历
        for(int i = r; i >= l; --i)
        {
            res.push_back(matrix[d][i]);
        }
        // 遍历完下行后，需要更新对应的 d 值
        if(u > --d)
        {
            return res;
        }
        // 最后向上遍历
        for(int i = d; i >= u; --i)
        {
            res.push_back(matrix[i][l]);
        }
        // 遍历完左列后，需要更新对应的 l 值
        if(++l > r)
        {
            return res;
        }
    }
    // 退出后，返回结果即可，理论上这一行不会执行到
    return res;
}