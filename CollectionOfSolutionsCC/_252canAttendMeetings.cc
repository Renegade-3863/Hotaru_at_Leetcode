#include "Solution.h"

bool Leetcode201_300::Solution::canAttendMeetings(vector<vector<int>>& intervals)
{
    // 比较简单的题目，我们只需要判断区间集合里面的各个区间是否存在交集即可，只要存在交集，一个人就不可能参加所有会议
    // 不过判断交集肯定不能是毫无章法地暴力一对一比较，那种 O(n^2) 的时间复杂度并不优秀
    // 我们可以对原 intervals 数组进行排序
    // 通过排序来限定其中一个维度的某种次序，来方便我们的比较
    // 假定这里我们对会议的开始时间进行升序排列
    // 排序完成后，我们只需要判断任意两个相邻的区间 a 和 b
    // 是否存在 a.end >= b.begin 的情况，如果出现了，那么很明显我们不可能同时完整参加会议 a 和会议 b
    sort(intervals.begin(), intervals.end(), [&](const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    });
    int n = intervals.size();
    for(int i = 1; i < n; ++i)
    {
        // 可能有人会疑惑这里的比较策略：为什么我们只需要和前一个区间进行比较？
        // 后文进行一下贪心策略的解释
        if(intervals[i][0] < intervals[i-1][1])
        {
            return false;
        }
    }
    return true;
}

// 关于贪心比较策略的解释：
// 我们可以换一个角度思考这个比较策略的含义：
// 我们判断的确实是：当前这个区间是否和它前面的所有区间都没有交集
// 考虑这样的事实：对于当前的区间 intervals[i]
// intervals[i-1][0] <= intervals[i][1] 是一个必然结果(由我们的排序可知)
// intervals[i-1][1] > interval[i][0] 也是一个两个区间有交集的充要条件
// 我们要明确的是：为什么这个比较能同时判断出 intervals[i] 和前面所有区间是否有交集？
// 1. 如果二者有交集，那么前面的区间自然不用判断了，可以直接返回 false
// 2. 如果二者没有交集，那么由于我们能循环过来，那么说明前面这个区间 (intervals[i-1]) 也一定是一个可以完整参加的区间
// 说到这，我们会发现，又回到了这样一个循环不变式：
// 对于遍历下标 i，其左侧的连续区间是目前已知的从第一场会议开始能连续完整参加的所有会议
// 有了这个循环不变式，我们不难推断出下面的事实：
// 如果当前区间 intervals[i] 和 intervals[i-1] 都没有交集，那么因为 intervals[i-1] 一定比 intervals[i] 相对看起来更靠左(起码开始时间偏左)
// 那么由于 intervals[i-1] 都和它左边的所有区间没有交集，很显然的一点就是，intervals[i] 也不可能和 intervals[i-1] 左边的任何区间存在交集
// 至此，我们就明确了一次比较决定一列关系的原因