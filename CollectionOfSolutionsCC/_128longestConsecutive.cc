#include "Solution.h"

// 备注：为什么是一个 O(n) 的解法？
// 注意我们遍历的过程，应该了解到我们至多只会遍历每个元素三次，第一次是添加哈希表的过程
// 第二次要么是它本身是一个序列的开头，要么它是以另一个元素开头的序列中的一个元素，至于它是另一个元素开头的序列中的一个元素的情况，我们压根不会进行任何处理
// 而只有当这个元素本身不是一个序列的开头的时候，我们才会遍历这个元素三次，其它情况下都只会遍历两次，综合下来，最坏的时间复杂度依然是 O(n)
int Leetcode101_200::Solution::longestConsecutive(vector<int>& nums)
{
    // 要求我们找出一组未排序数组中最长的连续序列的长度
    // 乍一看有点懵，不知道从何下手
    // 我们依然考虑把问题化大为小的策略
    // 把问题分解为：
    // 找出以每个元素作为序列开始元素的情况下，最长连续序列的长度
    // 那么这样一来，问题就变得明晰了
    // 我们可以遍历整个数组，找出以它们开头的序列的最长长度
    // 一个哈希表记录每个元素是否在 nums 中出现过
    unordered_set<int> memo;
    int n = nums.size();
    // 全局的最大值
    int res = 0;
    for(int i = 0; i < n; ++i)
    {
        memo.insert(nums[i]);
    }
    // 之后再第二次遍历，使用上面记录的哈希表加快元素查找的效率
    for(int i = 0; i < n; ++i)
    {
        if(memo.find(nums[i]-1) == memo.end())
        {
            int curNum = nums[i]+1, curMax = 1;
            // 如果这个元素是一个序列的开头，那么我们就不断地递增元素值，直到找完数组中可以拿到的全部以当前元素开头的序列
            while(memo.find(curNum) != memo.end())
            {
                ++curNum; ++curMax;
            }
            // 找到了以 nums[i] 开头的序列的最大长度，更新全局的最优解
            res = max(res, curMax);
        }
        // 如果这个元素不是一个序列的开头，那么我们在整个遍历中一定会从这个序列的开头遍历到这里来，可以直接跳过
    }
    // 返回全局结果即可
    return res;
}