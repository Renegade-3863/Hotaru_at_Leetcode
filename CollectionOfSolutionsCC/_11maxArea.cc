#include "Solution.h"

int Leetcode1_100::Solution::maxArea(vector<int>& height)
{
    // 本题的核心问题是求取一个容器可以存储的最大水量
    // 从最简单的暴力方法开始思考
    // 我们可以枚举每一个左侧边界 left，根据这个左边界枚举所有可能的右边界 right，并依次计算对应的面积，经过了 O(n^2) 的遍历之后
    // 就能找到最终的全局最大面积了
    // 考虑是否可以对枚举过程进行优化
    // 首先，我们对于 right 的遍历方法可以是从外到内的，这种情况是否有一些不必要的检查？
    // 如果某个时候：height[left] < height[right] 此时如果我们减小 right，会发生什么？
    // 原面积：(right-left+1)*(height[right])，此时我们把 right 减1
    // 得到的面积：(right-left)*min(height[left], height[right-1])
    // 而我们知道，height[left] 是一定小于 height[right] 的，那么相当于 min(height[left], height[right-1]) 这个式子的最大值
    // 就被我们限定在了一个严格小于 height[right] 的值，此时就不难看出，"得到的面积" 一定是小于 "原面积" 的。
    // 那么显然这种移动就是永远无效的了，后续的推理也是一样的，对于这个确定的左边界，永远也不可能拿到一个比 "原面积" 更大的值了，我们可以剪掉这种检查
    // 这个 "剪掉" 具体应该如何做呢？
    // 最直接的方法自然是右移 left 指针，那此时思考一下 right 是否有必要移动？
    // 如果按原来的思路，我们应该是重新把 right 放到最外侧，重新进行遍历检查
    // 不过，考虑这样的一个事实：
    // 对于原来的 left 值，right 在重走之前的下标的时候，一定都满足 height[right] >= height[left](我们移动 left 的条件保证了这一点)
    // 那么也就是说，对于这些所有的移动，计算得到的面积一定是 height[left] * (right-left+1) (这个left是移动之前的)
    // 不难看出来，这个面积是一定比上一次的 height[left] * (right-(left+1)+1) 要小的
    // 那么我们就不难总结出本题一种线性的双指针解法了
    // 额外考虑一点，如果两侧的垂线高度相等，我们应该移动哪一边？
    // 简单的想法是随意移动一边即可，因为无论移动哪一边，都还有另一边的相同高度值做限定，整体的高度值不会受到影响，只要内部还有更高的高度值，我们就可以找到可行的更大结果
    int left = 0, right = height.size()-1;
    int res = 0;
    while(left < right)
    {
        // 更新最大面积结果
        res = max(res, min(height[left], height[right])*(right-left));
        // 更新边界信息
        if(height[left] <= height[right])
        {
            ++left;
        }
        else
        {
            --right;
        }
    }
    return res;
}