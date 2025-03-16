#include "Solution.h"

bool Leetcode601_700::Soltuion::checkPossibility(vector<int>& nums)
{
    // 本质上是判断相邻逆序对数的题目
    // 我们只用一轮遍历，看看有多少紧邻的逆序对就行了
    // 如果有超过一对这种相邻的逆序对，那么就没法最终转换成一个非递减数列
    // 补充：上面的 yy 最后发现是必要条件，不是充分条件
    // 我们还需要确保这不超过一次的紧邻逆序对是 "可修改的"
    // 举个例子：
    // [3, 4, 2, 3]
    // 这个数组虽然只有一个紧邻逆序对 {4, 2}
    // 但是我们如果修改了 4，那么最大只能改成 2
    // 而 2 又小于左边的 3
    // 而我们如果想修改 2，又只能把它改到 3 (要防止超过右边的 3)
    // 而 3 依然是小于 4 的
    // 所以这个唯一的紧邻逆序对实际上是不可修改的
    // 我们模拟一下这个检查过程即可
    int n = nums.size(), cntRev = 0, pos = -1;
    // 特殊情况：如果 n <= 2，那么直接返回 true 即可
    if(n <= 2)
    {
        return true;
    }
    for(int i = 1; i < n; ++i)
    {
        if(nums[i] < nums[i-1])
        {
            // 出现了一个逆序对，我们累加 cntRev 一次
            ++cntRev;
            // 记录逆序对的位置
            pos = i-1;
        }
    }   
    if(cntRev > 1)
    {
        return false;
    }
    if(cntRev == 0)
    {
        return true;
    }
    // 我们用表达式总结一下上面的充分性检查流程
    // 首先，我们检查修改 nums[pos] 能否完成要求
    // 它最小可以调到 nums[pos-1]，而如果 pos == 0，那么就一定可以完成要求，因为 nums[pos] 可以无限小 
    if(pos == 0 || nums[pos-1] <= nums[pos+1])
    {
        return true;
    }
    // 其次，我们检查修改 nums[pos+1] 能否完成要求
    // 它最大可以调到 nums[pos+2]，而如果 pos == n-2，那么就一定可以完成要求，因为 nums[pos+1] 可以无限大
    if(pos == n-2 || nums[pos+2] >= nums[pos])
    {
        return true;
    } 
    // 都没法完成要求，返回 false 即可
    return false;
}