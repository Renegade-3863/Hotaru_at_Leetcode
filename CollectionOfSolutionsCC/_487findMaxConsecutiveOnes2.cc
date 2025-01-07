#include "Solution.h"

// 注意：下面的解决方案也可以应对进阶提问，因为没有任何 O(n) 级别的存储空间使用
int Leetcode401_500::Soltuion::findMaxConsecutiveOnes2(vector<int>& nums)
{
    // 一个指针模拟题，没有太多的技巧可言，不过如果不是最多可以翻转一个0，那么可能我们还需要引入另一个变量记录当前连续1序列中出现了多少个零
    // 我们记录一个指针，这个指针指向当前找到的连续 1 序列中最左侧的 0 的下标，因为最多一个 0，所以我们不用额外用一个变量记录 0 的个数
    // 之后还需要两个指针，分别指向当前连续 1 序列的左右边界下标
    // -1 代表这个指针还没记录任何 0 的下标
    int n = nums.size();
    int firstZero = -1, left = -1;
    // res 记录的是当前已知的答案
    int res = 0;
    // right 指针用于遍历
    for(int right = 0; right < n; ++right)
    {
        // 需要更新的情况是：nums[right] == 0 && firstZero != -1 && firstZero < right
        if(nums[right] == 0 && firstZero != -1)
        {
            // 更新 left，注意：left+1 才是连续 1 序列的第一个值
            left = firstZero;
            // 更新 firstZero 为 right
            firstZero = right;
        }
        else if(nums[right] == 0)
        {
            // 实际上，这个条件中只可能是 firstZero == -1
            // 我们只把 firstZero 设置为 right 即可
            firstZero = right;
        }
        res = max(res, right-left);
    }
    return res;
}