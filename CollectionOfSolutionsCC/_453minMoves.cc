#include "Solution.h"

int Leetcode401_500::Soltuion::minMoves(vector<int>& nums)
{
    // 很 sao 的一道题，正难则反的思路
    // 既然正向思考会需要变动很多数 (n-1 个)，那么我们不如反过来思考
    // 每次操作会使 n-1 个元素增加，这句话和 "每次操作会使剩下那一个元素减少1" 从作用上完全是等价的
    // 如果我们考虑相对值，而不是绝对值，就会发现这个道理
    // 所以，题目相当于在问：每次减少一个值1，最少需要减少多少次才能使数组所有元素相等？
    // 那么思路就非常简单了
    // 首先找出数组中最小的元素，这是最后的相等线
    int smallest = *min_element(nums.begin(), nums.end());
    int res = 0;
    // 之后线形扫描整个数组，找出每个元素到 smallest 到距离，累加求和即可
    for(const auto& num : nums)
    {
        res += num-smallest;
    } 
    return res;
}