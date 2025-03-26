#include "Solution.h"

int Leetcode701_800::Soltuion::findLength(vector<int>& nums1, vector<int>& nums2)
{
    // 据说是腾子很爱考的一道题
    // 本质思想很简单，就是二分子数组长度+滚动哈希判同
    // 选一个质数作为取模的基底
    const unsigned long long p = 13131; 
    int m = nums1.size(), n = nums2.size();
    // 之后考虑编写一个滚动哈希的函数
    function<int(vector<int>&, vector<int>&, int)> rollingHash = [&](vector<int>& nums1, vector<int>& nums2, int len) -> int
    {
        // 我们用一个哈希集合记录 nums1 和 nums2 的长度为 len 的子数组中每一种哈希值的出现情况
        unordered_set<unsigned long long> memo;
        int m = nums1.size(), n = nums2.size();
        // 首先检查 nums1 的长度为 len 的子数组，计算它们的哈希值，使用上面定义的 p 作为公式参数
        // hash 用于记录哈希值
        unsigned long long hash = 0;
        unsigned long long expr = 1;
        for(int i = 0; i < len; ++i)
        {
            hash = hash*p+nums1[i];
            expr *= p;
        }
        // 记录哈希值
        memo.insert(hash);
        // 之后是滚动计算
        for(int i = len; i < m; ++i)
        {
            hash = hash*p-expr*nums1[i-len]+nums1[i];
            // 把当前子数组的哈希值记录到 memo 哈希集合中
            memo.insert(hash);
        }
        // nums1 处理完成，之后我们考虑用同样的方法处理 nums2
        hash = 0;
        for(int i = 0; i < len; ++i)
        {
            hash = hash*p+nums2[i];
        }
        // 我们检查之前在处理 nums1 时是否取到过这个值
        if(memo.count(hash))
        {
            return len;
        }
        // 之后继续滚动处理
        for(int i = len; i < n; ++i)
        {
            hash = hash*p-expr*nums2[i-len]+nums2[i];
            if(memo.count(hash))
            {
                return len;
            }
        }
        // 否则，没找到，我们返回 -1 即可
        return -1;
    };
    // 外层，我们用二分法，二分处理我们检查的 "答案长度"
    int left = 1, right = min(m, n), res = 0;
    // 可能答案的最长长度为二者中更短的那一个，最短长度为 1
    while(left <= right)
    {
        int mid = ((right-left)>>1)+left;
        // 取完中点，我们考虑长度为 mid 的子数组是否可以满足要求
        int l = rollingHash(nums1, nums2, mid);
        if(l == -1)
        {
            // 这个长度不可行，那么所有 [mid, right] 之间的长度都不可能了
            // 我们修改 right 即可
            right = mid-1;
        }
        else
        {
            // 这个长度可行，那么所有 [left, mid] 之间的长度我们都不用检查了
            left = mid+1;
            // 别忘了更新 res 
            res = mid;
        }
    }
    return res;
}