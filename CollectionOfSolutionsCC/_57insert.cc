#include "Solution.h"

vector<vector<int>> Leetcode1_100::Solution::insert(vector<vector<int>>& intervals, vector<int>& newInterval)
{
    // 简单思考就会觉得其实本质上就是一道模拟题，面试的时候遇到模拟题的话都是幸运的
    // 我们要做的事情很简单，按部就班地把这个新区间捏到数组里即可
    // 1. 检查第一个和 newInterval 有重叠的区间
    int n = intervals.size();
    vector<vector<int>> res;
    if(n == 0)
    {
        res.emplace_back(newInterval);
        return res;
    }
    bool added = false;
    for(int i = 0; i < n; ++i)
    {
        // 如果当前区间和 intervals 数组中的某个区间有重叠，就可以进入第二层循环
        if(intervals[i][1] >= newInterval[0] && intervals[i][0] <= newInterval[1])
        {
            // 注意，一旦进入了这个处理例程，我们就不会再返回外层循环了，处理结束后就直接返回结果
            // 循环继续合并和寻找所有后续的和 newInterval 有交集的集合，对它们进行合并
            // 设定合并后的区间的开始值和结束值(当前的值)
            int start = min(intervals[i][0], newInterval[0]), end = max(intervals[i][1], newInterval[1]);
            // 循环，不断地检查后续的区间，看它们能否进一步并入当前这个合并后的区间
            while(i < n)
            {
                if(i+1 < n && intervals[i+1][0] > end)
                {
                    ++i;
                    res.emplace_back(vector<int>{start, end});
                    // 当前位置的区间已经不能再并入前面的这个合并后的大区间了
                    // 此时可以直接把后面所有的原始区间都直接原封不动添加到 res 数组中并返回
                    for(; i < n; ++i)
                    {
                        res.emplace_back(intervals[i]);
                    }
                    return res;
                }
                // 否则，这个区间还是一个可以和之前的大区间合并的区间，进行合并操作即可
                else if(++i < n)
                {
                    end = max(intervals[i][1], end);
                    // start 不用更新，它一定是可以保持原值的
                }
            }
            // 如果内部的 if 判断没有结束循环，说明后面的所有区间都被合并了
            // 这里把这个合并后的大区间添加到 res 末尾即可
            res.emplace_back(vector<int>{start, end});
            // 根据前面的设计，这里需要直接退出最外层的 for 循环
            return res;
        }
        // 否则的话，说明当前遍历到的区间是和 newInterval 没有交集的，可以保持原样加入到答案数组中(注意：这部分区间是完全没有可能和后面新更新后的区间重叠的
        // 因为原有的所有区间都是互相不重叠的，而新加进来的区间也和它们没有重叠，所以即使新加进来的区间和后面的区间取并集，也一定无法接触到这些区间)
        // 经过第一版代码逻辑的分析，我们现在尝试把 newInterval 和 intervals 中的区间没有重叠着一情况在循环中就执行完成，而不是留到最后重新寻找插入位置
        // 因为我们现在在检查的这个区间在这里是和 newInterval 没有任何交集的，所以如果 newInterval 实际上没有和任何区间重叠，那么应该有如下几种情况
        // 1. newInterval[0] > intervals[i][1] && newInterval[1] < intervals[i+1][0]，newInterval 要插到 intervals[i] 的后面
        // 2. newInterval[1] < intervals[i][0] && newInterval[0] > intervals[i-1][0]，newInterval 要插到 intervals[i] 的前面
        // 我们只需要特殊处理一些边界问题即可
#if 1
        if(newInterval[1] < intervals[i][0] && (i == 0 || newInterval[0] > intervals[i-1][0]) && !added)
        {
            // 此时只需要把 newInterval 添加进来即可
            res.emplace_back(newInterval);
            added = true;
        }
#endif
        res.emplace_back(vector<int>{intervals[i][0], intervals[i][1]});
#if 1
        if(newInterval[0] > intervals[i][1] && (i == n-1 || newInterval[1] < intervals[i+1][0]) && !added)
        {
            res.emplace_back(newInterval);
            added = true;
        }
#endif
    }
#if 0
    // 如果这个循环正常退出了，说明前面 intervals 中所有的区间都和 newInterval 没有交集，我们只需要找出 newInterval 需要被插入的位置即可
    int idx = 0;
    while(idx < n)
    {
        // 只需要找到第一个起始位置在 newInterval 右边的区间就行了
        if(intervals[idx][0] >= newInterval[1])
        {
            break;
        }
        ++idx;
    }
    res.insert(res.begin()+idx, newInterval);
    // 返回结果
#endif
    return res;
}