#include "Solution.h"

bool Leetcode301_400::Solution::isPerfectSquare(int num)
{
    // 看到这个问题，应该想到要用二分算法(如果你已经刷过了三百多题，这种二分应该是能一眼看出来的了)
    // 一个数的平方根可取的范围，只能是 [1, num] 之间的数
    // 不过还有一步优化
    // 注意到 x^2 = num 这个等式
    // 我们如果把 x 换成 num/2
    // 就是 num^2/4 和 num
    // 我们不难发现 num(num-4) 在 num >= 4 的时候就一定是不小于零的了
    // 而 4 是一个完全平方数，这是我们都知道的
    // 所以我们完全可以在 num > 4 的时候，从 num/2 开始检查 num 的平方根，而不是从 num 开始
    if(num < 0)
    {
        return false;
    }
    if(num <= 4)
    {
        return num == 0 || num == 1 || num == 4;
    }
    int left = 1, right = num/2;
    while(left <= right)
    {
        int mid = ((right-left)>>1)+left;
        if(mid <= INT_MAX/mid && mid*mid < num)
        {
            left = mid+1;
        }
        else if(mid <= INT_MAX/mid && mid*mid == num)
        {
            return true;
        }
        // mid > INT_MAX/mid || mid*mid > num
        else
        {
            right = mid-1;
        }
    }
    return false;
}