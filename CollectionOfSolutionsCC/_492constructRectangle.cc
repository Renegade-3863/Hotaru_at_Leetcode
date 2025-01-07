#include "Solution.h"

vector<int> Leetcode401_500::Soltuion::constructRectangle(int area)
{
    // 简单题简单做，题目的要求是求出一个数值 (area) 的尽量相等的因数
    // 那么最接近的那个数，很明显就是 sqrt(area)
    // 那么只要 area 本身是个完全平方数，那么我们直接返回 sqrt(area) 这个整数即可
    // 否则，我们很明显应该以 sqrt(area) 两侧的任意一个最近整数开始枚举
    // 我们选择小于 sqrt(area) 的最大值作为起点，也就是枚举 W 值来完成本题
    int W = sqrt(area);
    while(W > 0)
    {
        if(area % W == 0)
        {
            return {area/W, W};
        }
        --W;
    }
    return {-1, -1};
}