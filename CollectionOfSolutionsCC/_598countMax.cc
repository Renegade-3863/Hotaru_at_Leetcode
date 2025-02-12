#include "Solution.h"

int Leetcode501_600::Soltuion::maxCount(int m, int n, vector<vector<int>>& ops)
{
    // 脑筋急转弯题目，本题我们只需要考虑所有 op 中最小的行和最小的列即可
    int res = 0, row = m, col = n;
    for(const auto& op : ops)
    {
        row = min(row, op[0]);
        col = min(col, op[1]);
    }
    return row*col;
}