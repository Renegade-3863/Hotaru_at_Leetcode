#include "Solution.h"

vector<int> Leetcode301_400::Solution::intersect(vector<int>& nums1, vector<int>& nums2)
{
    // 和上一题没有本质区别，面试官如果问你这道题，基本上都是想考察你对数据库连接操作的理解
    // 我们沿用上一题的解法，稍微改一点逻辑即可

    // 学完了数据库中有关外部排序归并的思想，再来看这道题，感觉其实就是一个很简单的实践
    // 对于两个有序的数组，我们想要求交集就非常简单
    // 利用两个指针 (在外部排序归并中，这相当于给每个归并段分配了一个缓冲区用于在内存中进行实际的比较)
    // 每次检查两个指针指向的元素是否相等
    // 1. 相等，并且输出结果中的元素不等于这个元素，那么把这个元素尾接到输出结果数组中
    // 2. 不相等，那么我们只需要移动值较小的那一个指针即可，因为另一个数组中不再可能有这个较小值了
    // 循环直到任何一个指针移动到了结尾，因为我们要求的是交集，所以只要任何一个数组检查完成，整个流程就可以结束了
    int ptr1 = 0, ptr2 = 0;
    int m = nums1.size(), n = nums2.size();
    // 对两个数组进行排序，这一步是 O(nlogn) 的
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
    // 剩下的就是上面的流程了
    vector<int> res;
    while(ptr1 < m && ptr2 < n)
    {
        // 1.
        if(nums1[ptr1] == nums2[ptr2])
        {
            // 要求的唯一区别在于，本题不要求去重，所以这里我们只需要删掉这个判断条件即可
            res.push_back(nums1[ptr1]);
            ++ptr1; ++ptr2;
        }
        // 2.
        else if(nums1[ptr1] > nums2[ptr2])
        {
            ++ptr2;
        }
        else
        {
            ++ptr1;
        }
    }
    return res;
}