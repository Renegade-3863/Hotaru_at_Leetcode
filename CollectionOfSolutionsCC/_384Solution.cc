#include "Solution.h"

// 经典的洗牌算法，算法课上应该都是学过的
// 具体过程也是类似递归：
// 我们先把前 (n-1) 个元素的 (n-1)! 种排列生成好，那么每一种排列对应的出现概率就是 1/(n-1)!
// 之后考虑如何通过这个结果生成前 n 个元素的随机排列
// 我们只需要考虑这个第 n 个元素插入到前面这 (n-1)! 种排列中任意一种的哪一个空隙中即可
// 因而对于每种排列，我们应该有 n 种可能的排列种数，而每种排列都不会重复，所以一共就有 n! 种排列
// 而每种排列又都是等可能的，所以它们的概率都是 1/n!
// 这样，我们就找到了最终的答案
Leetcode301_400::Solution::Solution::Solution(vector<int>& nums)
{
    this->memo = nums;
    this->res = nums;
}

vector<int> Leetcode301_400::Solution::Solution::reset()
{
    this->res = this->memo;
    return this->res;
}

vector<int> Leetcode301_400::Solution::Solution::shuffle()
{
    // 根据上面的方法写代码即可
    for(int i = 1; i <= n; ++i)
    {
        swap(this->res[i-1], this->res[rand()%i]);
    }
    return this->res;
}