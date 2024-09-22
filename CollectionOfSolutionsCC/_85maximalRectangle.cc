#include "Solution.h"

int Leetcode1_100::Solution::maximalRectangle(vector<vector<char>>& matrix)
{
    // 本题要求我们找出一个 rowsxcols 的二维矩阵中最大的只包含1的矩形面积
    // 同样的思路，任何复杂的问题都需要有一个相对简单的切入点
    // 本题，因为我们没法同时变动要找的矩形的行界和列界，因而我们可以尝试固定其中一跳边界
    // 假设我们固定行界，这种方式看起来比较直观
    // 按行进行遍历，每行内固定行界，检查列界
    // 不难发现，其实我们要做的在固定了行界后就是84题：面积最大的矩形
    // 因为我们固定了下方的行界，而此时如果我们把所有连续的从当前行界处向上延伸的1序列看成是上一题中的 "柱子"
    // 其实它们是完全一样的
    // 那么明确了这一点，我们就不难按之前的逻辑(单调栈，动态规划)进行求解
    // 全局的最大值
    int res = 0, m = matrix.size(), n = matrix[0].size();
    // 维护一个类似前缀数组的一维数组，用来模拟类似上一题中的柱子高度数组 heights
    vector<int> heights(n, 0);
    // 遍历所有行界
    for(int i = 0; i < m; ++i)
    {
        // 先更新 heights 数组
        for(int j = 0; j < n; ++j)
        {
            // 只有当柱子能够接到当前行界的时候才能通过前缀递推
            heights[j] = matrix[i][j] == '1' ? heights[j]+1 : 0;
        }
        // 之后在算出来的 heights 数组上运行我们上一题中使用的单调栈/动态规划算法即可
        vector<int> left(n, -1);
        vector<int> right(n, n);
        stack<int> stk;
        for(int j = 0; j < n; ++j)
        {
            while(!stk.empty() && heights[stk.top()] >= heights[j])
            {
                stk.pop();
            }
            left[j] = stk.empty() ? -1 : stk.top();
            stk.push(j);
        }
        stk = stack<int>();
        for(int j = n-1; j >= 0; --j)
        {
            while(!stk.empty() && heights[stk.top()] >= heights[k])
            {
                stk.pop();
            }
            right[j] = stk.empty() ? n : stk.top();
            stk.push(j);
        }
        for(int j = 0; j < n; ++j)
        {
            int width = right[j]-left[j]-1;
            res = max(res, width*heights[j]);
        }
    }
    // 结束后返回最终结果即可
    return res;
}