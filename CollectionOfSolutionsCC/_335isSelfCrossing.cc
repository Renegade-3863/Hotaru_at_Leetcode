#include "Solution.h"

bool Leetcode301_400::Solution::isSelfCrossing(vector<int>& distance)
{
    // 完全的数学题，没有任何数据结构/算法含金量，个人认为这题不想做就不做了，解法也说明了这就是一道 "内卷" 题。。。
    int n = distance.size();
    if(n < 4) 
    {
        return false;
    }

    int i = 2;
    while(i < n && distance[i] > distance[i-2])
    {
        ++i;
    }
    if(i == n)
    {
        return false;
    }

    if(distance[i] >= distance[i-2] - (i < 4 ? 0 : distance[i-4]))
    {
        distance[i-1] -= i < 3 ? 0 : distance[i-3];
    }
    for(++i; i < n && distance[i] < distance[i-2]; ++i);
    return i != n;
}