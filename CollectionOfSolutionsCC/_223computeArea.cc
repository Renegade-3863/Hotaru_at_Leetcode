#include "Solution.h"

int Leetcode201_300::Solution::computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{
    // 这题不像是 CS 题目，更像是一道数学题
    // 分情况进行讨论即可
    // 我们需要先判断这两个矩形是否相交，如果不相交，那么我们甚至不用进行计算，直接返回结果即可
    // 为了计算相交部分的面积，我们可以简化一下问题：
    // 如果二者相交，那么很明显这两个矩形的八条边界线之间会有交集：
    // 具体的，a 矩形的两条横边：[ay1, ay2] 一定会和 b 矩形的两条横边 [by1, by2] 有重叠的部分
    // 重叠部分的合法长度应该为 max(min(ay2, by2)-max(ay1, by1), 0)
    // 同理，竖边的重叠合法长度为：max(min(ax2, bx2)-max(ax1, bx1), 0)
    // 最后，整个的覆盖面积就等于两个矩形的面积和，减去它们的重叠部分面积
    int overlapHeight = max(min(ay2, by2)-max(ay1, by1), 0), overlapWidth = max(min(ax2, bx2)-max(ax1, bx1), 0);
    return (ay2-ay1)*(ax2-ax1)+(by2-by1)*(bx2-bx1)-overlapHeight*overlapWidth;
}