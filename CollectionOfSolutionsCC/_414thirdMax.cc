#include "Solution.h"

// 记录一下错误经历，题意理解错了。。。
int Leetcode401_500::Solution::thirdMax(vector<int>& nums)
{
    // 简单的快速选择类问题
    // 我们需要从一个数组中快速选择出第 k 大的数
    // 那么我们可以使用三路分区的算法来既满足分区的属性，又避免大量重复元素导致的效率风险
    // 剩下的基本就是三路的模版了
    // 这个函数的意思是：从 nums[l] 到 nums[r] 中选出第 k 大的那个元素
    int n = nums.size();
    if(n < 3)
    {
        return max(nums[0], nums[1]);
    }
    function<int(int, int, int)> partition = [&](int l, int r, int cnt) -> int 
    {
        // 我们按照这个区间中的最后一个元素作为 pivot 值
        int pivot = nums[r];
        // 之后按照这个值对区间进行三分
        // 两个边界变量 i 和 j，以及一个 k 用于遍历
        int i = l-1, j = r+1;
        // 基本定义是：
        // [l, i] 之间的元素都是小于 pivot 的，(i, k) 之间的元素都是等于 pivot 的，[j, r] 之间的都是大于 pivot 的
        // 剩下的部分是还没做出判断的 
        int k = l;
        while(k < j)
        {
            // 每一个元素有三种可能
            // 1. nums[k] < pivot
            // 那么把这个元素放到 nums[i+1] 的位置
            // 注意，我们换过来的元素一定是一个等于 pivot 的，所以我们可以直接移动 k
            if(nums[k] > pivot)
            {
                swap(nums[k++], nums[++i]);
            }
            // 2. nums[k] == pivot
            // 那么不用做任何事情，直接移动 k 即可
            else if(nums[k] == pivot)
            {
                ++k;
            }
            // 3. nums[k] > pivot
            // 那么此时我们要把 nums[k] 换到 nums[j-1] 的位置上
            // 但是此时因为我们不能确定换过来的元素一定是等于 pivot 的元素
            // 所以我们不能移动 k 值
            else
            {
                swap(nums[k], nums[--j]);
            }
        }
        // 经过了上面的调整，我们只需要判断 pivot 这个值覆盖了的区间
        // 这个区间就是 [i+1, j-1]
        // 我们此时只需要这个范围是否覆盖到了 l+cnt-1 这个下标
        if(l+cnt-1 >= i+1 && l+cnt-1 <= j-1)
        {
            return pivot;
        }
        else if(l+cnt-1 < i+1)
        {
            return partition(l, i, cnt);
        }
        return partition(j, r, cnt-(j-l));
    };
    return partition(0, nums.size()-1, 3);
}

// 重申一下，本题要求的是找出第3大的那个数，而不是非升序排序后的第三个数
// 所以我们的想法其实可以格外简单
int thirdMax(vector<int>& nums)
{
    // 我们可以简单地判断第一大的数，第二大的数，最后就是第三大的数
    // 第一轮：找 nums 中最大的那个元素
    int max1 = INT_MIN;
    int n = nums.size();
    for(int i = 0; i < n; ++i)
    {
        max1 = max(max1, nums[i]);
    }
    int max2 = INT_MIN;
    for(int i = 0; i < n; ++i)
    {
        if(nums[i] != max1)
        {
            max2 = max(nums[i], max2);
        }
    }
    int max3 = INT_MIN;
    bool found = false;
    for(int i = 0; i < n; ++i)
    {
        if(nums[i] != max1 && nums[i] != max2)
        {
            found = true;
            max3 = max(nums[i], max3);
        }
    }
    return found ? max3 : *max_element(nums.begin(), nums.end());
}