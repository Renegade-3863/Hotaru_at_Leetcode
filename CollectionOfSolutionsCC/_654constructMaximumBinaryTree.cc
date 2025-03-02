#include "Solution.h"

Leetcode601_700::TreeNode* Leetcode601_700::Soltuion::constructMaximumBinaryTree(vector<int>& nums)
{
    // 二叉树问题基本上都可以从 DFS 的角度入手思考
    // 本题自然可以用最简单粗暴的 "递归+遍历找最大值" 的方法
    // 不过 O(n^2) 的复杂度显然并不差强人意
    // 所以我们需要考虑如何进行优化
    // 思考这样的问题：
    // 首先，如果我们想对 nums[i] 这个元素进行构造
    // 那么它的左孩子就是 nums[i] 左侧所有元素中那个最大的，小于它的元素
    // 而它的右孩子就是 nums[i] 右侧所有元素中那个最大的，小于它的元素
    // 那么我们似乎可以通过类似单调栈的方式来处理这个问题：
    // 维护一个单调递减的栈：
    // 检查 nums[i] 和当前栈顶的元素
    // 如果 nums[i] 小于栈顶元素
    // 那么我们知道 nums[i] 可能是这个栈顶元素的右子结点
    // 从构造顺序上看，这个栈顶的更大的元素，一定会在 nums[i] 的上层被构建
    // 至于最后 nums[i] 是不是这个栈顶元素的右子结点
    // 我们暂时还没法确定
    // 因为我们不知道 nums[i] 是不是这个栈顶元素右侧，到第一个比栈顶元素大的区间中最大的那个值
    // 所以我们暂时保留这个子结点，以备后续检查
    // 而如果 nums[i] 大于栈顶元素
    // 那么我们也可以假定：栈顶的这个元素就是 nums[i] 的左孩子
    // 但是我们还不能完全确定它就是最后 nums[i] 的左孩子
    // 不过出现这种情况，有件事我们是可以确定的：
    // 栈顶的这个元素的右孩子一定确定了
    // 因为 nums[i] 更右侧的所有元素都被 nums[i] 这个比它值更大，因而在上层的结点给隔断了
    // 在这种情况下，我们就没必要在单调栈中继续保留这个栈顶元素了
    // 而在我们循环，直到栈顶元素变成比 nums[i] 大的元素，或者栈直接空了的时候，nums[i] 的左孩子也就最终确定了
    // 同样的道理，nums[i] 左侧第一个比它大的元素，就是那个更上层的，隔断了 nums[i] 和这个更大元素左侧区间的值
    // 经过上面的分析，我们就基本可以理解这道题简化遍历流程的单调递减栈的思路了
    // 不过还是要吐槽一句，这道题要是没做过，面试现场想单调栈解法，确实有点不当人了。。
    // 创建一个单调递减栈
    stack<int> stk;
    // 记录所有构造过的结点，不论它是否完整
    unordered_map<int, TreeNode*> mapping;
    TreeNode* root = nullptr;
    int maximum = INT_MIN;
    for(const auto& num : nums)
    {
        mapping[num] = new TreeNode();
        if(num > maximum)
        {
            root = mapping[num];
            maximum = num;
        }
        // 检查 num 和 stk.top() 的关系
        // 1. 如果 !stk.empty() && stk.top() < num
        while(!stk.empty() && stk.top() < num)
        {
            // 那么我们假定 stk.top() 这个值就是 num 的左孩子
            // 题目限定了 num 不会重复，所以每个值只会对应唯一一个树结点
            // 并把 stk.top() 弹出栈
            mapping[num]->left = mapping[stk.top()];
            stk.pop();
        }
        // 2. 此时 stk.empty() || stk.top() > num
        // 那么我们可以假定 num 是 stk.top() 的右孩子
        // 或者，如果 stk.empty()，那么 num 这个结点左上就没有结点了
        if(!stk.empty())
        {
            mapping[stk.top()]->right = mapping[num];
        }
        stk.push(num);
    }
    return root;
}