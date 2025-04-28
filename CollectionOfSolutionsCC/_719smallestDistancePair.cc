#include "Solution.h"

int Leetcode701_800::Soltuion::smallestDistancePair(vector<int>& nums, int k)
{
    // 首先，题目对计算用的数对并没有实际的顺序要求，所以我们可以考虑先对 nums 进行排序
    sort(nums.begin(), nums.end());
    // 排好序之后，我们可以发现一些性质：
    // 首先，相近的数值距离一定相对 (但不是绝对) 较小
    // 比如 [1, 1, 3]
    // 之后考虑如何计算数对之间的关系：
    // 最暴力的方法是
    // 枚举 1，匹配 1, 3
    // 枚举 1，匹配 3
    // 得到结果
    // 上面这样的方法很明显是 O(n^2) 的，题目数据范围限制在了 10^4 数量级，所以这种方法肯定会超时
    // 所以我们需要考虑如何压缩成 O(nlogn) (因为我们排序就用了 O(nlogn)..)
    // 既然要二分，那么我们就需要思考：要二分谁？
    // 这道题里，能二分的东西不多，k 是看起来最像需要被拆的那一个
    // 所以我们尝试拆它
    // 我们尝试寻找二分的上下界，也就是：多大的距离有可能是第 k 小的？
    // 我们不难发现，整个数组中，最大的距离就是 max(nums)-min(nums)
    // 最小距离就是 0
    // 所以我们可以对区间 [0, max(nums)-min(nums)] 进行二分
    // 对于每一个二分出来的距离结果
    // 我们可以对 nums 数组使用二分查找
    // 完成下面的任务：
    // 对于以每一个元素 nums[i]，以它结尾，并且距离为 mid 的数对个数
    // 上面的任务可以以 O(nlogn) 的时间复杂度来完成
    // 我们可以先写一下这个函数：
    function<int(int, int)> checkNoBiggerThan = [&](int dist, int idx) -> int
    {
        // 二分查找法可以简单实现
        int left = 0, right = idx-1;
        int res = -1;
        while(left <= right)
        {
            int mid = ((right-left)>>1)+left;
            if(nums[idx]-nums[mid] <= dist)
            {
                // 如果 nums[mid] 与结尾元素的距离不大于 dist，那么最小的满足距离不大于 dist 的左数值一定在 mid 或者它左边
                res = mid;
                right = mid-1;
            }
            else
            {
                // nums[mid] 不满足要求，那么结果一定在 mid 右边
                left = mid+1;
            }
        }
        // 如果 res = -1，说明不存在满足 nums[mid]-nums[res] <= dist 的元素
        // 也就是说，idx 左边的所有元素与它的距离都大于 dist
        // 此时我们返回 0 即可
        if(res == -1)
        {
            return 0;
        }
        // 否则，我们返回的是 [res, idx-1] 的区间长度
        return idx-res;
    };
    // 完成了二分函数，我们写一下外层函数并调用它们即可
    int n = nums.size();
    int left = 0, right = nums[n-1]-nums[0];
    int res = -1;
    while(left <= right)
    {
        int mid = ((right-left)>>1)+left;
        int noBiggerThan = 0, smallerThan = 0;
        for(int i = 0; i < n; ++i)
        {
            noBiggerThan += checkNoBiggerThan(mid, i);
        }
        // 我们检查下面条件：
        // noBiggerThan >= k 
        // 如果上面的条件成立，那么说明 mid 有可能成为最后的结果，我们更新 candidate 答案 res (注意到这个值最后一定会等于最后的结果)
        // 同时，如果答案不是 mid，那么它一定在 mid 的左边
        // 因为不小于 mid 的距离值不少于 k 个，那么可能包含答案的那个距离值就一定是小于当前 mid 的
        if(noBiggerThan >= k)
        {
            res = mid;
            right = mid-1;
        }
        else
        {
            // 否则，mid 一定不会是答案，同时存在的答案一定在 mid 右边，我们更新 left 即可
            left = mid+1;
        }
    }
    return res;
}