#include "Solution.h"

vector<vector<int>> subsets(vector<int>& nums)
{
    // 本题基本算是求固定长度组合的题目(上一题)的简单拓展，即要求找出长度为 [0, nums.size()] 的所有组合
    // 所以不多赘述，直接上代码
    function<void(vector<vector<int>>&, vector<int>&, int)> backtrack = [&](vector<vector<int>>& res, vector<int>& cur, int idx)
    {
        // 只要进入一次递归调用，就添加一个组合，无条件
        res.push_back(cur);
        for(int i = idx; i < nums.size(); ++i)
        {
            cur.push_back(nums[i]);
            backtrack(res, cur, i+1);
            cur.pop_back();
        }
    };
    vector<vector<int>> res;
    vector<int> cur;
    sort(nums.begin(), nums.end());
    backtrack(res, cur, 0);
    return res;
}