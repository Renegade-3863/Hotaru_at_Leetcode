#include "Solution.h"

// 第一版：正向深搜回溯，很容易 TLE
vector<vector<int>> Leetcode201_300::Solution::getFactors(int n)
{
    // 本题要求我们找出一个给定整数的所有因子，这又可以视作是一个回溯类问题
    // 不过既然是回溯类问题，那么就不可避免地需要面对去重的问题
    // 不过本题的去重问题也可以通过按序遍历因子数组来实现
    // 我们定义下面的回溯回调函数体：
    // backtrack(idx)，代表从 idx 开始选数的构造过程
    // path 用于记录当前因子组合中存储的所有因子
    if(n == 1)
    {
        return {};
    }
    vector<int> path;
    vector<vector<int>> res;
    int pathRes = 1;
    function<void(int)> backtrack = [&](int idx) 
    {
        // 回溯的结束条件：idx 达到1，即已经找齐了所有的因子
        if(pathRes == n)
        {
            res.push_back(path);
            return;
        }
        for(int i = idx; i < n; ++i)
        {
            if(pathRes*i <= n)
            {
                pathRes *= i;
                path.push_back(i);
                backtrack(i);
                path.pop_back();
                pathRes /= i;
            }
        }
    };
    backtrack(2);
    return res;
}

// 第二版：尝试换用反向 DFS，从结果开始往回深搜，可以通过，但是时间复杂度非常高
// 感觉同层的遍历部分还是可以剪枝，因为 axb 被检查过后，bxa 就不用检查了
vector<vector<int>> getFactors(int n)
{
    vector<vector<int>> res;
    vector<int> path;
    int pathRes = 1;
    // 虽然有点丑陋，不过特殊情况特判一下应该无可厚非
    if(n == 1)
    {
        return {};
    }
    function<void(int, int)> backtrack = [&](int idx, int remainder)
    {
        if(pathRes == n)
        {
            res.push_back(path);
            return;
        }
        // 对因子规划为反向有序
        for(int i = idx; i <= remainder; ++i)
        {
            if(i == n)
            {
                continue;
            }
            if(n%i == 0)
            {
                path.push_back(i);
                pathRes *= i;
                backtrack(i, remainder/i);
                pathRes /= i;
                path.pop_back();
            }
        }
    };
    backtrack(2, n);
    return res;
}

// 第三版：进一步优化同一层内的遍历次数
// 这里还是借用了一下答案的方法，感觉这种子问题的解法是真的很巧妙
vector<vector<int>> getFactors(int n)
{
    vector<vector<int>> res;
    vector<int> path;
    // 在看这个函数之前，我们考虑一下递归求解一个大整数的因子的过程
    // 举例：12 = 2*6 = 2*(2*3)
    //         = 3*4
    // 因而我们不难发现，整个求解过程就是在不断地拆分一个个的因子
    // 最开始，我们是在拆解 12 这个原本的因子
    // 之后，第一行后面，我们开始拆 6 这个新的可拆解因子
    // 整体的递归子问题可以这样看：
    // (不可拆解部分)*(可拆解部分)
    // 再进一步看一下 48:
    // 48 = 2*24 = 2*(2*12) = 2*(2*(2*6)) = 2*(2*(2*(2*3)))
    //           = 2*(3*8) = 2*(3*(4*2))
    //           = 2*(4*6)
    //    = 3*16 = ...
    // 不难发现，为了去重，我们需要
    // 1. 因子检查不小于前面找过的有序因子中最大的那一个    (这个确保的是枝之间的去重)
    // 2. 因子检查不超过当前子因子的平方根                (这个确保的是同层之间的去重)
    function<void(int, int)> backtrack = [&](int idx, int remainder)
    {
        // 对因子规划为反向有序
        // 只检查到当前剩余母因子的平方根为止，防止后续出现 (a, b), (b, a) 重复 (防止同一因子间的重复)
        // 同时检查开始点是记录的上一轮深入继承来的最后一个因子，不能选择更小的 (防止不同因子间的重复)
        for(int i = idx; i <= sqrt(remainder); ++i)
        {
            // 如果这个值是当前母因子的一个有效的因子
            if(remainder%i == 0)
            {
                path.push_back(i);
                path.push_back(remainder/i);
                res.push_back(path);
                // 这里需要先把母因子弹出路径数组，再把它替换成对应的两个小因子
                path.pop_back();
                backtrack(i, remainder/i);
                // 当前因子检查完成，进行回溯
                path.pop_back();
            }
        }
    };
    backtrack(2, n);
    return res;
}