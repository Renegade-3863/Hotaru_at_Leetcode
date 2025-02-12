#include "Solution.h"

int Leetcode501_600::Soltuion::arrayPairSum(vector<int>& nums)
{
    // 简单的贪心类问题
    // 我们考虑一下题目的要求
    // 题目需要我们输出二分结果后产生的最大 min(ai, bi) 数值对和
    // 那么，从贪心的角度来讲，我们肯定是要把较小的值尽量配对，较大的值尽量配对
    // 那么排序很明显就是最合适的解决办法了
    // 这里回顾一下比较难写的基数排序算法
    // 基数排序的基本原则是：
    // 按照每个数的各个位，逐位进行排序
    // 例如：
    // [231, 2353, 1254, 2145]
    // 首先按最低位 (个位) 进行排序：
    // [2145, 1254, 2353, 231]
    // 之后按十位：
    // [1254, 2353, 2145, 231]
    // 百位：
    // [2353, 1254, 231, 2145]
    // 最后是千位：
    // [2353, 2145, 1254, 231]
    // 这样就按从高到低的逆序顺序排好了
    // 同时注意：基数排序中对每个数位进行排序的算法必须是稳定的，即：数值一样的位，排序前后保持原有的顺序不变
    // 否则会出现：原本按照较小位排序，在前面的数字，在更高位上被错误地排到前面的情况
    // 这个稳定的排序，就是我们常说的 "计数排序" 了
    // 我们先写一个计数排序的调用函数
    function<void(vector<int>&, int)> radixSort = [&](vector<int>& nums, int idx) -> void
    {
        // 按照 idx 位数对 nums 中的数据进行一轮重排，如果某个数不存在对应的 idx 位数，那么就把对应位视作 0 来处理
        // 我们首先把 nums 中每一个数的 idx 位数存储到一个数组中
        int n = nums.size();
        vector<int> memo(10, 0);
        // 这个数组中，下标为 i 的元素代表 nums 所有 idx 位上数为 i 的元素个数
        for(const auto& num : nums)
        {
            int rad = (num/idx)%10;
            // 累加到对应的位上去
            ++memo[rad];
        }
        for(int i = 1; i < 10; ++i)
        {
            memo[i] += memo[i-1];
        }
        // 累加完成，我们现在需要根据 memo 中的记录对原本的数进行重排
        // 反向遍历 nums 中的元素，根据每个数对应位上的元素把数值放到对应的结果数组中
        vector<int> res(n, 0);
        for(int i = n-1; i >= 0; --i)
        {
            res[memo[nums[i]/idx%10]-1] = nums[i];
            --memo[nums[i]/idx%10];
        }
        // 把结果复制回 nums 中
        copy(res.begin(), res.end(), nums.begin());
        // 结束过程
    };
    // 写完了计数排序过程，我们在外层的基数排序中调用它即可
    // 注意，基数排序并不适合那些有负数参与的数组，我们这里用最小的数 (如果存在负数，那么它一定是负数)，把整个数组归一化到非负数
    int minimum = *min_element(nums.begin(), nums.end());
    for(auto& num : nums)
    {
        num -= minimum;
    }
    // 根据最大元素，计算出最大的数位
    int maximum = *max_element(nums.begin(), nums.end());
    int mRad = 1;
    while(maximum)
    {
        ++mRad;
        maximum /= 10;
    }
    int cnt = 1;
    while(mRad--)
    {
        cnt *= 10;
    }
    for(int idx = 1; idx < cnt; idx *= 10)
    {
        radixSort(nums, idx);
    }
    // 排好了序，我们把各个奇数位上的元素求和即可
    int res = 0, n = nums.size();
    for(int i = 0; i < n; ++i)
    {
        if(i % 2 == 0)
        {
            res += nums[i];
        }
    }
    res += (n>>1)*minimum;
    return res;
}