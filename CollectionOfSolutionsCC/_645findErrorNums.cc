#include "Solution.h"

vector<int> Leetcode601_700::Soltuion::findErrorNums(vector<int>& nums)
{
    // 简单题，简单做，我们可以直接对 nums 求和
    // 之后再遍历过程中找出那个出现了两次的值，并把它取出来，按照拿到的差值就能推算出原值
    int n = nums.size(), sum = 0, rep = -1;
    // 可以用哈希表来记录哪些值出现过一次了
    unordered_set<int> memo;
    for(int i = 0; i < n; ++i)
    {
        sum += nums[i];
        if(memo.count(nums[i]))
        {
            // 这个条件发生了，说明 nums[i] 这个值一定是重复的那个，记录到 rep 中
            rep = nums[i];
        }
        memo.insert(nums[i]);
    }
    // 一些简单数学运算
    return {rep, (1+n)*n/2-(sum-rep)};
}

// 简单优化空间复杂度
// 上面用哈希表检查重复的做法属实有些曲线救国
// 我们可以利用原地哈希的做法来优化空间复杂度
vector<int> findErrorNums(vector<int>& nums)
{
    int n = nums.size(), sum = 0, rep = -1;
    for(int i = 0; i < n; ++i)
    {
        // 我们尝试把 nums[i] 放到它应该在的地方
        while(nums[i] != i+1)
        {
            // 检查 nums[i]-1 这个下标上是否已经有重复的元素了，没有，就把 nums[i] 和 nums[nums[i]-1] 进行交换
            // 否则，nums[i] 就是那个重复的元素
            if(nums[nums[i]-1] == nums[i])
            {
                rep = nums[i];
                // 别忘了退出循环，不然会死循环。。
                break;
            }
            // 没有重复，我们可以交换
            swap(nums[i], nums[nums[i]-1]);
        }
    }
    // 但是注意，由于上面的流程会修改 nums 元素的位置，为了避免重复计算同一个元素导致 sum 结果错误，我们不得不分开执行这两步
    for(int i = 0; i < n; ++i)
    {
        sum += nums[i];
    }
    // 一些简单数学运算
    return {rep, (1+n)*n/2-(sum-rep)};
}