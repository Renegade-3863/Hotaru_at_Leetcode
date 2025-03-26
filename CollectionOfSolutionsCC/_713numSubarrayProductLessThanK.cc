#include "Solution.h"

int Leetcode701_800::Soltuion::numSubarrayProductLessThanK(vector<int>& nums, int k)
{
    // 关键词提取：
    // 严格小于 k，连续子数组
    // 那么第一反应应该是滑动窗口
    // 不过我的第一反应是检查 nums 是否可能包含负元素，不知道你有没有这样的冲动
    // 如果没有，可以回看一下前面的题目，滑动窗口的题目合集里面其实是有几道由于包含负元素而导致不满足二分规律的
    // 对于那样的题目，滑动窗口是有问题的
    // 不过好在本题限制了 1 <= nums[i] <= 1000
    // 那么我们滑动窗口的思路就不会有太大的问题
    // 先思考一下怎么滑这个窗口
    // 这道题和我们之前写滑动窗口的题目是很像的
    // 我们考虑用另一个指针去枚举窗口左侧边界 l
    // 注意到这个 l 有一些性质：
    // 它一定只会往右单向移动
    // 因为窗口右边界往右延伸，一定会变得更大
    // 而窗口左边界往左延伸，也一定会变得更大
    // 所以我们可以按照滑动窗口常用的思路：
    // 每次确定 "以某一个元素结尾的子数组个数"
    // 我们每次往右移动一次窗口右边界，之后维护窗口 "内部元素积小于 k" 这一性质
    // 这种维护可以通过 l 指针往右移动来实现
    int n = nums.size();
    // arr 就是前缀积数组
    // left 定义为窗口左边界
    int left = 0, tot = 1, ans = 0;
    for(int right = 0; right < n; ++right)
    {
        // 往右扩展一次右边界
        tot *= nums[right];
        // 之后考虑维护 [left, right] 窗口的性质
        // 注意确保 left 小于等于 right，否则可能会报错
        while(tot >= k && left <= right)
        {
            // 每次往右挪一次 left，减少窗口内的元素总乘积
            tot /= nums[left];
            ++left;
        }
        // 处理完成，现在的区间 [left, right] 就满足总乘积小于 k，而 [left, right] 中的所有元素，都是满足 [l, right] 的乘积小于 k 的
        // 所以我们需要对 ans 加 right-left+1
        ans += right-left+1;
    }
    return ans;
}