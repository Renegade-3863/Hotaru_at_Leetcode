#include "Solution.h"

int Leetcode601_700::Soltuion::maximumProduct(vector<int>& nums)
{
    // 三数之和变成三数之积了
    // 我们依然可以尝试用类似的思路求解本题
    // 首先对 nums 数组进行排序
    sort(nums.begin(), nums.end());
    int n = nums.size();
    // 思考：最大的乘积无非有几种情况
    // 1. 数组中最大的三个数的乘积
    // 2. 数组中最大的一个正数乘上最小的两个负数
    // 我们分开求两个解，并输出二者的较大值作为答案即可
    return max(nums[0]*nums[1]*nums[n-1], nums[n-3]*nums[n-2]*nums[n-1]);
}