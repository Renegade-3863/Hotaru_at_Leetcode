#include "Solution.h"

int Leetcode201_300::Solution::minSubArrayLen(int target, vector<int>& nums)
{
    // 可以说第一眼看到这个标题就应该反应过来是滑动窗口类问题
    // 规定一对窗口的左右边界 left 和 right
    // 我们要做的是：找出以每个下标作为 right 右边界的情况下，长度最小的可以满足总和大于等于 target 的子数组长度
    int n = nums.size();
    // 规定一个结果值 res，初始值为 nums.size()+1，代表不合法的结果，我们最后可以通过这个长度来判断是否存在可行解
    int left = -1, res = n+1;
    // sum 记录当前窗口中的值的和
    int sum = 0;
    for(int right = 0; right < n; ++right)
    {
        // 先添加值
        sum += nums[right];
        // 检查这个和值是否超过了 target 
        while(sum >= target)
        {
            // 超过了，代表当前 right 位置存在至少一个总和大于等于 target 的子数组
            // 我们可以通过移动 left 指针来找出结束于这个 right 的最短子数组
            res = min(res, right-left);
            sum -= nums[++left];
        }
        // 结束内层循环后，我们就找全了以当前的 right 结尾的所有总和大于等于 target 的子数组
    }
    // 返回结果即可
    return res == n+1 ? 0 : res;
}