#include "Solution.h"

int Leetcode301_400::Solution::maxSumSubmatrix(vector<vector<int>>& matrix, int k)
{
    // 本题是带限制的面试题 17.24，可以结合两道题一起来看
    // 我们可以使用类似该题的遍历方法，压缩二维到一维再应用一维前缀和算法
    // 我们用一个 sums 数组，记录限定好的两行之间夹逼出来的列的和
    int m = matrix.size(), n = matrix[0].size();
    // 全局的结果值
    int maximum = INT_MIN;
    // 枚举夹逼用的两行的行标
    for(int i = 0; i < m; ++i)
    {
        // 一个数组用于存储每一列上对应行之间的元素和
        vector<int> sums(n, 0);
        for(int j = i; j < m; ++j)
        {
            // 首先，累计 sums 数组中的每一列元素和
            for(int k = 0; k < n; ++k)
            {
                sums[k] += matrix[j][k];
            }
            // 之后，考虑如何使用我们刚刚拿到的这组数据
            // 此时的问题就被转换成了：如何在一个一维数组上，找出和不超过 k 的最大子数组？
            // 注意，这个数组是可能含有负数的，所以我们不能使用枚举一侧端点+二分的简单方法，需要维护一个有序的集合关系
            // 那么，不难想到，我们应该维护一个有序集合，保存枚举到的右端点左侧所有前缀和值的一个有序序列
            // 之后，从左边这个有序序列中找出距离当前枚举的这个右边界前缀和值最远的那一个值即可
            // 这个问题就是可以用二分来求解的了
            // 初始化这个有序集合
            set<int> st;
            // 最开始填入一个 0，代表存在一个和值为 0 的前缀，就是没有任何值的前缀
            st.insert(0);
            int preSum = 0;
            for(int right = 0; right < n; ++right)
            {
                // 先更新前缀和
                preSum += sums[right];
                // 在已有的前缀和有序集合中，寻找
                // 满足 pre[right]-pre[i] <= k 的最小的那个 pre[i]
                // lower_bound 用于在一个有序的区间内寻找第一个不小于给定元素参数的值
                auto b = st.lower_bound(preSum-k);
                // 如果存在这样的最小元素，我们更新全局的最大值即可
                if(b != st.end())
                {
                    maximum = max(maximum, preSum-*b);
                }
                st.insert(preSum);
            }
        }
    }
    return maximum;
}