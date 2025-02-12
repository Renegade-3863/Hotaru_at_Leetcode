#include "Solution.h"

// 第一版：暴力 DFS，不带记忆化，可以预见的 TLE
int Leetcode601_700::Soltuion::scheduleCourse(vector<vector<int>>& courses)
{
    // 这种排课程表，问最多可以上多少门课类型的题，暴力是 DP，取巧是贪心
    // 思维难度永远比代码难度大
    // 我们先思考：
    // 是否可以用类似 DFS (背包问题) 的方式来审视这道题？
    // 比如，我们用下面的定义来求解：
    // dfs(i, j) 代表：当前最晚允许修课到第 j 天，而我们从前 i 门课中选课进修的情况下
    // 最多可以修多少门课
    // 这个定义是否可以进行递推？
    // 注意，和一般的背包不同，本题背包的容量实际上是变的，j 这个值就是动态的背包容量
    // 考虑如何计算 dfs(i, j)
    // 我们对于当前最后这门课程 i (它的最晚结束时间就是 j)
    // 那么我们有两种选择：
    // 1. 上这门课，并且在能恰好修完的时候才开始上 (也就是说，上完课恰好到第 j 天，这样很明显是最优的)
    // 2. 不上这门课
    // 情况 1. 递推关系式就是：
    // 注意，情况 1 需要额外判断一下，第 i 门课这门课是否能修，也就是说，它的最晚允许结束时间 courses[i][1] 是否不大于 j
    // 如果 courses[i-1][1] < j，那么我们就只能考虑情况 2 了
    // dfs(i, j) = dfs(i-1, j-courses[i-1][0])
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 考虑一下边界情况
        // 如果 i == 1，那么我们只考虑第一门课，那么我们直接检查这门课是否能修即可
        // 不用考虑 j 的值，这个值可以在内部代码中进行判断
        if(i == 1)
        {
            // cout << i << ", " << j << ": " << (int)(courses[0][0] <= j) << endl;
            return courses[0][0] <= j;
        }
        // i > 0，那么我们可以考虑检查 courses[i-1][1]，如果 courses[i-1][1] >= j，那么我们可以选 courses[i-1][1]
        int res = 0;
        // 同时，别忘了检查这门课到底能不能修完，因为有的样例，甚至最晚修完的时限都比这门课修完所需的时间短。。
        if(courses[i-1][1] >= j && courses[i-1][1] >= courses[i-1][0] && courses[i-1][0] <= j)
        {
            res = max(res, 1+dfs(i-1, min(j-courses[i-1][0], courses[i-2][1])));
        }
        // 其它情况下，我们要么是不打算修这门课，要么是压根没法修这门课，取最大值即可
        res = max(res, dfs(i-1, min(j, courses[i-2][1])));
        // cout << i << ", " << j << ": " << res << endl;
        return res;
    };  
    // 按照上面的逻辑，我们可以先对 courses 进行排序，按照 "最晚结束时限" 进行升序排列即可
    sort(courses.begin(), courses.end(), [&](const vector<int>& a, const vector<int>& b) -> bool
    {
        return a[1] <= b[1];
    });
    // 之后，我们要求的结果，就是 dfs(courses.size(), courses[courses.size()-1][1])
    // for(int i = 0; i < courses.size(); ++i)
    // {
    //     cout << "[" << courses[i][0] << ", " << courses[i][1] << "]" << endl;
    // }
    return dfs(courses.size(), courses[courses.size()-1][1]);
}

