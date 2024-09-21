#include "Solution.h"

int Leetcode1_100::Solution::removeDuplicates2(vector<int>& nums)
{
    // 依然可以利用类似循环不变式的方案来进行修改
    // 规定一个变量 left，规定 left 以及左侧的所有元素都是满足题中所给出的 "即使重复，也只能重复出现两次" 这一要求的
    // 注意到这样一个事实：我们可以很容易地维护：left 划定的左侧数组一定是一个有序的数组
    // 使用另一个遍历变量 right，这个变量不断向右遍历，遇到一个新元素，就和 left+1 处的元素交换，并修改 left 的信息
    // 持续到 right 遍历完所有元素
    // cnt 用于记录当前检查的这个元素已经出现的总次数，如果这个值大于等于2了，那么我们就不能将这个元素交换到 left+1 位置了
    // 一旦遇到一个和前一位不一样的元素，我们就需要把 cnt 的值进行重置
    int left = -1, n = nums.size(), cnt = 0;
    // 额外用一个变量记录当前合法的最大值
    int rec = nums[0];
    for(int right = 0; right < n; ++right)
    {   
        // 如果这个值是一个新值，那么我们需要重置 cnt 值
        if(nums[right] != rec)
        {
            cnt = 0;
            rec = nums[right];
        }
        // 如果当前元素出现的次数少于两次，那么这个元素还可以归到合法的区间中，就归进去并更新相关信息
        // 注意，我们规定的是：(left, right) 中的元素一定都是不合法的，没法合并到 left 区间中的，这一循环不变式也是一直会保持的
        if(cnt < 2)
        {
            swap(nums[++left], nums[right]);
            ++cnt;
        }
        // 否则，我们不更新 left，也不进行任何交换，把这个不合法的值留在原位即可
    }
    // 循环全部结束后，left 的值加1就是合法部分的长度
    return left+1;
}