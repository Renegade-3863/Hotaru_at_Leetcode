#include "Solution.h"

int Leetcode201_300::Solution::hIndex2(vector<int>& citations)
{
    // 个人认为最有个性的一道二分题目了
    // 首先，题目要求我们给出对数复杂度的解法，同时也告诉我们数组是升序的，那么几乎就是明示我们要使用二分法了
    // 那么我们便可以对整个数组进行二分
    // 考虑这样的事实：
    // h 的取值一定是在 [0, citations.size()] 中的，这一点由 h 指数的定义就可以推断出来
    // 那么很明显我们要二分的区间就是这个 [0, citations.size()]
    // 定义区间左右边界 [left, right]
    // 之后，二分答案区间，问询 citations[n-mid] 这个值
    // 提问：为什么要问询 citations[n-mid] 这个值，而不是 citations[mid]?
    // 主要原因在于：
    // citations[mid] 的意义是什么？
    // 我们会发现，没办法以有意义的方式来定义这个值
    // 它只是某个下标 mid 上论文引用的次数
    // mid 本身是答案的一个备选值，而这个备选值本身并不具备下标的含义，所以我们不能用答案值作为下标
    // 那么 citations[n-mid] 为什么就有意义了呢？
    // 原因在于：
    // n-mid 这个值有一种隐含的意义：
    // n-mid 下标右侧(包括它本身)是有 mid 个元素(论文)的
    // 此时我们如果检查这个位置上的元素和 mid 的关系：
    // 1. citations[n-mid] >= mid
    // 此时说明：n-mid 这个位置以及右侧是有至少 mid 篇论文的
    // 也就是说有至少 mid 篇论文被引用的次数是不少于 nums[n-mid] 的
    // 回顾我们对于 mid 的定义
    // mid 代表的是当前有可能成为 h 的结果的区间的中点
    // 我们要做的是检查 mid 是否有可能成为 h 的候选值
    // 此时由于 citations[n-mid] 的被引用次数都不少于 mid 次了，那么它以及它右边的 mid 个值就都不会少于 mid 次
    // 因而这个 mid 就是一个合法的 h 值，但是还不够，我们只是确定了这个值是一定合法的，但没法保证它是最大的，不过我们依然可以丢弃左半的那些更小的值，它们都不可能是最终结果了
    // 这样就构成了一对二分关系
    // 2. citations[n-mid] < mid
    // 那么我们显然可以知道，这个 mid 值不可能是 h 的备选值，因为后面最大的 mid 个元素不是都不小于 mid 的，那么显然也就不可能有至少 mid 个元素不小于 mid 了
    // 终于搞明白了二分规则，我们写代码就很简单了
    int n = citations.size();
    int left = 0, right = n;
    int res = 0;
    while(left <= right)
    {
        // 由于我们取出的 mid 值可能等于0，所以需要进行特判
        // 当 mid 等于0的时候，我们相当于在问最后一篇论文被引用的次数是否不少于1次，那么直接用 citations[n-1] 和 mid 进行比较即可
        int mid = ((right-left)>>1)+left;
        if(citations[mid > 0 ? n-mid : n-1] >= mid)
        {
            res = mid;
            left = mid+1;
        }
        else
        {
            right = mid-1;
        }
    }
    return res;
}