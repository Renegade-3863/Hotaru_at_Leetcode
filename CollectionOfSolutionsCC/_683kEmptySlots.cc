#include "Solution.h"

int Leetcode601_700::Soltuion::kEmptySlots(vector<int>& bulbs, int k)
{
    // 定义树状数组的最大范围
    // n 的取值范围为 [1, 20000]，那么我们可以定义一个最长 20009 的树状数组
    const int MAXN = 20009;
    int n = bulbs.size();
    // 实战一下树状数组算法
    // 本题可以转换成这样的表述形式：
    // 有一个长度为 n 的数组 arr，下标范围为 [1, n]
    // 初始时，整个数组中每个下标上的元素均为 0
    // 之后，遍历 bulbs 数组的时候，每次我们会把 arr 中的一个元素从 0 修改成 1
    // 题目要求我们找出这样的情况：
    // 某个时刻，arr 中区间 [i, j] (where j = i+k-1) 中恰好有 2 个 1，并且 arr[i] 也是 1
    // 而只有当我们把某个元素 (假设下标为 i) 从 0 改成 1 的时候，才有可能在区间 [i-k+1, i], [i, i+k-1] 中找到题目要求的结果
    // 那么这种类似 "区间和" 的定义形式，就恰好适合用树状数组/线段树来实现
    // 简单套一下树状数组的模版，再加上一些 question-specified 的魔改就可以了
    // 1. 定义一个树状数组，初始化为全 0
    int t[MAXN] = {0};
    // 定义一个 lowbit 函数，计算 x 的最低位 1 的位置
    function<int(int)> lowbit = [&](int x) -> int
    {
        // 挺基本的 trick。。
        return x & (-x);
    };
    // 定义一个单点修改函数
    // add (实际上这个修改函数只会 "+1")，所以不用第二个参数了
    function<void(int)> add = [&](int idx) -> void
    {
        int k = idx;
        while(k <= n)
        {
            t[k] += 1;
            k += lowbit(k);
        }
        // 单点修改完成
    };
    // 定义一个 getsum 函数，用于查询 [1, r] 的区间和
    function<int(int)> getsum = [&](int r) -> int
    {
        int res = 0, k = r;
        while(k > 0)
        {
            res += t[k];
            k -= lowbit(k);
        }
        return res;
    };
    // 定义一个 getsum1 函数，用于查询 [l, r] 的区间和
    function<int(int, int)> getsum1 = [&](int l, int r) -> int
    {
        // sum(l, r) = sum(1, r)-sum(1, l-1)
        return getsum(r)-getsum(l-1);  
    };
    // 模版写好了，剩下的就是调用了
    for(int i = 0; i < n; ++i)
    {
        // 遍历每一个 bulb
        // 先调用 add 进行单点修改
        add(bulbs[i]);
        // y, 0, 0, 0, ..., 1
        // 之后，检查我们开头提到的两个区间
        if(bulbs[i] > k+1 && getsum1(bulbs[i]-k-1, bulbs[i]) == 2 && getsum1(bulbs[i]-k-1, bulbs[i]-k-1) == 1)
        {
            // 找到了，返回结果
            return i+1;
        }
        if(bulbs[i]+k+1 <= n && getsum1(bulbs[i], bulbs[i]+k+1) == 2 && getsum1(bulbs[i]+k+1, bulbs[i]+k+1) == 1)
        {
            return i+1;
        }
        // 没找到，继续遍历即可
    }
    // 没有合条件的情况，返回 -1
    return -1;
}

// [10,1,9,3,5,7,6,4,8,2]
/*
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    1:
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 1]
    2:
    [1, ]
*/