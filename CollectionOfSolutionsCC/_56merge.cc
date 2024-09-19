#include "Solution.h"

struct cmp
{
public:
    // 按升序排列，数值小的元素优先级高
    bool operator() (const vector<int>& a, const vector<int>& b)
    {
        return a[0] < b[0];
    }
};

vector<vector<int>> Leetcode1_100::Solution::merge(vector<vector<int>>& intervals)
{
    // 本题要求我们合并一些有重叠的区间，不进行排序的话，可能会有重叠区间寻找的额外时间开销
    // 所以这里先根据所有区间的开始值进行排序
    // 注意 STL 各种功能型函数的使用方法，这里我们需要传入一个仿函数类型
    sort(intervals.begin(), intervals.end(), cmp());
    // 排好序之后，我们需要做的就是简单遍历+合并了
    int n = intervals.size();
    // 标记一个当前被并入的区间的右边界值
    // idx 用于记录这个被并入区间在 res 中的下标
    int end = intervals[0][1], idx = 0;
    vector<vector<int>> res;
    res.push_back(vector<int>(2, 0));
    res[0][0] = intervals[0][0]; res[0][1] = intervals[0][1];
    for(int i = 1; i < n; ++i)
    {
        // 如果当前这个最后一个区间覆盖了后面一个子区间的开始值，我们就可以把这个子区间并入当前这个被并入区间
        if(end >= intervals[i][0])
        {
            // 这里要注意更新逻辑，不能只要找到了一个重叠区间就更新 res[idx][1]，还要判断这个重叠区间是否被包含在了当前这个最后一个区间中
            res[idx][1] = max(res[idx][1], intervals[i][1]);
        }
        // 否则，我们就找到了一个新的，不和前面任何区间有重叠的子区间，需要在 res 中新开一个被合并区间
        else
        {
            res.push_back(vector<int>(2, 0));
            res[++idx][0] = intervals[i][0];
            res[idx][1] = intervals[i][1];
        }
        // 别忘了更新 end 值
        end = res[idx][1];
    }
    return res;
}