#include "Solution.h"

int Leetcode601_700::Soltuion::findKthNumber(int m, int n, int k)
{
    // 又是一道 K 路归并类问题
    // 不用管什么所谓的 "乘法表" 说辞
    // 这就是 n 个有序数组，从中找出第 k 小的数的问题
    // 这种题一般有两种解法：
    // 优先队列法和二分解法
    // 优先队列法很好理解，所以这道题我们尝试一下二分解法
    // 首先，明确一件事：
    // 这道题和传统的 K 路归并问题的区别在于
    // 这道题是知道 n 个有序数组中元素的最大值的
    // 换句话说，取值范围为 [1, m*n]
    // 我们可以对这个取值区间进行按值二分
    // 具体来说：
    // 最后的答案值一定在 [1, m*n] 这个范围中
    // 所以我们可以每次取可能有答案值的区间中点 mid
    // 检查这个 m*n 矩阵中小于 mid 的元素的总个数，假设结果为 cnt1
    // 以及这个 m*n 矩阵中等于 mid 的元素的总个数，假设结果为 cnt2
    // 那么如果对于某个 mid 值，cnt1 < k，并且 cnt1+cnt2 >= k
    // 那么第 k 个值就一定是 mid 了
    // 其它情况：
    // 也就是：cnt1 >= k || cnt1+cnt2 < k
    // 1. 如果 cnt1 >= k (注意，此时有 cnt1+cnt2 >= k，因为 cnt2 一定为正，所以 cnt1 >= k => cnt1+cnt2 >= k)
    // 那么我们可以肯定 mid 以及所有大于 mid 的元素都一定不是结果了
    // right 指针放到 mid-1 即可
    // 2. 如果 cnt1+cnt2 < k (注意：此时有 cnt1 < k，因为 cnt2 一定为正，所以 cnt1+cnt2 < k => cnt1 < k)
    // 此时我们知道 mid 以及左侧所有值都不可能是结果了
    // 把 left 放到 mid+1 即可
    // 划定二分的初始区间
    int left = 1, right = m*n, res = -1;
    // 注意：如果 left == right 了，我们就找到结果了，可以结束循环
    while(left <= right)
    {
        int mid = ((right-left)>>1)+left;
        // 检查每一行中不小于 mid 的元素个数，累加到 cnt1 中
        // 再检查每一行中等于 mid 到元素个数，累加到 cnt2 中
        // 找 cnt1 也可以用一个二分过程
        // 遍历每一行
        int cnt1 = 0, cnt2 = 0;
        for(int i = 1; i <= m; ++i)
        {
            // [l, r] 为可能存在结果的区间
            // 这里的结果是 "最大的小于 mid 的元素的序号"
            int l = 1, r = n, c1 = 0, c2 = 0;
            while(l <= r)
            {
                int m = ((r-l)>>1)+l;
                // 检查 i*m 和 mid 的关系
                // 如果 i*m 不小于 mid，那么我们知道 [m, r] 中不存在答案，r 放到 m-1 即可
                if(i*m >= mid)
                {
                    r = m-1;
                }
                else
                {
                    l = m+1;
                    // m 可能是答案的候选人
                    c1 = m;
                }
            }
            cnt1 += c1;
            l = 1; r = n;
            while(l <= r)
            {
                int m = ((r-l)>>1)+l;
                if(i*m > mid)
                {
                    r = m-1;
                }
                else
                {
                    l = m+1;
                    c2 = m;
                }
            }
            cnt2 += c2;
        }
        if(cnt1 < k && cnt2 >= k)
        {
            res = mid;
            break;
        }
        else if(cnt1 >= k)
        {
            right = mid-1;
        }
        else
        {
            left = mid+1;
        }
    }
    return res;
}