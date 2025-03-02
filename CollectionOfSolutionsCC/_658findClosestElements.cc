#include "Solution.h"

vector<int> Leetcode601_700::Soltuion::findClosestElements(vector<int>& nums, int k, int x)
{
    // 比较容易想到的解法是用二分查找+双指针扩散找结果
    // 我们首先找出整个数组中最接近 x 的那一个值，然后用双指针 left 和 right 分别尝试往左右两侧扩散
    // 直到找全 k 个要求的结果
    // 二分查找的过程直接用一般的模版就行
    // 定义 idx 记录已知的最靠近 x 的值的下标，初始值为 -1
    int idx = -1, n = nums.size();
    // [left, right] 标记可能存在 idx 结果的区间，diff 记录已知的最小差距值
    int left = 0, right = n-1, diff = INT_MAX;
    while(left <= right)
    {
        // 取中点
        int mid = ((right-left)>>1)+left;
        // 我们需要的其实是 abs(nums[mid]-x) 这个值，但是移动指针需要的是 nums[mid]-x
        // 分析一下：
        // 1. 如果 nums[mid]-x < 0，说明 mid 左侧的所有值都不可能比 mid 更靠近 x
        // 那么我们可以直接记录 idx 为 mid，并把 left 放到 mid+1
        // 但是还是要加上 diff 的判断，因为可能会有一左一右两个靠近 x 的值，需要比较
        if(nums[mid]-x < 0)
        {
            if(abs(nums[mid]-x) < diff)
            {
                diff = abs(nums[mid]-x);
                idx = mid;
            }
            else if(abs(nums[mid]-x) == diff)
            {
                idx = min(mid, idx);
            }
            left = mid+1;
        }
        // 2. 如果 nums[mid]-x == 0，那么我们就可以直接结束循环了，找到 x 了
        else if(nums[mid]-x == 0)
        {
            idx = mid;
            break;
        }
        // 3. 如果 nums[mid]-x > 0，说明 mid 右侧的所有值都不可能比 mid 更靠近 x
        // 我们可以直接记录 idx 为 mid，并把 right 放到 mid-1
        // 但是还是要加上 diff 的判断，因为可能会有一左一右两个靠近 x 的值，需要比较
        else
        {
            if(abs(nums[mid]-x) < diff)
            {
                diff = abs(nums[mid]-x);
                idx = mid;
            }
            else if(abs(nums[mid]-x) == diff)
            {
                idx = min(mid, idx);
            }
            right = mid-1;
        }
    }
    // 准备开始扩散
    left = idx-1; right = idx+1;
    // 往左右两侧扩散结果
    int cnt = 1;
    vector<int> res;
    while(cnt < k && cnt < n)
    {
        // 对每一对 (nums[left], nums[right]) 数值对，我们首先进行比较
        // 如果 abs(nums[left]-x) <= abs(nums[right]-x)，那么填入 nums[left]，left 往左走一步
        // 否则填入 nums[right]，right 往右走一步
        // 注意数组越界问题
        int leftDiff = left >= 0 ? abs(nums[left]-x) : -1, rightDiff = right < n ? abs(nums[right]-x) : -1;
        if(leftDiff == -1)
        {
            ++right;
        }
        else if(rightDiff == -1)
        {
            --left;
        }
        else
        {
            if(leftDiff <= rightDiff)
            {
                --left;
            }
            else
            {
                ++right;
            }
        }
        // 无论怎样，我们都会多记录一个结果，cnt 加一即可
        ++cnt;
    }
    return vector<int>(nums.begin()+left+1, nums.begin()+right);
}