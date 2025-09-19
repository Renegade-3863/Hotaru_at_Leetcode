#include <iostream>
#include <stack>

class Solution {
public:
    int trap(vector<int>& height)
    {
        // 我们单刀直入问题本身
        // 思索一下题目要求我们做的事情是什么
        // 无非就是这个问题：
        // 每一个下标上，可以接到多少雨水？
        // 要解决这个问题，我们需要进一步解构问题本身：
        // 对于一个下标，它能接到的雨水量，无非就是它左右两侧的最高柱子中，较矮的那一个与它本身的高度差值
        // 那么我们依然可以用类似哈希表的方法来处理这道题
        int n = height.size();
        // 为了避免最后比较的时候出现默认值的错误，这里我们用 INT_MAX 作为默认值
        vector<int> left(n, INT_MAX);
        vector<int> right(n, INT_MAX);
        // 我们同时记录两个全局值，一个记录“当前遍历到的位置左侧最大的柱子的高度
        // 另一个记录”当前遍历到的位置右侧最大的柱子的高度
        // 两个变量交替使用即可
        int leftMax = height[0], rightMax = height[n-1];
        // 第一步，先处理 left 数组
        for(int i = 0; i < n; ++i)
        {
            // 检查 height[i] 与 leftMax 之间的大小关系
            // 如果 height[i] 小于 leftMax，那么我们就可以直接把 leftMax 作为 left[i] 的值
            // 否则，我们就用 height[i] 更新 leftMax，并把 height[i] 作为 left[i] 的值
            if(height[i] < leftMax)
            {
                left[i] = leftMax;
            }
            else
            {
                leftMax = height[i];
                left[i] = leftMax;
            }
        }
        for(int i = n-1; i >= 0; --i)
        {
            // 反过来处理 right 数组，思路和上面一样，只是方向不一样而已
            if(height[i] < rightMax)
            {
                right[i] = rightMax;
            }
            else
            {
                rightMax = height[i];
                right[i] = rightMax;
            }
        }
        // 处理完成后，我们只需要遍历一轮 left 和 right 数组，根据长x高的算法计算一下对应的总水量即可
        int res = 0;
        for(int i = 0; i < n; ++i)
        {
            res += (min(left[i], right[i])-height[i]);
        }
        return res;
    }
}