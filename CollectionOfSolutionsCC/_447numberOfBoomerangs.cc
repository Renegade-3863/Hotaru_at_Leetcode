#include "Solution.h"

int Leetcode401_500::Solution::numberOfBoomerangs(vector<vector<int>>& points)
{
    // 又是一个看了答案感觉自己是个傻子的题目
    // 采用三叶大佬的解法，本题抽丝剥茧后，无非就是要求这样一件事：
    // 按点之间距离进行配对，给出的这些点能配出多少个不同的三元组？
    // 先固定一个起始点，也就是回旋镖的拐点
    // 之后我们可以联想到要先把所有点对之间的距离预处理出来
    // 并存储到一个哈希表中，以备后续调用
    // 预处理完成后，我们可以检查这个以 (距离, 计数) 对为核心的哈希表
    // 对每种距离的数对个数进行组合计算即可
    int n = points.size();
    int res = 0;
    for(int i = 0; i < n; ++i)
    {
        unordered_map<int, int> mapping;
        for(int j = 0; j < n; ++j)
        {
            int x = points[i][0]-points[j][0], y = points[i][1]-points[j][1];
            int dist = x*x+y*y;
            ++mapping[dist];
        }
        for(const auto& pair : mapping)
        {
            res += pair.second*(pair.second-1);
        }
    }
    return res;
}