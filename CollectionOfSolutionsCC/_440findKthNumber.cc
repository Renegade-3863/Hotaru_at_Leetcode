#include "Solution.h"

// 暴力回溯，直接被好几十万的测试数据干 TLE 了。。。
int Leetcode401_500::Solution::findKthNumber(int n, int k)
{
    // 类似一种变形的回溯问题
    // 我们画出来一棵回溯树就行
    // 按位一位一位构造最后的结果
    // cur 代表现在填入的是第几位数
    // val 代表当前构造出来的数
    // 虽然题目限定了 1 <= k <= n <= 10^9，但是这里还是应该进行边界检查
    if(k <= 0)
    {
        return 0;
    }
    int val = 0;
    int cnt = 0, res = -1;
    bool found = false;
    function<void(int)> backtrack = [&]() 
    {
        // 递归结束条件：
        // val > n
        // 此时我们不能进行添加，直接返回
        // 否则，我们把当前的 val 值添加到结果集中
        if(val > n)
        {
            // 因为每次进入递归都会假设 cnt 递增了1
            // 这里我们需要删掉这次递增，因为是无效的
            --cnt;
            return;
        }
        if(cnt == k)
        {
            res = val;
            found = true;
            return;
        }
        // 注意到，我们不能包含 '0' 这个数，所以我们假定 cur 是大于 1 的即可
        // 这样写代码的时候统一性更好
        // 对于当前位的数，我们可以尝试 0-9 的所有数
        for(int i = 0; i <= 9 && !found; ++i)
        {
            // 尝试添加一个数
            val = val*10+i;
            // 每生成一个新数，cnt 就加一
            ++cnt;
            // 深入一层
            backtrack();
            // 回溯
            val /= 10;
        }
    };
    // 我们从所有一位数开始回溯算法
    for(int start = 1; start <= 9 && start <= n && !found; ++start)
    {
        val = start;
        ++cnt;
        backtrack();
    }
    return res;
}

// 之后就是尝试优化一些不必要的检查
// 实际上，我们可以通过一些手段，明确出第 k 个数在这棵树中位于哪里
// 我们可以观察出，这棵树有这样的性质：
// 它一定只有最后一层上会出现不满的情况
// 那么我们就可以利用这个性质来加速搜索
// 具体思路为：
// 对于每一层的每一个结点
// 我们首先判断这个结点为根代表的子树中有多少个结点
// 假设有 cnt(i) 个结点，i 为这个结点本身的值
// 那么由于我们要找的是第 k 个元素，那么很明显
// 1. 如果 cnt(i) >= (k-i)，那么说明我们要找的数就在 i 的子树中
// 2. 如果 cnt(i) < (k-i)，那么我们可以跳过这棵树，第 k 个值一定不在这棵树中
int findKthNumber(int n, int k)
{
    function<int(int, int)> count = [&](int cur, long long n)
    {
        int cnt = 0;
        long long first = cur;
        long long last = cur;
        while(first <= n)
        {
            cnt += min(last, n) - first + 1;
            first = first * 10;
            last = last * 10 + 9;
        }
        return cnt;
    };
    int cur = 1;
    k -= 1;
    while(k > 0)
    {
        int cnt = count(cur, n);
        if(cnt <= k)
        {
            // 丢弃当前这棵子树，往后平行挪动一位
            k -= cnt;
            ++cur;
        }
        else
        {
            // 一定在当前子树中，我们向下深入一层，检查新的一层
            cur = cur*10;
            k -= 1;
        }
    }
    return cur;
}