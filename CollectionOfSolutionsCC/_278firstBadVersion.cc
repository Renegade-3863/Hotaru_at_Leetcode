#include "Solution.h"

int Leetcode201_300::Solution::firstBadVersion(int n)
{
    // 很简单的二分题目
    // 我们要找的是第一个出错的版本号，所以我们可以规定一个 "第一个出错的版本号可能存在的区间"
    // 即 [left, right]
    // 之后通过对这个区间进行不断的二分，来找到最后的结果
    int left = 0, right = n;
    // 规定一个候选人值，记录当前已知的可能为第一个出错的版本号的值
    int res = n;
    while(left <= right)
    {
        int mid = ((right-left)>>1)+left;
        // 如果中点处的版本是有错误的，那么中间这个版本就有可能是 "第一个出错的版本号"，记录候选值，并更新区间
        if(isBadVersion(mid))
        {
            res = mid;
            right = mid-1;
        }
        // 否则，mid 和之前的所有版本号都不可能出错，同步更新区间
        else
        {
            left = mid+1;
        }
    }
    // 检查完成，返回结果即可
    return res;
}