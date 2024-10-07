#include "Solution.h"

int majorityElement(vector<int>& nums)
{
    // 本题是摩尔投票的典型问题，当然也可以用哈希表的方式来进行数值选取
    // 不过那样会有 O(n) 的空间复杂度
    // 这里我们使用空间复杂度为 O(1) 的摩尔投票方案
    // 我们规定一个当前已知的票数最多的"候选人"
    int candidate = nums[0];
    // 记录当前这个"候选人"拿到的有效票数
    int cnt = 1, n = nums.size();
    for(int i = 1; i < n; ++i)
    {
        if(cnt == 0)
        {
            candidate = nums[i];
            ++cnt;
        }
        else if(nums[i] == candidate)
        {
            ++cnt;
        }
        else
        {
            --cnt;
        }
    }
    return candidate;
}