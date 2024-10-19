#include "Solution.h"

vector<int> Leetcode201_300::Solution::maxSlidingWindow(vector<int>& nums, int k)
{
    // 对于本题，我们可以简单地使用一个有序集合保存每一个长度为 k 的窗口中的所有值，每次把这个有序数组中的最大值放到答案数组中的对应位置上
    // 如果不允许你使用 STL 提供的优先队列这个现成的数据结构，那么就需要考虑现场自己写一个优先队列/大顶堆了。。。难度直接翻倍
    // 初始化一个最大优先队列，用于存储我们长度为 k 的窗口中的元素
    struct cmp {
        bool operator() (const pair<int, int>& a, const pair<int, int>& b) 
        {
            return a.first < b.first;
        }
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
    int n = nums.size();
    vector<int> res;
    // 先填充第一个长度为 k 的窗口
    for(int i = 0; i < k && i < n; ++i)
    {
        pq.push({nums[i], i});
    }
    res.push_back(pq.top().first);
    // 滚动检查后序窗口
    for(int i = k; i < n; ++i)
    {
        // 如果这个最大值下标已经不在窗口中了，我们需要把它弹出窗口
        while(!pq.empty() && pq.top().second <= i-k)
        {
            pq.pop();
        }
        // 把新值添加到这个大优先队列中
        pq.push({nums[i], i});
        res.push_back(pq.top().first);
    }
    return res;
}

// 上面这一版的代码不难看出是 O(nlogn) 的时间复杂度，因为这个优先队列，每加入一个新元素，我们都需要 O(logn) 的时间对其进行维护
// 根据题解，学习了使用单调队列的方案，感觉评论区有一句话总结的很到位：
// 一个队伍，年龄从队头到队尾逐渐减小，每当队伍中年龄最大的哪一个(队头的)年龄超出阈值(窗口长度 k)了，那么我们就要把他踢出队伍，而新加入进来的人，如果他比年长的前辈更有实力，那么我们就同样把这些年龄尚可的前辈也踢出队伍
// 太现实了。。。
vector<int> Leetcode201_300::Solution::maxSlidingWindow(vector<int>& nums, int k)
{
    // 基于上面的讨论模型，这里的队列必须使用双端队列来实现，单端队列不可行
    deque<int> q;
    int n = nums.size();
    // 结果数组
    vector<int> res;
    for(int i = 0; i < k && i < n; ++i)
    {
        // 如果队伍里的前辈不如这个新人，那么这个队伍里最强的人也显然不可能是他了，我们把这个人踢出去即可
        // 这里补充一点说明：为什么一定不会是这个前辈
        // 因为我们评估的总区间长度总是不变的，长度为 k
        // 因而这个前辈一定是会比这个新人更早老去，而直到新人老去之前，他都会因为能力比前辈更强而留在队伍中，等到新人也因为年老而被踢出队伍时，这个前辈早就因为年龄过大而被踢出了
        // 所以我们索性不用管这个前辈了
        while(!q.empty() && nums[q.back()] < nums[i])
        {
            q.pop_back();
        }
        // 把这个新人放到对应的位置上
        q.push_back(i);
    }
    // 记录第一个窗口中的最强者
    res.push_back(nums[q.front()]);
    // 滚动窗口
    for(int i = k; i < n; ++i)
    {
        // 依然是先根据这个新人尝试踢出前辈
        while(!q.empty() && nums[q.back()] < nums[i])
        {
            q.pop_back();
        }
        // 把新人添加进来
        q.push_back(i);
        // 别忘了踢出去年龄过大的
        while(q.front() <= i-k)
        {
            q.pop_front();
        }
        // 添加元素
        res.push_back(nums[q.front()]);
    }
    return res;
}