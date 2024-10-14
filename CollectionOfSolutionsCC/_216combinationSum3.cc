#include "Solution.h"

vector<vector<int>> Leetcode201_300::Solution::combinationSum3(int k, int n)
{
    // 又是一道回溯类问题，说实话遇到这种类型的题目我们应该感到庆幸，因为只要会了一般的写法，这种题基本是可以一招鲜吃遍天的
    // 还是根据回溯树来写即可，同时注意去重(还是固定所有同样数字的排列只有升序这一种顺序即可)
    // 本题由于相当于可取值集合中不含有重复的元素，我们的去重变得简单了
    // 全局参数：
    vector<vector<int>> res;
    vector<int> path;
    // 参数：sum 代表的是当前已经选出的结果值和，cur 代表我们本次可以选的第一个数
    function<void(int, int)> backtrack = [&](int sum, int cur)
    {
        // 回溯结束条件：
        // 如果我们添加的元素正好到了 k 个，就检查这个 sum 是否等于了 n，如果等于了就添加，否则不添加
        if(path.size() == k)
        {
            if(sum == n)
            {
                res.push_back(path);
            }
            return;
        }
        // for 循环模拟回溯树的同一层
        for(int i = cur; i <= 9; ++i)
        {
            // 执行递归
            path.push_back(i);
            // 递归调用模拟沿树的某一枝深入一层
            backtrack(sum+i, i+1);
            path.pop_back();
        }
    };
    // 调用即可
    backtrack(0, 1);
    return res;
}