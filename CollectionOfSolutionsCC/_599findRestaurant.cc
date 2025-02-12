#include "Solution.h"

vector<string> Leetcode501_600::Soltuion::findRestaurant(vector<string>& list1, vector<string>& list2)
{
    // 简单题简单做，理解题意很快就能找到方法
    // 用一个哈希表，记录第一个列表 list1 中每个字符串出现的下标
    // 之后遍历第二个列表 list2，每遇到一个在 list1 中出现过的字符串，就累加它们的下标，结果记为 sum
    // 维护一个全局的 "当前最小索引和" 值 minIdx
    // 如果 minIdx == sum，那么当前这个字符串可以添加到 res 数组中 (答案数组)
    // 如果 minIdx > sum，那么我们需要清空 res 数组，把这个字符串添加到清空后到 res 中，并更新 minIdx
    // 最后，如果 minIdx < sum，那么我们不能把当前字符串添加到 res 中
    unordered_map<string, int> idx;
    int m = list1.size(), n = list2.size();
    for(int i = 0; i < m; ++i)
    {
        idx[list1[i]] = i;
    }
    // 记录完成，对 list2 进行遍历
    int minIdx = INT_MAX;
    vector<string> res;
    for(int i = 0; i < n; ++i)
    {
        if(idx.count(list2[i]))
        {
            int sum = i+idx[list2[i]];
            if(sum == minIdx)
            {
                res.push_back(list2[i]);
            }
            if(sum < minIdx)
            {
                res.clear();
                res.push_back(list2[i]);
                minIdx = sum;
            }  
            // 否则什么都不做          
        }
        // 没找到，直接跳过 list2[i] 即可
    }
    return res;
}