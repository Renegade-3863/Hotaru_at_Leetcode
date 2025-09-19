#include "Solution.h"

long long Leetcode2900_3000::Solution::minSum(vector<int>& nums1, vector<int>& nums2)
{
    // 我们仔细思考一下
    // 假设 nums1 的数字和为 sum1，数组中 0 的个数为 cnt1，nums2 的数字和为 sum2，数组中 0 的个数为 cnt2
    // 那么 nums1 的最小结果数据和为 sum1+cnt1，nums2 则为 sum2+cnt2
    // 如果 sum1+cnt1 < sum2+cnt2，那么我们需要往第一个数组中补充数据
    // 而如果 cnt1 为 0，那我们就没法补充数据到 nums1 中
    // 否则，我们一定可以把两个数组都补充道 sum2+cnt2 这个值上
    // 对称地，如果 sum1+cnt1 > sum2+cnt2，那么同理，只要 cnt2 不为零即可
    // 最后，如果 sum1+cnt1 == sum2+cnt2
    // 那么无论怎么样，我们都能够把两个数组维护成最终依然相等的结果
    // 1. 如果 cnt1 == cnt2
    // 那么显然可以
    // 2. 如果 cnt1 > cnt2 
    // 那么自然有 sum1 < sum2，我们依然可以把二者补充到 sum2+cnt2
    // 3. 如果 cnt2 > cnt1
    // 那么自然有 sum1 > sum2，我们依然可以把二者补充到 sum1+cnt1
    unsigned long long sum1 = 0, sum2 = 0;
    unsigned long long cnt1 = 0, cnt2 = 0;
    for(const auto& num : nums1)
    {   
        if(num == 0)
        {
            ++cnt1;
        }
        sum1 += num;
    }
    for(const auto& num : nums2)
    {
        if(num == 0)
        {
            ++cnt2;
        }
        sum2 += num;
    }
    unsigned long long minimum1 = sum1+cnt1, minimum2 = sum2+cnt2;
    if(minimum1 == minimum2 || (minimum1 < minimum2 && cnt1) || (minimum1 > minimum2 && cnt2))
    {
        return minimum1 > minimum2 ? minimum1 : minimum2;
    }
    return -1;
}