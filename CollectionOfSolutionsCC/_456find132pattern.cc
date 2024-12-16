#include "Solution.h"

// 最朴素的 O(n^3) 的解法，可以预见的 TLE
bool Leetcode401_500::Soltuion::find132pattern(vector<int>& nums)
{
    // 还是从最朴素的方法入手
    // 枚举三元组开头位置的元素下标
    int n = nums.size();
    for(int i = 0; i < n-2; ++i)
    {
        // 之后遍历剩下位置上的元素，选择每一个大于 nums[i] 的元素进行下一轮循环
        for(int j = i+1; j < n-1; ++j)
        {
            if(nums[j] > nums[i])
            {
                for(int k = j+1; k < n; ++k)
                {
                    if(nums[k] > nums[i] && nums[k] < nums[j])
                    {
                        return true;
                    }
                }
            }
        }
    }
    // 没有找到可行解，返回 false
    return false;
}

// 考虑如何进行优化
// 我们尝试换一种方式思考
// 132 规律，我们可以先确认中间的 3，之后再枚举两端的 1 和 2
bool find132pattern(vector<int>& nums)
{
    // 基本思路为，枚举中间的 3 的值
    int n = nums.size();
    for(int i = 1; i < n-1; ++i)
    {
        // 之后根据一个固定的 3 值，先枚举出这个固定的 3 值左边的所有元素中最小的那一个，再枚举出这个固定的 3 值右边所有元素中最大的那一个，如果这个组合满足要求，那么就可以返回 true 了，如果连这个组合都不满足，那么这个 3 值就不可能可行了
        int num1 = INT_MAX;
        for(int j = 0; j < i; ++j)
        {
            if(nums[j] < nums[i])
            {
                num1 = min(num1, nums[j]);
            }
        }
        int num2 = INT_MIN;
        for(int k = n-1; k > i; --k)
        {
            if(nums[k] > num1 && nums[k] < nums[i])
            {
                num2 = max(num2, nums[k]);
            }
        }
        // 结束后筛查一下关系是否正确
        if(num1 < nums[i] && num1 < num2 && num2 < nums[i])
        {
            return true;
        }
    }
    // 遍历完成，没有找到可行解，返回 false
    return false;
}

// 上面的方法依然是 O(n^2) 的，所以没法通过，依然 TLE，我们需要考虑进一步优化
// 重新审视我们枚举 3 的做法
// 其实会发现下面的逻辑：
// 我们不用真的对每一个 3 都遍历左右两侧所有的元素，而可以用两个有序集合动态记录两部分的所有数据，在需要的时候使用对数级别的复杂度进行查找 (类似二分)
// 而又注意到，由于 1 这个数本身就是三元组中最小的那一个，所以我们实际上只需要用一个有序集合维护 3 右侧的元素，对于它左侧的元素，我们维护一个最小值变量来记录即可
bool find132pattern(vector<int>& nums)
{
    int n = nums.size();
    if(n < 3)
    {
        return false;
    }
    // 用于记录枚举的 3 右侧的所有元素的有序集合，multiset 允许出现重复元素，符合本题的实际要求，可以提供对数级别的查找效率
    multiset<int> st;
    // 进行元素的添加
    for(int i = 2; i < n; ++i)
    {
        st.insert(nums[i]);
    }
    // 初始情况下，num1 的最小值就是 nums[0] 本身
    int num1 = nums[0];
    // 之后就是遍历 3 的过程了
    for(int i = 1; i < n-1; ++i)
    {
        // 如果 num1 < nums[i]，我们才需要进行下面的检查
        if(num1 < nums[i])
        {
            // 提取 st 中最小(第一个)的大于 num1 的元素
            // 简单记录一个小细节问题，涉及到 STL 本身的特性
            // 如果使用下面的函数：
            // std::upper_bound(st.begin(), st.end(), num1)
            // 那么我们是在用一个通用的 (generic) 函数对一个 multiset 集合进行搜索，这样的效率比内置于 multiset 类内部的 upper_bound(针对 multiset 本身的特性进行了优化)
            // 效率是有差距的，本题使用上面的调用就会 TLE，而下面的这个不会 (不确定是不是 Leetcode 判题器本身的问题。。。)
            auto it = st.upper_bound(num1);
            // 如果这个元素存在，我们进一步判断它和 nums[i] 的关系
            if(it != st.end() && *it < nums[i])
            {
                // 找到了，返回 true 即可
                return true;
            }
        }
        // 维护 num1 
        num1 = min(num1, nums[i]);
        // 还需要从右侧的有序集合中删掉 i+1 位置上的这个元素
        st.erase(st.find(nums[i+1]));
    }
    // 没有找到合法解，返回 false
    return false;
}

// 学一下更优的 O(n) 解法
// 本质上是单调栈解法
bool find132pattern(vector<int>& nums)
{
    int n = nums.size();
    // 单调栈，维护 nums[i] 左侧
    stack<int> stk;
    // 一个前缀数组，记录一组前缀最小值，意为：nums[i] 左侧的最小值
    // 而最开始的时候，nums[0] 左侧没有任何值，所以我们初始化的时候填入一个 INT_MAX，代表不合法的值
    vector<int> pmin{INT_MAX};
    for(int i = 0; i < n; ++i)
    {
        // 从 stk 中弹出所有在 i 左侧的不大于 nums[i] 的元素下标
        // 提问：为什么这些元素可以被弹出(换句话说：不再被考虑)？
        // 因为我们要尝试把 nums[i] 作为 2 值考虑
        // 那么处于第一个大于 nums[i] 的元素和 nums[i] 之间的这些不大于 nums[i] 的元素下标，
        // 都不如用这个第一个大于 nums[i] 的元素更适合作为 3 值
        // 并且这个性质对于 nums[i] 右侧的所有还未检查的可能 2 值都是一样的
        // 具体地：如果 nums[i] 右侧的新元素是等于 nums[i] 的，那么很明显不用考了这些元素
        // 如果 nums[i] 右侧的新元素是大于 nums[i] 的，那么同样不可能利用原来被丢弃的这些元素作为 3 值
        // 最后一个，可能是最难理解的情况，如果 nums[i] 右侧的新元素是小于 nums[i] 的
        // 那么我们有可能在前面丢弃了一些本来可以作为 nums[i] 右侧这个新 2 值的 3 值的值
        // 这会有问题吗？
        // 别忘了一点：此时，nums[i] 这个位置的元素就能作为新元素的 3 值
        // 那么它左边之前被丢弃的，那些不大于它的元素很明显就没必要考虑了，画一画图就能明白
        // 综上，我们就不用费力再保留它们了
        // 循环结束的时候，如果存在，这个下标就是 stk.top()
        while(!stk.empty() && nums[stk.top()] <= nums[i])
        {
            stk.pop();
        }
        // 为了确保形成一个 132 结构，我们还需要在 nums[stk.top()] 左侧查找最小的那个值
        // 这通过一个前缀数组很容易实现
        if(!stk.empty() && pmin[stk.top()] < nums[i])
        {
            return true;
        }
        stk.push(i);
        // 递推地帮助 nums[i+1] 记录前缀最小值
        pmin.push_back(min(pmin.back(), nums[i]));
    }
    return false;
}