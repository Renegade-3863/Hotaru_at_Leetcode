#include "Solution.h"

bool Leetcode601_700::Soltuion::judgeCircle(string moves)
{
    // 简单题，简单做
    // 我们只需要遍历整个操作数组
    // 检查最后 L 和 R 能否抵消，U 和 D 能否抵消即可
    int cntL = 0, cntR = 0, cntU = 0, cntD = 0;
    for(const auto& move : moves)
    {
        switch(move)
        {
            case 'L':
                ++cntL;
                break;
            case 'R':
                ++cntR;
                break;
            case 'U':
                ++cntU;
                break;
            case 'D':
                ++cntD;
                break;
        }
    }
    return cntL == cntR && cntU == cntD;
}