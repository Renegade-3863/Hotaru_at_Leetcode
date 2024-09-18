#include "Solution.h"

vector<vector<int>> Leetcode1_100::Solution::permute(vector<int>& nums)
{
    // 额外添加一个哈希表用于判断当前元素是否在同一枝中出现过
    unordered_set<int> added;
    // 本题的目标是，求出给定不含重复元素的数组所有可能的排列顺序
    // 简单的回溯类问题
    // 可能会需要考虑去重，等到代码内部检查即可
    // 使用回溯树进行模拟
    /*
        res：全局的排列组合结果
        cur：当前枝上检出的中间结果
    */
    function<void(vector<vector<int>>&, vector<int>&)> backtrack = [&](vector<vector<int>>& res, vector<int>& cur)
    {
        // 退出情况
        // 如果 idx == nums.size();
        // 说明我们已经找到了一个合法的，可以加入到 res 答案中的数组，把 cur 加入到 res 中并返回即可
        if(cur.size() == nums.size())
        {
            res.emplace_back(cur);
            return;
        }
        // 否则，说明这个排列还没有填满，我们需要进一步检查下标 idx 处可以添加的元素
        for(int i = 0; i < nums.size(); ++i)
        {
            // 只有当前枝中没有添加过，我们才可以进行添加
            if(added.find(nums[i]) == added.end())
            {
                added.insert(nums[i]);
                cur.push_back(nums[i]);
                backtrack(res, cur);
                cur.pop_back();
                added.erase(nums[i]);
            }
        }
    };
    // 分析是否需要去重
    // 由于本题没有重复元素，因而不会出现某一位上选择了和之前一样的元素而导致最终选出相同的排列，故没必要去重
    vector<vector<int>> res;
    vector<int> cur;
    backtrack(res, cur);
    return res;
}