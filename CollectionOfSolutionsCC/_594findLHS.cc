#include "Solution.h"

int Leetcode501_600::Soltuion::findLHS(vector<int>& nums)
{
    // 简单来说，这道题是哈希表的题目
    // 我们考虑按照元素为键，出现次数为值，存储 nums 中每种元素出现的次数
    unordered_map<int, int> cnts;
    for(const auto& num : nums)
    {
        ++cnts[num];
    }
    // 观察到，数组中元素的顺序并不影响最终的结果，因为题目要求找出的是子序列长度
    // 所以我们可以遍历 cnts 中的每一种元素值，检查比它大 1 的元素是否存在，存在的话，更新一次最大长度
    // 再检查比它小 1 的元素是否存在，存在的话，再更新一次最终结果
    // 最后返回结果即可
    int res = 0;
    for(const auto& cnt : cnts)
    {
        if(cnts.count(cnt.first-1))
        {
            // 小 1 的元素存在，更新一次结果
            res = max(res, cnt.second+cnts[cnt.first-1]);
        }
        if(cnts.count(cnt.first+1))
        {
            // 大 1 的元素存在，更新一次结果
            res = max(res, cnt.second+cnts[cnt.first+1]);
        }
    }
    return res;
}