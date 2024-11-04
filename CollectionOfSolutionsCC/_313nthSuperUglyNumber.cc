#include "Solution.h"

int Leetcode301_400::Solution::nthSuperUglyNumber(int n, vector<int>& primes)
{
    // 本质上是一般的丑数问题的推广
    // 我们依然可以通过类似递推的方式，一步一步地递推出第 n 个超级丑数
    // 指定 primes.size() 个指针，每个指向最后一个还没有被对应的质数乘过的超级丑数的下标
    // 每一轮检查只需要找出这组下标上的超级丑数乘上对应的结果可以得到的最小值即可
    // 上面这个找最小值的过程，如果单纯的遍历检查，需要最大 O(primes.size()) 的额外时间复杂度
    // 我们考虑引入一个有序集合加速这个查找过程
    vector<long long> res;
    // 第一个超级丑数固定为 1
    res.push_back(1);
    // 记录当前已找到的超级丑数个数
    int count = 1;
    // 使用一个小优先队列，保存所有 primes.size() 个指针
    // 注意，这里使用 pair 数对而不是使用单纯的 int 的原因在于我们的 cmp 仿函数
    // 看一下 cmp 的 () 操作符定义就明白为什么了
    struct cmp 
    {
        // pair.first 存储的是对应的乘积，pair.second 存储的是对应的 res 数组下标
        bool operator() (const pair<long long, long long>& a, const pair<long, long>& b)
        {
            // 因为是小优先队列，所以对于存储容器，我们需要把大的元素放到堆底(也就是数组的最前面)
            return a.first > b.first;
        }
    };
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, cmp> minQ; 
    // 先初始化最初的 primes.size() 个元素到小优先队列中
    int m = primes.size();
    // 初始化 m 个指针
    vector<int> ptrs(m, 0);
    for(long long i = 0; i < m; ++i)
    {
        long long nxt = res[ptrs[i]]*primes[i];
        minQ.push(make_pair<long long&, long long&>(nxt, i));
    }
    // 梅开二度，需要判断我们提取出来的这个下一个最小值是不是已经添加过的重复值，而由于 res 本身有序的特性，我们只需要检查上一个添加的元素即可
    while(count < n)
    {
        if(res[count-1] != minQ.top().first)
        {
            res.push_back(minQ.top().first);
            ++count;
        }
        // 提取出需要移动到指针值
        long long ptr = minQ.top().second;
        minQ.pop();
        // 后移这个指针，并添加下一个该序列上的最小丑数
        long long nxt = res[++ptrs[ptr]]*primes[ptr];
        minQ.push(make_pair<long long&, long long&>(nxt, ptr));
    }
    return (int)res[n-1];
}