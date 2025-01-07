#include "Solution.h"

vector<int> Leetcode401_500::Soltuion::findRightInterval(vector<vector<int>>& intervals)
{
    // 题目没有限制区间之间的原来顺序必须被考虑，所以我们可以对原数组进行排序
    // 对于每一个区间，我们都需要找出 "起点最小、同时不早于当前区间结束点" 的那一个区间作为结果
    // 所以不难想到对区间数组按区间起点进行排序这个办法
    // 排序规则：按照起点，起点小的在前面，这样我们才好找结尾点
    // 题目限定了所有的起点都不相同，所以我们不用考虑 a[0] == b[0] 的情况
    // 补充哈希表，用于记录区间起点和原下标的映射关系
    int n = intervals.size();
    unordered_map<int, int> mapping;
    for(int i = 0; i < n; ++i)
    {
        mapping[intervals[i][0]] = i;
    }
    // 这一步用了 O(nlogn) 的时间复杂度
    sort(intervals.begin(), intervals.end(), [&](const vector<int>& a, const vector<int>& b) -> bool {
        return a[0] < b[0];
    });
    vector<int> ans(n, -1);
    // 之后就是遍历+二分了，同样是 O(nlogn) 的复杂度
    for(int i = 0; i < n; ++i)
    {
        // 对于每个 i，二分右侧的区间进行 "右区间" 查找
        // 初始可能出现 "右区间" 的下标范围是：[i, n-1] (包括 i 本身，因为 j 可以等于 i)
        int left = i, right = n-1; 
        // 初始时，默认本区间的 "右区间" 不存在，结果为 -1
        int res = -1;
        while(left <= right)
        {
            // 取区间中间的那一个进行判断
            int mid = ((right-left)>>1)+left;
            // 两种情况
            // 1. mid 区间的起点早于 intervals[i][1] (endi)，那么这个区间和前半段区间都可以丢掉了
            if(intervals[mid][0] < intervals[i][1])
            {
                left = mid+1;
            }
            // 2. mid 区间的起点不早于 intervals[i][1] (endi)，那么这个区间可以成为候选的 "右区间"，同时右侧所有其它区间都可以丢掉了
            else
            {
                res = mid;
                right = mid-1;
            }
        }
        // 循环退出，res 如果不是 -1，那么它就代表了当前区间 intervali 的 "右区间" 下标，记录到答案中即可
        // 这里记录答案的时候发现了一个小问题，我们前面对数组进行了重排序，所以这里没法定位到原区间了，我们需要一种类似哈希映射的机制帮助我们重构答案
        // 题目限定了每个区间的起点都不相同，我们可以利用这一点进行哈希
        if(res != -1)
        {
            // 注意这里存的都必须是原来的下标
            ans[mapping[intervals[i][0]]] = mapping[intervals[res][0]];
        }
    }
    // 结束，返回结果
    return ans;
}