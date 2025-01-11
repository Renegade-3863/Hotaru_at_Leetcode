#include "Solution.h"

// 仿函数，定义 "项目" 结构的比较方法，"项目" 结构的实际定义为数值对
struct cmp
{
    // 数值对内部值为：[成本，利润]
    bool operator() (const pair<int, int>& a, const pair<int, int>& b)
    {
        // 对利润，按升序排列，到优先队列 (用堆实现)，堆顶的元素就是净利润最大的那个
        return a.second < b.second;
    }
};

int Leetcode501_600::Soltuion::findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital)
{
    // 认真读一遍题，会发现这道题的本质很好发现，就是贪心
    // 比较基本的想法是：
    // 我们应当优先选择那些 "当前能够实现，并且获利最多" 的项目优先执行
    // 这样就不难联想到使用优先队列的方案
    // 我们以这样的方式定义一个优先队列：
    // 队列内存储一组执行成本由低到高的项目，换句话说，队列内 "成本低优先"
    // 同时，队列内应该还需要保存每个项目对应的利润
    // 但是这样还不是最优的，我们细化一下优先规则：
    // 对于所有 "当前成本可行" 的新项目，在队列内按照 "净利润 (纯利润-成本)" 高优先进行排序
    // 实现上有一些细节需要考虑
    // 我们简单设计一下：
    // 1. 首先对所有项目按 "成本" 排序
    // 2. 之后，按照成本顺序把这些项目添加到 "净利润" 优先队列中
    // 我们只在排序后到成本数组头部的元素 "成本" 不低于 "当前资本" 的情况下进行入队操作
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
    // 对所有项目进行重构，生成一个 [成本，净利润] 的数值对数组
    int n = profits.size();
    deque<pair<int, int>> board(n, pair<int, int>());
    for(int i = 0; i < n; ++i)
    {
        // 遍历每一对 [成本，纯利润] 对，计算净利润，和成本一起放到 board 数组对应位置上
        board[i].first = capital[i];
        board[i].second = profits[i];
    }
    // 对 board 按照 "成本维" 进行升序排列
    sort(board.begin(), board.end(), [&](const pair<int, int>& a, const pair<int, int>& b) {
        return a.first < b.first;
    });
    // 记录 "当前资本" 变量，动态维护这个值
    // cnt 记录的是 "当前已经执行的项目数"
    int curC = w, cnt = 0;
    // 不断提取项目进行执行，直到执行的总项目数达到上限 (k 或者 n)
    while(cnt < n && cnt < k)
    {
        // 每轮提取前，根据 curC 把 board 中头部的所有满足成本要求的项目添加到 pq 中等待执行
        while(!board.empty() && board[0].first <= curC)
        {
            pq.push(board[0]);
            board.pop_front();
        }
        // 添加完成，我们取 pq 顶部，即当前所有可执行的项目中 "净利润" 最高的一个来执行
        // 当前最优情况下，也没有可以执行的项目，我们只能提前退出了
        if(pq.empty())
        {
            break;
        }
        curC += pq.top().second;
        // 弹出这个项目，代表执行完成
        pq.pop();
        // 记录 "执行了一个项目"
        ++cnt;
    }
    return curC;
}