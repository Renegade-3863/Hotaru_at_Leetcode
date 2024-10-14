#include "Solution.h"

vector<string> Leetcode201_300::Solution::summaryRanges(vector<int>& nums)
{
    // 题目要求我们把一个分立的数组合并成一组区间集合
    // 应该是一道简单的模拟类问题
    // 我们尝试进行一轮模拟
    int n = nums.size();
    if(n == 0)
    {
        return {};
    }
    // left 定义为当前新的分立区间的左边界，right 定义为当前分立区间的右边界
    int left = nums[0], right = nums[0];
    vector<string> res;
    // 对 nums 进行一轮遍历
    for(int i = 1; i < n; ++i)
    {
        // 1. 如果当前的值相对上一个元素不是连续的，那么我们就可以进行区间添加了
        if(nums[i] > nums[i-1]+1)
        {
            // 构造出区间字符串
            string interval = to_string(left);
            if(left != right)
            {
                interval += "->"+to_string(right);
            }
            res.push_back(interval);
            // 区间添加结束后，同步更新 left
            left = nums[i];
        }
        // 更新右边界
        right = nums[i];
    }
    // 我们还需要把最后一个区间也添加进来，因为循环中我们添加区间的标准是(相邻两个元素差距大于1，所以会漏掉最后一个区间)
    string interval = to_string(left);
    if(left != right)
    {
        interval += "->"+to_string(right);
    }
    res.push_back(interval);
    return res;
}