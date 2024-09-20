#include "Solution.h"

vector<vector<int>> Leetcode1_100::Solution::permuteUnique(vector<int>& nums)
{
    // 依然是要找出一组数的所有排列可能，不过这里这组数可能会出现重复元素
    // 可以简单地通过回溯树理清回溯状态之间的关系
    // 通过回溯树，不难发现，只要我们在同一层上选取了之前选过的数字，就一定会出现重复答案
    // 因而我们需要剪枝这种情况，即，同层剪枝
    // 这同样可以通过维护一个全局哈希集合来实现(或者单纯地使用一个数组)
    // 这里使用一个简单数组来实现，因为哈希集合的 insert 和 erase 需要额外的函数调用，对效率有影响
    bool added[nums.size()];
    // 注意，使用传统数组形式初始化的 bool 数组必须手动进行初始化，不然初值会被随机赋值，可能会导致问题
    memset(added, 0, sizeof(added));
    function<void(vector<vector<int>>&, vector<int>&)> backtrack = [&](vector<vector<int>>& res, vector<int>& cur)
    {
        if(cur.size() == nums.size())
        {
            res.push_back(cur);
            return;
        }
        for(int i = 0; i < nums.size(); ++i)
        {
            // 如果当前枝中添加过下标为 i 的元素，那么不能重复添加，不然会检出不正确的解
            // 而如果当前层中之前已经尝试过了同样值的元素，那么不能再尝试第二次，不然会检出重复解
            if(added[i] || (i > 0 && nums[i-1] == nums[i] && !added[i-1]))
            {
                continue;
            }
            // 否则，这个值可以添加，进行回溯即可
            added[i] = true;
            cur.push_back(nums[i]);
            backtrack(res, cur);
            cur.pop_back();
            added[i] = false;
        }
    };
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    vector<int> cur;
    backtrack(res, cur);
    return res;
}yy