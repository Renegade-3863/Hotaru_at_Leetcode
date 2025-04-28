#include "Solution.h"

// 729 题的简单变种，我们依然可以用线段树来解决这道题
Leetcode701_800::Soltuion::MyCalendarTwo::MyCalendarTwo()
{
    // 构建的时候，要先新建内部的线段树根结点
    this->root = buildTree2();
}

bool Leetcode701_800::Soltuion::MyCalendarTwo::book(int startTime, int endTime)
{
    // 给定区间 [startTime, endTime]，我们需要先查询：
    // [startTime, endTime) 上的最大值
    // 题目给定最大区间为 [0, 1e9]，那么我们根结点假设代表的是 [0, 1e9+4]
    int maxi = query(this->root, 0, 1e9+4, startTime, endTime-1);
    if(maxi >= 2)
    {
        // 区间最大值不小于 2，说明当前区间上有至少一个时间被预定超过了 3 次，那么我们没法再次预定
        // 直接返回 false 即可
        return false;
    }  
    // 否则，我们可以预定，那么先对当前区间进行更新，注意，我们的 update 函数，处理的是 "对区间 [leftVal, rightVal] 这个区间的下标增加 v"
    update(this->root, 0, 1e9+4, startTime, endTime-1, 1);
    // 之后，返回 true 即可
    return true;
}