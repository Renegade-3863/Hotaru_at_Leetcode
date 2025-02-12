#include "Solution.h"

int Leetcode501_600::Soltuion::leastBricks(vector<vector<int>>& wall)
{
    // 基本的哈希表问题
    // 题目要求的是找到一条穿过砖块最少的切线，那么反过来，我们要找的就是一条穿过缝隙最多的切线
    // 所以，我们可以用一个哈希表记录每一个坐标上边界缝隙的个数，最后，找出坐标上边界缝隙个数最多的那一个
    // 用墙的总高度减去这个值就可以了
    unordered_map<int, int> cnts;
    int maximum = 0;
    for(const auto& w : wall)
    {
        int preSum = 0, n = w.size();
        for(int i = 0; i < n-1; ++i)
        {
            preSum += w[i];
            if(++cnts[preSum] > maximum)
            {
                maximum = cnts[preSum];
            }
        }
    }
    // 检查完成，wall.size()-maximum 就是答案
    return wall.size()-maximum;
}