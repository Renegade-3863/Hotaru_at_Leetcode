#include "Solution.h"

vector<vector<int>> Leetcode1_100::Solution::combinationSum(vector<int>& candidates, int target)
{
    // 使用给定的整数数组，找出其和为目标值 target 的所有子数组
    // 经典回溯类问题
    // 记录一个子数组的当前数字和作为状态变量在递归状态之间传递
    /*
        res 是全局的答案数组，用于存储所有可行的子数组
        rec 记录了当前子数组中的数字
        target 是最终目标和
        cur 是当前添加到子数组中的数字的和
    */
    function<void(vector<vector<int>>&, vector<int>&, int, int)> backtrack = [&](vector<vector<int>>& res, vector<int>& rec, int cur, int idx)
    {
        // 如果找到的子数组的和已经大于了 target，说明这个选择不合法，也没必要继续添加(递归)了，直接回溯即可
        if(cur > target)
        {
            return;
        }
        // 如果找到了一个和为 target 的子数组，直接记录并回溯即可
        else if(cur == target)
        {
            res.push_back(rec);
            return;
        }
        // 否则，cur 还是小于 target 的，我们可以进一步选数填入，并递归
        // 题干说明了，candidates 中不存在重复元素，并且所有元素都可以无限制重复选取，我们按这个思路进行选数即可
        // 不过需要注意很重要的一个问题，就是可能会选出来相同组合的不同排列
        // 思考一下如何去重
        // 尝试画一下树形的回溯图，我们不难看出来，其实出现重复，就是因为这棵树中的某些枝上出现了之前出现过的序列的一种不同排列
        // 从根本上讲，就是类似 (1, 2) 和 (2, 1) 这种类型的重排，
        // 那么，为了避免这种反序的结果，我们要做的就是把我们可能选择的结果限制到一种顺序，比如非递减顺序
        // 要实现这种方式，我们可以通过把 candidates 数组按升序排列，之后按 "以下标 i 位置的数开头的子序列" 的方式进行遍历
        // 当然，本题限制了 candidates 数组中所有元素均不重复，并且可以随意选取
        // 如果数组中的元素会有重复，并且选取的次数有限制，那又应该如何去重，这是就第40题了
        for(int i = idx; i < candidates.size(); ++i)
        {
            rec.push_back(candidates[i]);
            backtrack(res, rec, cur+candidates[i], i);
            rec.pop_back();
        }
    };
    vector<vector<int>> res;
    vector<int> rec;
    sort(candidates.begin(), candidates.end());
    backtrack(res, rec, 0, 0);
    return res;
}