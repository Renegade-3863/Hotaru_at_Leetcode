#include "Solution.h"

int Leetcode301_400::Solution::minArea(vector<vector<char>>& image, int x, int y)
{
    // 本题只需要明确一点：
    // 我们只需要四个值
    // 黑色矩形区域的：
    // 上方最突出的那个点
    // 下方最突出的那个点
    // 左边最突出的那个点
    // 右边最突出的那个点
    // 题目还要求不能用 O(mn) 的暴力搜索方法
    // 所以我们只能考虑优化
    // 不难想到可以通过两轮二分搜索来得出上面四个值
    // 先按照垂直方向遍历+二分一轮，找出水平方向上黑色区域左右的最突出值
    // 再按照水平方向遍历+二分一轮，找出竖直方向上黑色区域上下的最突出值
    // 用四个数对变量分别存储所需的四个值
    int leftMost = y, rightMost = y, upMost = x, lowMost = x;
    // 先垂直遍历+二分一轮
    int m = image.size(), n = image[0].size();
    // 左边界可能出现的区间是 [0, y]
    int left = 0, right = y;
    while(left <= right)
    {
        int mid = ((right-left)>>1)+left;
        // 对这一列进行检查
        bool found = false;
        for(int i = 0; i < m; ++i)
        {
            // 找到了一个 '1'，代表这一列存在可以作为左边界的值，我们需要记录并进一步向左深入搜索
            if(image[i][mid] == '1')
            {
                // 先记录
                leftMost = min(leftMost, mid);
                // 修改右边界
                right = mid-1;
                found = true;
                break;
            }
        }
        if(!found)
        {
            // 没找到，我们需要修改左边界
            left = mid+1;
        }
    }
    left = y; right = n-1;
    while(left <= right)
    {
        int mid = ((right-left)>>1)+left;
        // 对这一列进行检查
        bool found = false;
        for(int i = 0; i < m; ++i)
        {
            // 找到了一个 '1'，代表着一列存在可以作为右边界的值，我们需要记录并进一步向右深入搜索
            if(image[i][mid] == '1')
            {
                // 先记录
                rightMost = max(rightMost, mid);
                left = mid+1;
                found = true;
                break;
            }
        }
        if(!found)
        {
            // 没找到，我们需要修改右边界
            right = mid-1;
        }
    }
    // 剩下上下边界的逻辑也是类似的
    int up = 0, down = x;
    while(up <= down)
    {
        int mid = ((down-up)>>1)+up;
        bool found = false;
        for(int j = 0; j < n; ++j)
        {
            if(image[mid][j] == '1')
            {
                upMost = min(upMost, mid);
                down = mid-1;
                found = true;
                break;
            }
        }
        if(!found)
        {
            up = mid+1;
        }
    }
    up = x; down = m-1;
    while(up <= down)
    {
        int mid = ((down-up)>>1)+up;
        bool found = false;
        for(int j = 0; j < n; ++j)
        {
            if(image[mid][j] == '1')
            {
                lowMost = max(lowMost, mid);
                up = mid+1;
                found = true;
                break;
            }
        }
        if(!found)
        {
            down = mid-1;
        }
    }
    // 找到了四个方向上的最值，直接计算结果即可
    return (rightMost-leftMost+1)*(lowMost-upMost+1);   
}