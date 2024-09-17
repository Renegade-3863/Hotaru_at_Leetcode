#include "Solution.h"

int Leetcode1_100::Solution::trap(vector<int>& height)
{
    /* 可以说是非常经典的一道动态规划/单调栈类型的困难题了，不过如果了解了基本思路，其实无论哪种实现算法，本质上都是一种求解过程罢了 */
    // 对于一组柱子，我们要接水，那么有几种思考切入点
    // 最简单的分析方法就是，考虑每个下标可以存多少雨水
    // 如果要求解这个问题，我们可以考虑计算出每个下标位置左侧和右侧最高的比它高的最高的柱子的高度(因为这两根柱子是最直接的决定这个下标位置可以存多少水的柱子)
    // 要求解这些信息，我们有很多种不同的策略
    // 首先考虑动态规划是否可行
    // 最优子结构性质？
    // 对于一个下标 i，假设其左侧(包括它本身)最高的不低于 height[i] 的柱子高度为 left[i]
    // 那么显然 left[i] = max(height[i], left[i-1])
    // 即，它左侧(包括本身)最高的不低于 height[i] 的柱子的高度应该是它左侧紧邻的柱子的对应定义值，和它本身之间更高的那一个
    // 于是，我们就可以通过这个递推关系式，分别求出 left 数组和 right 数组，之后的求解就很简单了
#if 0
    int n = height.size();
    vector<int> left(n), right(n);
    left[0] = height[0];
    for(int i = 1; i < n; ++i)
    {
        left[i] = max(left[i-1], height[i]);
    }
    right[n-1] = height[n-1];
    for(int i = n-2; i >= 0; --i)
    {
        right[i] = max(right[i+1], height[i]);
    }
    // 求解完成，可以进行计算了
    // res 用来记录最终结果
    int res = 0;
    for(int i = 0; i < n; ++i)
    {
        res += min(left[i], right[i])-height[i];
    }
    return res;
#endif 
    // 上面这种类似 dp 算法的递推形式固然简单，不过我们敬爱的算法开发者们显然不认为这个 O(2n) 的额外内存空间是必须的，它们尝试更好的常数空间优化
    // 观察一些有关这两个数组的性质，我们会发现，如果要优化，就必须做到在更新的过程中就计算每个位置的水量
    // 能做到吗？
    // 我们考虑把 left 数组和 right 数组替换成两个变量 leftMax 和 rightMax，代表当前找到的下标 i 左侧和右侧最高的高度值
    // 那么我们如何通过更新这两个变量，来满足在更新过程中计算出一些下标处的可存水量呢？
    // 不难想到，单一方向的更新肯定是不行的，因为必须要同时知道两侧的最大高度值，我们才能进行水量的更新
    // 如何做到这一点？
    // 双向更新？ ->  双指针？
    // 考虑使用双指针同时更新 leftMax 和 rightMax
    // 一个 left 指针，一个 right 指针
    // 定义两个指针如下
    // left 指针左侧的所有位置都已经完成了水量的计算
    // right 指针右侧的所有位置都已经完成了水量的计算
    // 初始时，left 指向0，right 指向 height.size()-1，上面的定义是满足的
    // 那么之后应该如何推进？
    // 我们先根据 height[left] 来更新 leftMax，代表 height[left] 这个位置左侧最大的高度值
    // 再根据 height[right] 来更新 rightMax，代表 height[right] 这个位置右侧最大的高度值
    // 此时我们能移动某一侧的指针吗？
    // 显然是可以的，根据 leftMax 和 rightMax 各自的定义，我们不难看出它们不可能变小，只能要么一直不变，要么随着更新不断变大
    // 所以在这个时刻，我们检查 leftMax 和 rightMax，如果 leftMax < rightMax，说明什么？
    // 说明 left 指针指向的这个位置上的元素的限制柱子高度一定是 leftMax，想明白了这一点，后面的就迎刃而解了
    // 因为此时 left 及其左侧所有的元素的大小都是小于 right 及其右侧的柱子中最高的那一个的值的
    // 而后面我们继续移动 right 指针(只能继续向左)，得到的 rightMax 的值一定不会小于现在的这个 rightMax
    // 所以直接把此时这个较小的 leftMax 值作为 height[left] 位置的限制高度没有任何问题
    // 反之，对于 leftMax >= rightMax 的情况是一样的
    // 这样，一种简单的空间优化方案就呼之欲出了
    // 写出代码实现也就很简单了
    int left = 0, right = height.size()-1;
    int leftMax = 0, right = 0;
    int res = 0;
    while(left <= right)
    {
        // 先根据 height[left] 更新 leftMax
        leftMax = max(height[left], leftMax);
        // 再根据 height[rihgt] 更新 rightMax
        rightMax = max(height[rihgt], rightMax);
        // 按上面的推导进行计算即可
        if(leftMax <= rightMax)
        {
            res += leftMax - height[left];
            ++left;
        }
        else
        {
            res += rightMax - height[right];
            --right;
        }
    }
    return res;
}