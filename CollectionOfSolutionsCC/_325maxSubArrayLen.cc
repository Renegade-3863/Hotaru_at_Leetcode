#include "Solution.h"

int Leetcode301_400::Solution::maxSubArrayLen(vector<int>& nums, int k)
{
    // 本题有些熟悉滑动窗口算法的同学们可能第一印象会是想要直接套滑动窗口的模版
    // 可是本题实际上用不了滑动窗口算法，后面我们会讲为什么
    // 我们先换用前缀和方案来实现
    // 这里使用哈希表的原因在于，我们需要高效查找某个前缀和是否出现过，以及出现过的话，第一次出现的位置在哪里(之所以要记录第一次出现的位置，是因为我们要找的是最长的连续子数组)
    unordered_map<long long, int> preSum;
    int n = nums.size();
    // 累加一个前缀和 pre
    long long pre = 0;
    // 记录全局的答案
    preSum[0] = -1;
    int res = 0;
    for(int i = 0; i < n; ++i)
    {
        pre += nums[i];
        // 找前面的前缀中是否出现过 pre-k (原表达式为 pre-sum == k -> sum == pre-k)
        if(preSum.find(pre-k) != preSum.end())
        {   
            res = max(res, i-preSum[pre-k]);
        }   
        // 如果这个前缀和没记录过，那么我们记录一下
        if(preSum.find(pre) == preSum.end())
        {
            // 记录对应的下标
            preSum[pre] = i; 
        }
    }
    // 返回全局结果即可
    return res;
}

// 我们来详细解释一下本题不能用滑动窗口的本质原因
// 回顾一下我们以前写过的滑动窗口题
// 我们给出的定义一般都是：以某个元素为结尾的最长/最短连续窗口具有 xxx 性质
// 而本题我们能明确这样的性质吗？
// 假设我们不断往右挪动窗口右界，直到窗口内的元素值大于了 k
// 之后我们就可以明确此时窗口左边界左边没有更小的左边界可以构成答案了吗？
// 显然不能，因为我们的循环理论上只能明确以某个下下标为右边界的情况下的最长窗口，而这与左边界是不等价的