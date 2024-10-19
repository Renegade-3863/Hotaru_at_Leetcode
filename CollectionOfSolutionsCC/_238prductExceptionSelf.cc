#include "Solution.h"

vector<int> Leetcode201_300::Solution::productExceptionSelf(vector<int>& nums)
{
    // 本题同时要求 O(n) 的时间复杂度和 O(1) 的空间复杂度，同时给出了提示：输出数组不算做消耗的空间复杂度
    // 那么我们可以这样来完成这个题目：
    // 首先初始化出输出的结果数组
    int n = nums.size();
    vector<int> res(n, 1);
    // 之后，我们先从右到左遍历一遍 nums 数组，输入最后的乘积的右半部分
    for(int i = n-2; i >= 0; --i)
    {
        res[i] = res[i+1]*nums[i+1];
    }
    // 右半构建完成之后，我们可以用一个单独的变量，记录一轮左半部分，逐一地乘入 res 数组的各项中
    int left = 1;
    for(int i = 0; i < n; ++i)
    {
        res[i] *= left;
        left *= nums[i];
    }
    // 构建完成，可以返回结果了
    return res;
}