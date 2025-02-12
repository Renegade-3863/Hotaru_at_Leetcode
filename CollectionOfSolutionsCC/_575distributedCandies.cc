#include "Solution.h"

int Leetcode501_600::Soltuion::distributeCandies(vector<int>& candyType)
{
    // 简单题简单做 (不过上一题是例外。。)
    // 我们只需要记录每一种糖果出现的总次数，之后根据医生允许吃的最大糖果数即可得出最终的结果
    unordered_map<int, int> cnts;
    // 记录最大可以吃的糖果种类数 (不一定能吃到)
    int count = 0;
    for(const auto& candy : candyType)
    {
        if(!cnts.count(candy))
        {
            ++count;
        }
        ++cnts[candy];
    }
    return min((int)candyType.size()/2, count);
}