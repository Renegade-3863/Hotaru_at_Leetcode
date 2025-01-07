#include "Solution.h"

vector<int> Leetcode401_500::Soltuion::nextGreaterElement(vector<int>& nums1, vector<int>& nums2)
{
    // 不要先入为主带入题解中那些上来就用单调栈的，就觉得这题本身很难
    // 我们先从最简单的暴力解法入手，看一下这道题怎么解
    // 按照题目要求，我们最简单的方法是：
    // 遍历 nums1 中每一个元素 num1，对于 num1，再从头遍历 num2 中的所有元素，把每一轮暴力遍历得出的结果存储到 res 中作为答案返回即可
    // 不说别的，先把这种 O(n^2) 的解法写出来，优化再说
    int m = nums1.size(), n = nums2.size();
    // 结果数组长度应该和 nums 1 是一样的
    vector<int> res(m, 0);
    // val 用于记录对于当前 num1，在 num2 中对应相等元素的右侧第一个更大的元素值，默认为 -1
    int val = -1;
    for(int i = 0; i < m; ++i)
    {
        // 重置 val
        val = -1;
        // j 可以反向来找
        // 遇到 num1 的时候，就把 val 中记录的值放到 res 中对应位置上
        for(int j = n-1; j >= 0; --j)
        {
            if(nums1[i] == nums2[j])
            {
                res[i] = val;
            }
            if(nums1[i] < nums2[j])
            {
                val = nums2[j];
            }
        }
    }
    return res;
}

// 暴力写法写完了，剩下的就是考虑如何进行线性优化了
// 上面的解法肯定是 O(n^2) 的，这个相信明眼人都看得出来
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2)
{
    // 不要上来就带入单调栈的思维，我们从本质上思考如何求解这道题
    // 根据我们上一题的求解顺序
    // 我们不难发现：对于后面的 i，也就是右侧的 nums1[i]，我们实际上可以获取到一些根据左侧的 nums1[i] 而知道的 nums2[j] 情报
    // 而且，题目有一个很关键的条件我们没有用到：nums1 和 nums2 中均无重复元素
    // 那么既然 nums1 中的元素没有重复，有一个比较显然的条件：
    // 如果 nums1[i] 的 "右侧更大元素" 我们已知了，那么所有在 nums2 中位于 nums1[i] 这个值左侧，且比它更小的元素的 "右侧更大元素" 其实就是 nums1[i] 了
    // 想到这里，我们不难联想到这样一个做法：把 nums1 中所有元素值和对应的索引都放到一个哈希映射中
    // 之后对于 nums2 进行某种处理即可得出 res 数组：我们甚至不用再考虑 nums1 了！
    // 如何对 nums2 进行处理呢？
    // 回到刚才对逻辑：我们可以从后向前检查 nums2，保存一个单调递减的栈 (假设名字为 stk)
    // 在往前检查 nums2[j] 的时候，我们检查这个栈中顶部的元素，这个元素是栈中最小的元素
    // 对每个 nums2[j]，重复下面流程：
    // 如果 nums2[j] > stk.top()
    // 那么有这样的事实：所有位于 nums2[j] 左侧的元素，如果它存在于 nums1 中，那么它们的 "右侧第一个更大元素" 就不可能是 nums2[j] 右侧的这个更小元素了
    // 所以我们直接弹出 stk.top() 即可
    // 注意：nums2[j] == stk.top() 根据题意，是不存在的
    // 如果 nums2[j] < stk.top()
    // 那么此时我们就可以直接把 nums2[j] 压栈了，因为不知道左侧还有没有比 nums2[j] 小的元素，但对于 nums2[j] 来说，这个 stk.top() 就是它的 res 值了
    // 单调栈解法就成型了
    // 剩下写代码就是水到渠成了
    // 初始化一个栈，供使用
    stack<int> stk;
    // 存储 nums1 中元素 - 下标的映射
    unordered_map<int, int> mapping1;
    int m = nums1.size(), n = nums2.size();
    // 答案数组
    vector<int> res(m, 0);
    // 对映射进行存储
    for(int i = 0; i < m; ++i)
    {
        mapping1[nums1[i]] = i;
    }
    // 之后就是对 nums2 的反向遍历
    for(int j = n-1; j >= 0; --j)
    {
        // 将 nums[j] 和 stk.top() 进行比较
        while(!stk.empty())
        {
            // 弹出所有不大于 nums2[j] 的栈顶元素
            if(stk.top() <= nums2[j])
            {
                stk.pop();
            }
            else
            {
                break;
            }
        }
        // 检查 stk.top() 是否还有元素，有的话，它就是 nums2[j] 的结果，在 nums1 中也存在 nums2[j] 的情况下，就存储对应的结果
        // 否则跳过它即可
        if(mapping1.count(nums2[j]))
        {
            if(!stk.empty())
            {
                res[mapping1[nums2[j]]] = stk.top();
            }
            else
            {
                res[mapping1[nums2[j]]] = -1;
            }
        }
        // 把 nums2[j] 入栈，别忘了
        stk.push(nums2[j]);
    }
    return res;
}