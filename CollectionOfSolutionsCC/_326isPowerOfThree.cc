#include "Solution.h"

bool Leetcode301_400::Solution::isPowerOfThree(int n)
{
    // 本题的数学解法可以说非常抽象了。。想了解这个 O(1) 解法的可以直接移步三叶的题解
    // 还是用最朴素的 log3(n) 级别循环来解决本题吧
    int x = 1;
    while(x <= INT_MAX/3 && x < n)
    {
        x *= 3;
    }
    return x == n;
}