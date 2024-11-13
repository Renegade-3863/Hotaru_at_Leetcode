#include "Solution.h"

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
int Leetcode301_400::Solution::depthSumInverse(vector<NestedInteger>& nestedList)
{
    // 经典的 DFS 问题，没有什么技巧，定义了子问题暴力遍历就行了
    // 和第一道系列题的区别在于，本题的 "权重" 不再是深度本身，而是 "最大深度-深度+1"
    // 不过这个 "最大深度" 值我们一开始是不知道的
    // 所以需要额外定义一个方法来求解这张图的 "最大深度" 值
    // 并且在求出这个 "最大深度" 值之前，我们不能进行任何实际的计算
    // 我们依然是定义一个函数，用于返回一个 NestedInteger 类型的加权和
    // 定义一个全局的最大深度值
    int maxDepth = 1;
    // 为了更快地找出这个最大深度值，我们可以考虑换用 BFS
    queue<NestedInteger> q;
    // 我们需要往队列中先填入每一个嵌套类型
    for(const auto& nestedInteger : nestedList)
    {
        q.push(nestedInteger);
    }
    // 之后进行 BFS 深入，直到队列为空，我们就用最少的步数走到了最深的格子
    int steps = 0;
    while(!q.empty())
    {
        // 深入一步
        ++steps;
        int n = q.size();
        for(int i = 0; i < n; ++i)
        {
            const NestedInteger& nested = q.front();
            // 如果是一个数字，我们就不用在这一层上继续深入了，不再添加到队列中
            if(!nested.isInteger())
            {
                // 否则，我们就应该进一步深入，添加这个嵌套结构中的元素到队列中
                const vector<NestedInteger>& tmp = nested.getList();
                for(const auto& nxt : tmp)
                {
                    q.push(nxt);
                }
            }
            // 弹出 nested 即可
            q.pop();
        }
    }
    maxDepth = steps;
    cout << maxDepth << endl;
    function<int(const NestedInteger&, int)> dfs = [&](const NestedInteger& nestedInteger, int depth)
    {
        // 对这个数据结构保存的列表进行遍历即可
        // 分情况讨论：
        // 如果是一个单独的值，我们直接就能计算并返回结果了
        if(nestedInteger.isInteger())
        {
            return (maxDepth - depth + 1)*nestedInteger.getInteger();
        }
        // 存储最终的结果的变量
        int res = 0;
        // 否则，是一个列表，我们需要遍历这个列表，累计内部所有 NestedInteger 类型元素的权重和
        const vector<NestedInteger>& tmp = nestedInteger.getList();
        for(const auto& nested : tmp)
        {
            res += dfs(nested, depth+1);
        }
        return res;
    };
    int ans = 0;
    // 我们需要做的是对给定的数组循环调用 dfs 函数
    for(const NestedInteger& elem : nestedList)
    {
        ans += dfs(elem, 1);
    }
    return ans;
}