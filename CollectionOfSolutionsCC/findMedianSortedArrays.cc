#include "Solution.h"

double Leetcode1_100::Solution::findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
{
    // 推广到从一个数组中找第 k 小的数字的问题
    // 对于两个子数组，如果我们要找二者合并之后第 k 小的那个数字，那么我们就需要找到两个数组中对应第 k/2 小的数字，通过这样的方式，我们可以通过一些比较减少遍历次数
    // 假设 nums1[k/2] >= nums2[k/2]，那么说明更小的那一侧的 k/2 个数字一定在合并后的前 k 个数中，而另外一个数组的 k/2 个元素就不一定了，不过我们可以通过这种方式丢掉 k/2 个数字
    int m = nums1.size(), n = nums2.size();
    function<double(vector<int>&, vector<int>&, int, int, int, int, int)> findKth = [&](vector<int>& nums1, vector<int>& nums2, int start1, int end1, int start2, int end2, int k) -> double
    {
        // 如果某个数组的元素用光了，那么就直接返回另一个数组的第k个元素即可
        // nums1 用光了，返回 nums2 的第 k 个元素
        if(start1 > end1)
        {  
            return (double)nums2[start2+k-1];
        }
        if(start2 > end2)
        {
            return (double)nums1[start1+k-1];
        }
        // 到这里说明两个数组都还有剩余元素
        // 如果要找的就是合并后的第一个元素，那么只需要比较两个数组的第一个元素即可
        if(k == 1)
        {
            return (double)min(nums1[start1], nums2[start2]);
        }
        // 否则，只需要检查两个数组对应的第 k/2 个元素
        // 注意越界问题
        int i = start1 + k/2 - 1 <= end1 ? start1 + k/2 - 1 : end1;
        int j = start2 + k/2 - 1 <= end2 ? start2 + k/2 - 1 : end2;
        // nums1 对应位置的元素不小于 nums2 对应位置的元素，我们可以丢弃 nums2 中对应位置以及前面直到 start2 之间所有的值
        if(nums1[i] >= nums2[j])
        {
            // 这里最后一个参数不做化简的原因在于，j可能不等于 start2 + k/2 - 1，而是 end2
            return findKth(nums1, nums2, start1, end1, j+1, end2, k-(j-start2+1));
        }
        else
        {
            return findKth(nums1, nums2, i+1, end1, start2, end2, k-(i-start1+1));
        }
        // 不会执行到这一行，除非 if-else 语句出问题
        return -1.0;
    };
    // 我们要找的就是第 (m+n)>>1 大的元素和第 (m+n+1)>>1 大的元素的平均值
    return (findKth(nums1, nums2, 0, m-1, 0, n-1, (m+n)>>1) + findKth(nums1, nums2, 0, m-1, 0, n-1, (m+n+1)>>1))*0.5;
}