#include "Solution.h"

bool Leetcode1_100::Solution::canJump(vector<int>& nums)
{
    // 和跳跃游戏 II 一样的题目，本题要求更简单，只要求判断是否能够达到最后一个下标
    // 我们可以使用类似的贪心思路进行推断
    // 其实本质上这种贪心思想更类似于 BFS 广搜算法
    // 我们规定一对左右边界，标记当前下一步可达的所有位置下标
    // 闭区间
    int start = 0, end = 0;
    // 对于下一步每一个可达的下标，更新全局的最大可达位置下标
    int maxPos = 0;
    // 我们肯定是需要一个循环来执行这个类似 BFS 的更新算法，那么如何规定循环的结束条件呢？
    // 比较好理解的结论是：只要我们找到的所有下一步可达位置下标范围，包括了最后一个位置下标，那么我们就可以直接退出了
    // 而本题我们其实就是要判断这个循环能不能退出，这是本题和 跳跃游戏 II 的本质区别
    // 其实可以使用一个布尔变量标记每轮 for 循环结束后 (也就是 BFS 每一层结束后) maxPos 是否变得更大了，如果某一轮更新没有变得更大，那么很显然后面也不可能变得更大了
    // 因而我们就可以断定这个数组，我们没法走到结尾
    // 根据这个思路，就可以开始写循环代码了
    int n = nums.size();
    bool changed = false;
    while(end < n-1)
    {
        for(int i = start; i <= end; ++i)
        {
            // 更新当前步数+1可达的最大位置下标
            if(maxPos < i+nums[i])
            {
                maxPos = i+nums[i];
                changed = true;
            }
        }
        // 更新区间信息
        start = end+1;
        end = maxPos;
        // 这轮循环结束后 maxPos 没有变化，同时也没有覆盖到 n-1 下标，我们就可以返回 false 了
        if(!changed)
        {
            return false;
        }
        changed = false;
    }
    // 如果循环成功退出了，那么显然我们可以到达最后一个下标，返回 true 即可
    return true;
}