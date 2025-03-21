#include "Solution.h"

vector<int> Leetcode601_700::Soltuion::constructArray(int n, int k)
{
    // 不知道怎么做的时候，找几个例子看下，有没有切入点：
    // 首先，对于长度为 n，k 值为 1 的情况
    // 我们直接返回 [1, n] 原数组即可
    // 之后，如果 k 值为 2
    // 那么我们可以考虑把 n-1 和 2 之间的元素反序，形成下面的序列：
    // [1, n-1, n-2, n-3, ..., 3, 2]
    // 拿到的列表就是：
    // [n-2, 1, 1, 1, ..., 1]
    // 捏合后为：
    // [n-2, 1]，满足 k 为 2 的要求
    // 之后，如果 k 值为 3
    // 我们可以考虑把 n-2 到 2 之间的元素再反序，形成：
    // [1, n-1, 2, 3, 4, ..., n-2]
    // 拿到的列表就是：
    // [n-2, n-3, 1, 1, ..., 1]
    // 捏合后为：
    // [n-2, n-3, 1]，满足 k 为 3 的要求
    // 之后，如果 k 值为 4
    // 我们进一步把 3 到 n-2 之间的元素反序，形成：
    // [1, n-1, 2, n-2, n-3, ..., 3]
    // 得到列表：
    // [n-2, n-3, n-4, 1, 1, ..., 1]
    // 捏合后：
    // [n-2, n-3, n-4, 1]，满足 k 值的要求
    // 经过上面的尝试，我们就基本明确了最后的规律：
    // 对于任何一个已知的 k
    // 我们都可以先按交错排列的方式计算前 k 个元素
    // 这前 k 个元素按照一 "剩余最小"，一 "剩余最大" 的方式交错排列
    // 之后，后半 n-k 个元素，我们根据 k 的奇偶性，来决定剩下的元素是要正序排列还是逆序排列
    // 两个指针，标记可用数据的左右区间
    int left = 1, right = n;
    vector<int> res(n);
    for(int j = 0; j < k; ++j)
    {
        // 先填写前 k 个元素
        // 奇数下标填写一个大数，偶数填写一个小数
        if(j % 2)
        {
            res[j] = right--;
        }
        else
        {
            res[j] = left++;
        }
    }
    // 后半根据 k 的奇偶性，决定 [left, right] 中的元素是要正序填入，还是逆序填入
    if(k%2)
    {
        // 奇数，正序填入
        for(int j = k; j < n; ++j)
        {
            res[j] = left++;
        }
    }
    else
    {
        // 偶数，逆序填入
        for(int j = k; j < n; ++j)
        {
            res[j] = right--;
        }
    }
    return res;
}