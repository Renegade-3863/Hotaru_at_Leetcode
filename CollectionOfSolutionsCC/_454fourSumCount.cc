#include "Soltuion.h"

int Leetcode401_500::Soltuion::fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4)
{
    // 第一眼看没什么太好的思路，那么我们尝试先暴力进行求解
    // 基本就是一个四重循环，遍历所有可能的四元组
    int len1 = nums1.size(), len2 = nums2.size(), len3 = nums3.size(), len4 = nums4.size();
    int res = 0;
    for(int i = 0; i < len1; ++i)
    {
        for(int j = 0; j < len2; ++j)
        {
            for(int k = 0; k < len3; ++k)
            {
                for(int l = 0; l < len4; ++l)
                {
                    if(nums1[i]+nums2[j]+nums3[k]+nums4[l] == 0)
                    {
                        ++res;
                    }
                }
            }
        }
    }
    return res;
}

// 上面的代码很明显会超时，我们需要关注如何优化我们的遍历方式
// 有一种利用哈希表的比较简单的降一维的策略
int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4)
{
    // 我们用一个哈希表记录四个数组的其中一个，剩下三个正常遍历
    // 记录某一个数组中，各个元素对应出现的次数
    unordered_map<int, int> cnts;
    int res = 0;
    // 假设我们记录 nums1
    for(const auto& num : nums1)
    {
        ++cnts[num];
    }
    int len1 = nums1.size(), len2 = nums2.size(), len3 = nums3.size(), len4 = nums4.size();
    // 之后改四重循环为三重
    for(int j = 0; j < len2; ++j)
    {
        for(int k = 0; k < len3; ++k)
        {
            for(int l = 0; l < len4; ++l)
            {
                int sum = nums2[j]+nums3[k]+nums4[l];
                if(cnts.find(-sum) != cnts.end())
                {
                    res += cnts[-sum];
                }
            }
        }
    }
    return res;
}

// 改成了 O(n^3) 依然超时，我们需要进一步考虑如何优化
// 第一版优化记录的是某种元素值的哈希表
// 这里我们可以考虑记录某两个元素和的哈希表
int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4)
{
    unordered_map<int, int> sumCnts;
    int res = 0;
    // 先用 O(n^2) 的一轮循环，记录其中两组数组所有可能的和值的个数
    int len1 = nums1.size(), len2 = nums2.size(), len3 = nums3.size(), len4 = nums4.size();
    // 这里我们假设记录 nums1 和 nums2 的和值
    for(int i = 0; i < len1; ++i)
    {
        for(int j = 0; j < len2; ++j)
        {
            ++sumCnts[nums1[i]+nums2[j]];
        }
    }
    // 之后，再用一轮 O(n^2) 的循环来遍历另外两个数组的组合，利用哈希表的信息加速计算
    for(int k = 0; k < len3; ++k)
    {
        for(int l = 0; l < len4; ++l)
        {
            int sum = nums3[k]+nums4[l];
            if(sumCnts.find(-sum) != sumCnts.end())
            {
                res += sumCnts[-sum];
            }
        }
    }
    return res;
}