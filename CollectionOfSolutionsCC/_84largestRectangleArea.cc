#include "Solution.h"

int Leetcode1_100::Solution::largestRectangleArea(vector<int>& heights)
{
    // 本题要求我们找出一组连续柱子能构成的最大矩形面积
    // 无论多么复杂的问题都需要一个相对简单的切入点，考虑本题可以有什么样的切入点
    // 我们需要计算的是一个面积值，矩形面积公式都很熟悉：长x高
    // 那么本题的一种比较简单的切入方案就是，找出以每个柱子的高度作为整个矩形高度的所有矩形中，面积最大的值
    // 此时我们会发现，我们的讨论变得简单了一些，因为限定于每个固定的高度，此时我们要找面积最大值，就只需要想办法把长变得尽量大即可
    // 分析到这一步，我们发现问题逐渐明晰
    // 根本思路就是，通过某种方案，我们可以记录下对应所有高度值的矩形向左和向右最远可以延伸到的下标位置
    // 这个方案也就是本题的核心问题了
    // 如果一个高度值的下标范围可以延伸到某个下标，那么必须有：这个下标和该高度值下标之间所有柱子的高度都是不大于该高度值下标处柱子高度的
    // 我们可以先观察一下这是否蕴含了某种递推性质(或者子问题性质)
    // 显然可以有，假设我们定义这样一个数组
    // left[i] 代表 heights 数组中位于下标 i 以及其左侧所有元素中从右到左第一个小于 heights[i] 的元素的下标
    // 那么 left[i] 就是
    // 1. heights[i] > heights[i-1] : i-1
    // 2. heights[i] <= heights[i-1] : 循环回溯, 因为这个小于 heights[i-1] 这个元素的柱子不一定小于 heights[i]
    // 因而我们需要进一步根据 heights[left[i]] 和 heights[i] 的大小关系来进行推理
    // 1) 如果 heights[i] > heights[left[i-1]]，那么可以简单地把 left[i] 设置为 left[i-1]，因为 (left[i-1], i-1] 之间的所有元素都是不小于 heights[i-1] 的
    // 因而也都一定是不小于 heights[i] 的
    // 2) 如果 heights[i] <= heights[left[i-1]]，那么我们就循环检查，继续检查从 left[i-1] 这个位置向左第一个小于 height[left[i-1]] 的柱子的高度
    // 直到我们找到了一个高度小于 heights[i] 的柱子或者找到了下标 -1
    int n = heights.size();
    vector<int> left(n, -1);
    vector<int> right(n, n);
    // 先递推求解 left 数组
    for(int i = 1; i < n; ++i)
    {
        int tmp = i-1;
        while(tmp >= 0 && heights[tmp] >= heights[i])
        {
            // 回溯
            tmp = left[tmp];
        }
        left[i] = tmp;
    }
    // 再递推求解 right 数组
    for(int i = n-2; i >= 0; --i)
    {
        int tmp = i+1;
        while(tmp <= n-1 && heights[tmp] >= heights[i])
        {
            // 回溯
            tmp = right[tmp];
        }
        right[i] = tmp;
    }
    // 进行实际的计算
    int res = 0;
    for(int i = 0; i < n; ++i)
    {
        // 计算以 heights[i] 为高的矩形的最大面积
        int width = right[i]-left[i]-1;
        res = max(res, width*heights[i]);
    }
    return res;
}

// 动态规划转单调栈
// 为什么会想到单调栈这种数据特种数据结构？
// 根据上面动态规划的步骤，我们观察循环的步骤，会发现 tmp 值一定是会随着循环不断进行而越变越小的
// 那么我们是否能通过某种方式优化掉这个看起来冗余的循环呢？
// 就是说，我们能不能提前知道 heights[i] 左侧第一个比它高度小的柱子的下标呢？
// 如果把我们的算法逻辑展开成用折线图动态模拟，你会发现其实我们本质上就是在不断地维护一个总体的单调递增序列
// 因为我们一旦找到了一个高度低于前一个元素的值，就会不断向前回溯寻找，直到找到第一个小于它的元素
// 因而，我们只需要维护一个基于这个原数组的全局单调递增序列即可
// 基于这个思路，单调栈算法就很明晰了
int largestRectangleArea(vector<int>& heights)
{
    int n = heights.size();
    // 创建一个栈用于模拟单调栈
    stack<int> stk;
    vector<int> left(n, -1);
    vector<int> right(n, n);
    for(int i = 0; i < n; ++i)
    {
        // 我们来维护栈内元素单调递增序列的性质
        while(!stk.empty() && heights[stk.top()] >= heights[i])
        {
            stk.pop();
        }
        left[i] = stk.empty() ? -1 : stk.top();
        // 别忘了压栈
        stk.push(i);
    }
    // 重置栈内元素
    stk = stack<int>();
    for(int i = n-1; i >= 0; --i)
    {
        // 我们来维护栈内元素单调递增序列的性质
        while(!stk.empty() && heights[stk.top()] >= heights[i])
        {
            stk.pop();
        }
        right[i] = stk.empty() ? n : stk.top();
        // 别忘了压栈
        stk.push(i);
    }
    // 求解最终结果的流程和上面是一致的
    int res = 0;
    for(int i = 0; i < n; ++i)
    {
        // 计算以 heights[i] 为高的矩形的最大面积
        int width = right[i]-left[i]-1;
        res = max(res, width*heights[i]);
    }
    return res;
}

// 最后提一句，单调栈的优化策略实际上并没有完全省去循环，实际上它只压缩了重复的循环回溯
// 也就是说，我们只需要检查一次每个元素前面比它小的第一个元素就够了