// 第二版：给 DFS 加上记忆化数组
// 依然 TLE，看来是不得不用贪心了。。。
int scheduleCourse(vector<vector<int>>& courses)
{
    // 由于 j 的值可能会很大，所以这里我们不用二维数组来记录，而用一个嵌套哈希表来进行记录
    unordered_map<int, unordered_map<int, int>> memo;
    // 把上一版代码复制过来，再加上和 memo 有关的记忆化代码即可
    function<int(int, int)> dfs = [&](int i, int j) -> int
    {
        // 考虑一下边界情况
        // 如果 i == 1，那么我们只考虑第一门课，那么我们直接检查这门课是否能修即可
        // 不用考虑 j 的值，这个值可以在内部代码中进行判断
        if(i == 1)
        {
            // cout << i << ", " << j << ": " << (int)(courses[0][0] <= j) << endl;
            return courses[0][0] <= j;
        }
        if(memo[i].count(j))
        {
            return memo[i][j];
        }
        // i > 0，那么我们可以考虑检查 courses[i-1][1]，如果 courses[i-1][1] >= j，那么我们可以选 courses[i-1][1]
        int res = 0;
        // 同时，别忘了检查这门课到底能不能修完，因为有的样例，甚至最晚修完的时限都比这门课修完所需的时间短。。
        if(courses[i-1][1] >= j && courses[i-1][1] >= courses[i-1][0] && courses[i-1][0] <= j)
        {
            res = max(res, 1+dfs(i-1, min(j-courses[i-1][0], courses[i-2][1])));
        }
        // 其它情况下，我们要么是不打算修这门课，要么是压根没法修这门课，取最大值即可
        res = max(res, dfs(i-1, min(j, courses[i-2][1])));
        // cout << i << ", " << j << ": " << res << endl;
        memo[i][j] = res;
        return res;
    };  
    // 按照上面的逻辑，我们可以先对 courses 进行排序，按照 "最晚结束时限" 进行升序排列即可
    sort(courses.begin(), courses.end(), [&](const vector<int>& a, const vector<int>& b) -> bool
    {
        return a[1] <= b[1];
    });
    // 之后，我们要求的结果，就是 dfs(courses.size(), courses[courses.size()-1][1])
    // for(int i = 0; i < courses.size(); ++i)
    // {
    //     cout << "[" << courses[i][0] << ", " << courses[i][1] << "]" << endl;
    // }
    return dfs(courses.size(), courses[courses.size()-1][1]);
}

// 第三版：考虑改用贪心算法。。
int scheduleCourse(vector<vector<int>>& courses)
{   
    // 本质上来说，这道题是很贴近生活的一道题，那么我们也可以用更贴近生活的方式来进行思考
    // 从本质上来说，把整个数组按照 lastDayi 进行排序肯定是没问题的
    // 因为结束时间越早的课程，我们就越可能在前面考虑它
    // 我们思考这样的极端情况：
    // 如果每门课的结束时间都设定的很晚 (假设无限久的限制)，那么很明显我们可以上完所有课程
    // 但是肯定会有一些课程按当前方案，没法在限定的结束时间内上完
    // 那么我们就需要考虑它是否有选择的价值，如果一定要选，那么我们就需要把前面选出来的某一门课剔除出当前选择的方案，以此来减少已经累计起来的时间
    // 那么只要我们剔除掉一个前面已经选择了的，修习所需时间最长的一门课，很明显就是最优的 (理想情况是，这样就可以修当前这门课了，但如果这样剔除，也没法修当前这门课，那么很明显没必要放弃更多课)
    // 要实现前面描述的这种效果，我们就需要一个优先队列，存储所有已经选择了的课程，并按照它们的 "持续时间" 进行排序
    // 虽然正常 C++ 的 priority_queue 默认就是大顶堆，不过这里我们还是把定义写全，毕竟不是所有人都是 STL 大师
    priority_queue<int, vector<int>, less<int>> pq;
    // sum 代表当前已经累计了的方案所需要的累计修习时间总和
    int sum = 0;
    // 把所有课程按照结束时限进行排序
    sort(courses.begin(), courses.end(), [&](const vector<int>& a, const vector<int>& b) -> bool
    {
        return a[1] < b[1];
    });
    // 之后是遍历 courses 数组，模拟上面的贪心方法
    int n = courses.size();
    for(int i = 0; i < n; ++i)
    {
        // 尝试把当前课程添加到 sum 中，检查 sum 添加了当前课程的修习时间后，是否超过了这门课修完的最晚时限
        if(sum+courses[i][0] > courses[i][1])
        {
            // 那么我们检查 pq 顶部的那门课的修习时间是否长于 courses[i][0]
            // 如果是，那么我们弹出那门课，用当前这门课来代替即可
            if(!pq.empty() && pq.top() > courses[i][0])
            {
                sum -= pq.top();
                pq.pop();
                // 把这门课添加进去
                sum += courses[i][0];
                pq.push(courses[i][0]);
            }
            // 否则，这门课时间过长，我们就不能选它了
        }
        // 否则，当前这门课即使添加到当前方案里，也不会导致超时，那么我们加进去即可
        else
        {
            pq.push(courses[i][0]);
            sum += courses[i][0];
        }
    }
    // 遍历结束，pq 中保存的课程个数就是最终的答案
    return pq.size();
}