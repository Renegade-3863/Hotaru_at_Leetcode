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

NestedInteger Leetcode301_400::Solution::deserialize(string s)
{
    // 很常规的递归题，我们先尝试最简单的递归写法
    // 定义 dfs 递归函数：
    // NestedInteger dfs(int i) 代表把 s[i] 位置开始，同一层的嵌套整数类型的解析结果
    // 那么很明显，这个函数的递归结束条件就是 s[i] == ']'
    // 因为一个 ']' 标识着同一层的结束
    // 其实说实话这道题有点类似含括号的计算器的那道题，做完这题可以回去回顾一下那道题
    // 注意一个细节问题，本题限定条件下，有可能出现整个 s 就是一个唯一的数的情况
    // 此时我们直接返回这个数本身即可
    // 这种单独的情况判定可以通过检查最后一个字符来实现
    NestedInteger res = NestedInteger();
    if(isdigit(s.back()))
    {
        int val = 0;
        for(int i = 0; i < s.size(); ++i)
        {
            val = val * 10 + (s[i]-'0');
        }
        res.setInteger(val);
        return res;
    }
    int i = 0;
    // 其它情况，是一个列表形式的嵌套整数，我们正常进行求解
    // 首先，考虑较为简单的情况：列表只有一层，没有更深的层次
    // 毕竟有更深的层次无非就是多套一个递归函数的问题
    // 定义这个子问题为 dfs(idx)
    // 只有一层的情况下，我们只需要检查从 idx+1 开始(默认 idx 处为左中括号)
    // 直到遇到 ']' 结束，返回结果即可
    function<NestedInteger(int&)> dfs = [&](int& idx) -> NestedInteger
    {
        NestedInteger res = NestedInteger();
        // 因为现在我们假设整个结构只有一层，所以我们只需要一个整型数存储每一个值
        int val = 0;
        // 此时我们默认 s[idx] 是一个左中括号，所以先右移一位 idx
        ++idx;
        // 退出循环的条件为 s[idx] == ']'，因为右中括号意味着当前这个一层的结构已经被我们处理完毕了
        while(1)
        {
            // 我们填数的契机是：遇到逗号就填，或者遇到右中括号也填
            if(s[idx] == ']')
            {
                // 填数
                res.add(NestedInteger(val));
                ++idx;
                break;
            }
            if(s[idx] == ',')
            {
                res.add(NestedInteger(val));
                val = 0;
                ++idx;
            }
            // 如果遇到了一个新的数，那么就要合并到 val 中
            if(isdigit(s[idx]))
            {
                val = val * 10 + (s[idx]-'0');
                ++idx;
            }
        }
        return res;
    };
    return dfs(i);
}

// 上面的代码适用于单层的嵌套整数，我们现在考虑引入多层的情况
NestedInteger Leetcode301_400::Solution::deserialize(string s)
{
    // 很常规的递归题，我们先尝试最简单的递归写法
    // 定义 dfs 递归函数：
    // NestedInteger dfs(int i) 代表把 s[i] 位置开始，同一层的嵌套整数类型的解析结果
    // 那么很明显，这个函数的递归结束条件就是 s[i] == ']'
    // 因为一个 ']' 标识着同一层的结束
    // 其实说实话这道题有点类似含括号的计算器的那道题，做完这题可以回去回顾一下那道题
    // 注意一个细节问题，本题限定条件下，有可能出现整个 s 就是一个唯一的数的情况
    // 此时我们直接返回这个数本身即可
    // 这种单独的情况判定可以通过检查最后一个字符来实现
    NestedInteger res = NestedInteger();
    if(isdigit(s.back()))
    {
        int val = 0;
        int i = s[0] == '-' ? 1 : 0;
        int sign = s[0] == '-' ? -1 : 1;
        for(; i < s.size(); ++i)
        {
            val = val * 10 + sign * (s[i]-'0');
        }
        res.setInteger(val);
        return res;
    }
    int i = 0;
    // 其它情况，是一个列表形式的嵌套整数，我们正常进行求解
    // 考虑有更深层次的情况
    // 无非就是多套一个递归函数的问题
    // 定义这个子问题为 dfs(idx)
    // 有多层的情况下，我们可能会途中遇到新的左中括号
    // 那么此时我们需要做的事 res.add(dfs(idx))，无他
    // 直到遇到 ']' 结束，返回结果即可
    function<NestedInteger(int&)> dfs = [&](int& idx) -> NestedInteger
    {
        NestedInteger res = NestedInteger();
        // 因为现在我们假设整个结构只有一层，所以我们只需要一个整型数存储每一个值
        int val = 0;
        // 用于在遇到右中括号的时候判断是否有需要添加的数值
        bool hasVal = false;
        // 记录 val 的符号
        int sign = 1;
        // 此时我们默认 s[idx] 是一个左中括号，所以先右移一位 idx
        ++idx;
        // 退出循环的条件为 s[idx] == ']'，因为右中括号意味着当前这个一层的结构已经被我们处理完毕了
        while(1)
        {
            // 我们填数的契机是：遇到逗号就填，或者遇到右中括号也填
            if(s[idx] == ']')
            {
                // 填数
                if(hasVal)
                {
                    res.add(NestedInteger(val));
                    hasVal = false;
                }
                ++idx;
                break;
            }
            if(s[idx] == ',')
            {
                // 注意，逗号前面也可能是一个右中括号，那么前面的这个子列表我们就已经添加过了，不能再进行添加
                if(s[idx-1] != ']')
                {
                    res.add(NestedInteger(val));
                }
                val = 0;
                hasVal = false;
                sign = 1;
                ++idx;
            }
            // 如果遇到了一个新的数，那么就要合并到 val 中
            if(isdigit(s[idx]))
            {
                hasVal = true;
                val = val * 10 + sign * (s[idx]-'0');
                ++idx;
            }
            if(s[idx] == '[')
            {
                res.add(dfs(idx));
            }
            // 注意，还有一种情况：符号
            // 不过这没什么难的，我们只需要记录一下当前数的符号，添加前乘上去就好了
            if(s[idx] == '-')
            {
                sign = -1;
                ++idx;
            }
        }
        return res;
    };
    return dfs(i);
}