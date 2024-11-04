#include "Solution.h"

int Leetcode301_400::Solution::countRangeSum(vector<int>& nums, int lower, int upper)
{
// 在这里，我们需要用到在 .h 文件里面定义的第二种线段树结构
    // 我们需要一个多大的结点？
    // 应该是需要一个至少能包含所有我们会查询到的区间大小的结点，不过这样我们需要预处理整个前缀和数组
    long long preSum = 0;
    vector<long long> preSums = {0};
    int n = nums.size();
    for(int i = 0; i < n; ++i)
    {
        preSum += nums[i];
        preSums.push_back(preSum);
    }
    // 处理完前缀和数组后，我们需要知道最大和最小可能查询到的边界值
    long long lowerBound = LLONG_MAX, upperBound = LLONG_MIN;
    for(long long preSum : preSums)
    {
        lowerBound = min({lowerBound, preSum, preSum-lower, preSum-upper});
        upperBound = max({upperBound, preSum, preSum-lower, preSum-upper});
    } 
    // 之后根据上面求得的数据初始化根结点
    SegNode2* root = new SegNode2(lowerBound, upperBound);
    // 之后按前缀和的逻辑进行循环遍历即可
    int res = 0;
    for(long long preSum : preSums)
    {
        // 累加答案
        // cout << preSum-lower << ", " << preSum-upper << endl;
        // lower <= preSum-x <= upper
        res += root->query(preSum-upper, preSum-lower);
        root->update(preSum, preSum, 1);
    }
    return res;
}