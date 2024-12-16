#include "Solution.h"

int Leetcode601_700::Soltuion::findShortestSubArray(vector<int>& nums)
{
    // 简单题简单做，读懂了题目的意思，我们进行下面的转述：
    // 1. 找出所有出现次数最多的元素
    // 2. 从所有出现次数最多的元素中，找出一个元素，使得覆盖所有这个元素的连续子数组长度最短
    // 那么我们要做的事情就很简单了
    // 存一个哈希表，这个哈希表中存储这样的数据结构
    // 键：元素值
    // 值：(最早出现位置, 最后出现位置) 数值对
    // 同时只有出现次数最多的元素才会被存到这个哈希表中作为数值对
    // 那么基本的逻辑也就清晰了
    // 我们进行两轮遍历，一轮找出所有出现次数最多的元素
    // 另一轮找出所有出现次数最多的元素最早和最后出现的下标
    // 最后遍历构造出的哈希表，计算出最短的距离 (最短连续子数组的长度就是这个值)
    // 记录数组中每种元素出现的次数
    unordered_map<int, int> cnts;
    // 用于记录每个元素最早和最晚出现的位置下标
    unordered_map<int, pair<int, int>> pos;
    int n = nums.size();
    for(int i = 0; i < n; ++i)
    {
        if(cnts.find(nums[i]) == cnts.end())
        {
            // 第一次出现，记录最早坐标和最后坐标均为 i
            pos[nums[i]] = make_pair<int&, int&>(i, i);
        }
        ++cnts[nums[i]];
        // 更新最后坐标
        pos[nums[i]].second = i;
    }
    // 取出出现次数最多的元素出现的次数，用于后续分析对应元素的最早和最后出现下标   
    int maximum = INT_MIN;
    for(const auto& it : cnts)
    {
        if(it.second > maximum)
        {
            maximum = it.second;
        }
    }
    // 再遍历一轮 cnts 表，对于所有出现了最多次的元素，计算 最后出现下标-最早出现下标+1 这个值，更新最小的那一个作为答案
    int res = INT_MAX;
    for(const auto& it : cnts)
    {
        if(it.second == maximum)
        {
            res = min(res, pos[it.first].second-pos[it.first].first+1);
        }
    }
    return res;
}