#include "Solution.h"

bool Leetcode201_300::Solution::containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff)
{
    // 困难题，我们先考虑最暴力的方案
    // 对于每个位置上的元素，我们可以向右扩散 indexDiff 个元素，直到检查到合法的元素，我们就可以返回结果了
    // 不过这样显然需要 O(n*indexDiff) 的时间复杂度，相当于近似 O(n^2)，是效率非常低下的，我们需要考虑进行优化
    // 不难看出主要的优化点在于 indexDiff 这个位置上
    // 我们可以考虑使用一些高效的查找数据结构，利用它们找出 nums[i] 到 nums[i+indexDiff] 之间的所有值中小于等于 nums[i] 的最大值和大于等于 nums[i] 的最小值
    // O(k) 优化？最应该想到的就是 O(logk) 的下一级
    // 这就是类似 BST 的查找结构了
    // 具体的，在 C++ 中存在 set 这种基于红黑树的高效数据存取结构，可以满足我们的高效存储和数据检出的要求
    set<long> st;
    for(int i = 0; i < nums.size(); ++i)
    {
        // 找出指向 (有序集合，注意，只有有序集合 lower_bound 函数才有效！) st 中第一个不小于 nums[i]-valueDiff 的元素的位置
        auto lb = st.lower_bound((long)nums[i]-valueDiff);
        // 如果这个迭代器不指向 st.end() 位置，也就是说，它是指向一个有效元素的迭代器，并且这个指向的元素值本身是不大于 nums[i]+valueDiff 的，那么我们就可以说已经找到了答案
        if(lb != st.end() && *lb <= (long)nums[i]+valueDiff)
        {
            return true;
        }
        // 注意，还需要把这个元素添加到有序集合中
        st.insert(nums[i]);
        // 如果我们在添加当前元素之前，已经添加了 indexDiff 个元素，那么在添加了新的元素后，我们还需要删掉前面窗口开头的元素
        if(i >= indexDiff)
        {
            st.erase(nums[i-indexDiff]);
        }
    }
    // 走完了一轮循环，我们就可以直接返回 false 了，因为在循环中没有找到合法解
    return false;
}