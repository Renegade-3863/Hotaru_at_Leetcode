#include "Solution.h"

int Leetcode501_600::Soltuion::findUnsortedSubarray(vector<int>& nums)
{
    // 本题是一个很有趣的思维类题目，本身不涉及太深的算法知识，但有点考验智商
    // 我们思考这样一个问题：
    // 什么时候，一个元素必须被纳入最终排序的范围？
    // 我们不难想到这样的思路：
    // 如果一个元素比它左边的所有元素都是不小于，那么很明显我们就不用对它进行排序
    // 而如果一个元素并不 "不小于" 它左边所有的元素，那么很明显，我们需要把它和左边 "第一个大于它" 的元素，以及之间的所有元素进行排序
    // 这种第一想法建立下来之后，我们就不难想到单调栈的解法
    // 我们可以从左往右建立单调非递减栈
    // 栈内保存一个单调非递减的数组 
    // 每次遇到一个新元素 nums[i]
    // 我们把它和栈顶的元素进行比较
    // 如果栈顶元素也不大于 nums[i]，那么我们直接把它压入栈中即可
    // 但如果栈顶元素是大于 nums[i] 的，那么说明这个 nums[i] 就必须和前面的某个元素交换一下位置才能保证数组有序
    // 我们不断弹出栈顶元素，并记录每个栈顶元素在原数组中第一次出现的下标，直到栈顶元素重新满足不大于 nums[i]
    // 那么此时我们保留的这最后一个大于 nums[i] 的元素的下标，就是我们必须进行排序的区间的一个左端点了 (但不一定是最终的左端点)
    // 不过我们已经知道，至少这个下标以及往右直到 i 之间的元素，就已经必须被排序了
    // 保持这样的遍历模式，不断更新要排序的区间的左端点和右端点，直到我们遍历完整个数组为止
    // 最后，我们就找到了最短需要排序的区间，计算其长度即可
    // 标记左右端点
    int n = nums.size();
    int leftMost = n, rightMost = -1;
    stack<int> stk;
    // 记录数组中每个元素第一次出现的下标
    unordered_map<int, int> firstApp;
    for(int i = 0; i < n; ++i)
    {
        // 如果 nums[i] 是第一次出现，那么记录它出现的下标
        if(!firstApp.count(nums[i]))
        {
            firstApp[nums[i]] = i;
        }
        // 如果栈为空，或者栈顶元素不大于 nums[i]，那么直接压栈即可
        if(stk.empty() || stk.top() <= nums[i])
        {
            stk.push(nums[i]);
            continue;
        }
        // 否则，说明栈顶元素是大于 nums[i] 的，此时我们需要定位新的左边界和右边界信息
        // 提问：这里为什么需要保留触发 while 循环弹出的这个 top 值？
        // 解答：因为这个元素依然在前面，而且它是到 i 这个位置为止所有元素中最大的那一个，所以它可以代替前面这 i+1 个元素整体来触发后续的循环弹出
        int tmp = stk.top();
        while(!stk.empty() && stk.top() > nums[i])
        {
            // 更新左边界
            leftMost = min(leftMost, firstApp[stk.top()]);
            // 提问：这里 firstApp 内记录的信息，是否需要重置？
            // 解答：不需要，因为后面压入的同值元素不会影响这个定义的正确性
            // 弹出这个栈顶元素
            stk.pop();
        }
        stk.push(tmp);
        // 更新右边界即可
        rightMost = max(rightMost, i);
    }
    // 循环结束，[leftMost, rightMost] 区间就是需要排序的区间
    // 注意，二者是同步更新的，所以我们只需要检查其中一个值是否合法
    if(leftMost == n)
    {
        return 0;
    }
    // 合法，返回区间长度即可
    return rightMost-leftMost+1 <= 1 ? 0 : rightMost-leftMost+1;
}