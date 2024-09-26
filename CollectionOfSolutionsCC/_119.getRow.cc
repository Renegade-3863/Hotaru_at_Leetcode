#include "Solution.h"

vector<int> Leetcode101_200::Solution::getRow(int rowIndex)
{
    // 本题如果不要求 O(rowIndex) 的时间复杂度，其实非常简单，按上一题的流程加上一点滚动数组优化就是一个很不错的 O(rowIndex^2) 的解法
    // 不过本题要求只用 rowIndex 行内的数据进行计算，这显然就是要考我们数学知识了
    // 回忆一下杨辉三角的数学意义：组合数在集合图形(三角形)上的表现形式
    // 行n(从0开始计数)的下标为 m 的数的值为 C(n, m)，即从 n 个不同元素中取 m 个元素的组合数
    // 从左到右有这样的递推关系
    // C(n, m) = C(n, m-1) x (n-m+1)/m
    // 我们直接利用这个公式进行推导即可
    vector<int> res(rowIndex+1, 0);
    res[0] = 1;
    for(int i = 1; i <= rowIndex; ++i)
    {
        long long tmp = ((long long)res[i-1])*(rowIndex-i+1)/i;
        res[i] = tmp;
    }
    return res;
}