#include "Solution.h"

int Leetcode501_600::Soltuion::findPairs(vector<int>& nums, int k)
{
    // 套皮的 "两数之和" 问题，我们同样可以用哈希表来解决这道题
    // 题目要求的是 |nums[i] - nums[j]| == k
    // 那么也就是 -k == nums[i]-nums[j] || k == nums[i]-nums[j]
    // 我们记录所有 "已经检查过" 的元素值到一个哈希表中
    // 之后每遍历到一个元素，我们都检查前面是否记录过 nums[i]+k 或者 nums[i]-k 这两个值即可
    // 题目有一点说的不是很明确，注意：数对不能重复计算，也就是说，我们还需要一种机制来记忆是否发现过某种数值对
    // 这用一个数值哈希表就可以实现
    // 之所以用数值哈希表，是因为确定了一个数值对中较小的那一个值，那么我们就能推理出较大的那一个值了
    // 这样我们就不用再重载一个存储 "数值对" 结构对象的哈希表了，节省了代码工作量
    unordered_set<int> memo;
    // res 用于存储所有满足题意的数值对中 "较小的那一个值"
    unordered_set<int> res;
    // 我们不用考虑对应值的下标，所以直接用简化的遍历方式即可
    for(const auto& num : nums)
    {
        if(memo.count(num+k))
        {
            // 把二者中较小的那一个放到 res 结果中，unordered_set 会自动去重
            // num 是更小的那一个
            res.insert(num);
        }
        if(memo.count(num-k))
        {
            res.insert(num-k);
        }
        // 记忆 num 值
        memo.insert(num);
    }
    return res.size();
}