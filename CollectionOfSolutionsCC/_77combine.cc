#include "Solution.h"

vector<vector<int>> Leetcode1_100::Solution::combine(int n, int k)
{
    // 题目描述很简单，要求找出范围 [1, n] 中所有可能的 k 个数的组合
    // 这种找出所有可能结果的题目十有八九都是回溯的典型题
    // 一般回溯类问题的困难点都在如何剪枝上
    // 本题要找的是组合，那么如果画出递归树，我们会发现这样一个比较明显的事实：
    // 我们不应该在同一枝中的某一结点处重复选用比同枝中上层结点值小的那些值
    // 组合必须数的类型不同才算不同，因而不同顺序的排列并不能算是不同组合
    // 所以这里我们通过这样剪枝的方式，就相当于限定了同一个组合结果(枝条)中，所有选择了的元素必须是按递增顺序
    // 这样所有相同元素选择的不同排列就都只剩下按递增顺序这一种了，自然就消除了重复
    function<void(vector<vector<int>>&, vector<int>&, int)> backtrack = [&](vector<vector<int>>& res, vector<int>& cur, int idx)
    {
        // 填好一组 k 个数之后，就可以记录并返回了
        if(cur.size() == k)
        {
            res.push_back(cur);
            return;
        }
        // 回溯树的模拟很简单，就是一个循环(模拟层)套一个递归调用(模拟枝)
        // 鉴于本题数值的特殊性，我们无需对数组进行预排序，记录一个当前第一个可以添加的元素值即可进行剪枝
        for(int i = idx; i <= n; ++i)
        {
            cur.push_back(i);
            backtrack(res, cur, i+1);
            cur.pop_back();
        }
    };
    vector<vector<int>> res;
    vector<int> cur;
    backtrack(res, cur, 1);
    return res;
}