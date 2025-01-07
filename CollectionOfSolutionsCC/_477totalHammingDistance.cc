#include "Solution.h"

int Leetcode401_500::Soltuion::totalHammingDistance(vector<int>& nums)
{
    // 简单的模拟题，不涉及什么算法或者数据结构
    // 按位来考虑：假设这一组数某一个二进制位上 1 的个数为 m 个，那么 0 的个数就是 nums.size()-m 个
    // 稍微推理一下，不难知道：对应位上的汉明距离总和就是 m * (nums.size()-m)
    // 我们对这些 32 位二进制数的每一个位进行一轮遍历求解即可累加得到答案
    // 存储最终结果
    int res = 0, n = nums.size();
    for(int i = 0; i < 31; ++i)
    {
        // 遍历每一个数的对应位，找出 1 的个数和 0 的个数
        int countOne = 0;
        for(const int& num : nums)
        {
            countOne += (num >> i) & 1;
        }
        res += countOne * (n-countOne);
    }
    return res;
}