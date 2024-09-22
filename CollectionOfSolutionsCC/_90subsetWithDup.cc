#include "Solution.h"

vector<vector<int>> subsetsWithDup(vector<int>& nums)
{
    // 给定一个包含重复元素的集合，要求找出这个数组所有可能的子集(原数组中的元素可以重复出现，但是不能拿出重复的集合)
    // 依然可以使用回溯树来解决回溯问题
    // 本题剪枝的方案也是比较复杂的
    // 总和回溯树考虑，我们会发现，同一层中，不能重复往一个位置上添加重复的元素，这是去重的一个条件
    // 同样，由于我们要找的是组合，不是排列，所以同样元素的顺序我们需要限制为只能从左到右排列到结果中
    // 所以，同一枝中也不能选择上面选过的数的下标之前(包括上面选过的数的下标本身)的任何元素，这样的限制就可以避免重排重复
    // 我们可以先把 nums 数组排序，这样可以更容易实现上面两种去重策略
    sort(nums.begin(), nums.end());
    int n = nums.size();
    vector<bool> visited(n, false);
    function<void(vector<vector<int>>&, vector<int>&, int)> backtrack = [&](vector<vector<int>>& res, vector<int>& cur, int idx)
    {
        res.push_back(cur);
        // 回溯结束条件
        // idx == n
        if(idx == n)
        {
            return;
        }
        // 遍历之前先把这个结果记录进全局数组
        // 依然是熟悉的循环层，回调枝
        for(int i = idx; i < n; ++i)
        {
            // 同一层内重复元素要剪枝
            // 单纯这样进行判断会有问题：同一枝内相邻的重复元素还是可以进行添加的，需要做区分
            if(i > idx && nums[i-1] == nums[i] && !visited[i-1])
            {
                continue;
            }
            cur.push_back(nums[i]);
            visited[i] = true;
            backtrack(res, cur, i+1);
            visited[i] = false;
            cur.pop_back();
        }
    };
    vector<vector<int>> res;
    vector<int> cur;
    backtrack(res, cur, 0);
    return res;
}