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

int Leetcode301_400::Solution::depthSum(vector<NestedInteger>& nestedList)
{
    // 一般涉及到这种嵌套问题的，不用想太多，基本都是可以用递归来解决的
    // 我们考虑下面的递归定义式：
    // dfs(nestedInteger, level) 代表这个嵌套数在 level 层的加权和
    // 那么考虑如何对这个问题进行求解
    // 我们肯定是需要进一步深入检查这个 nestedInteger
    // 两种情况：
    // 1. 这个东西本身就是一个数
    // 使用提供的 API，即 nestedInteger.isInteger = true
    // 那么我们直接返回这个值乘 level 即可，这是根据题目的定义来的
    // 2. 这个东西本身是一个列表
    // 那么我们需要进一步便利这个列表本身，并递归调用这个 dfs 函数去求解每一个内嵌元素的结果
    // dfs(nestedInteger, level) = sum of dfs(eachNestedInteger, level+1)
    // 简单的递归模式确定了时候，我们只需要写代码即可
    function<int(const NestedInteger&, int)> dfs = [&](const NestedInteger& nestedInteger, int level) -> int
    {
        if(nestedInteger.isInteger())
        {
            return nestedInteger.getInteger()*level;
        }
        // 获取列表本身用于递归遍历
        const vector<NestedInteger> list = nestedInteger.getList();
        int res = 0;
        for(const auto& elem : list)
        {
            res += dfs(elem, level+1);
        }
        return res;
    };
    // 对列表中每个元素调用 dfs，返回最后的和值即可
    int ans = 0;
    for(const auto& nestedInteger : nestedList)
    {
        ans += dfs(nestedInteger, 1);
    }
    return ans;
}