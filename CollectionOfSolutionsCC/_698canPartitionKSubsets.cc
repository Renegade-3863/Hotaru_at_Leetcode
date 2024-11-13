#include "Solution.h"

// 剪枝版本的回溯是本题最容易理解的方法，我们把详细的解释放到代码里
bool Leetcode601_700::Solution::canPartitionKSubsets(vector<int>& nums, int k)
{
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if(sum%k)
    {
        return false;
    }
    vector<int> sums(k, 0);
    // 8 个 32 位的整型数足够表示200位二进制数
    int used = 0;
    bool found = false;
    // 对 nums 数组降序排列，有利于我们后续剪枝
    sort(nums.begin(), nums.end(), [&](const int& a, const int& b) {
        return a > b;
    });
    int n = nums.size();
    function<void(int)> dfs = [&](int idx)
    {
        // 基本情况
        // idx == n
        // 此时说明所有元素都已经被添加完毕了，我们只需要检查是不是所有元素的和都是 sum/2 即可
        if(idx == n)
        {
            found = true;
            return;
        }
        // 其它情况下，对于当前元素，我们考虑分别尝试把它放到两个不同的集合中
        // 首先尝试放到第一个集合中
        // 如果这个元素已经用过了，那么我们不需要进一步深入递归，跳过这个元素即可
        if(used & (1<<idx))
        {
            return;
        }
        // 同时，因为我们按照降序进行排列，如果当前元素和前一个相同，那么我们也没必要进一步深入了，因为这个元素前面已经检查过了，没找到合法解
        // 否则，我们可以深入递归
        for(int j = 0; j < k; ++j)
        {
            // 剪枝：如果这个元素已经被尝试填入到了某一种特定和值的集合中，那么我们就可以直接跳过了
            if(j > 0 && sums[j] == sums[j-1])
            {
                continue;
            }
            if(sums[j]+nums[idx] > sum/k)
            {
                // 如果这个和已经大于了 sum/2 
                // 那么不可能有可行解，我们跳过这次尝试即可
                continue;
            }
            // 否则，我们可以尝试当前这个元素
            sums[j] += nums[idx];
            // 记录已经使用过
            used = (1<<idx) | used;
            // 递归
            dfs(idx+1);
            // 检查是否已经找到了结果
            if(found)
            {
                return;
            }
            // 否则，没找到，我们回溯
            used = (1<<idx) ^ used;
            sums[j] -= nums[idx];
        }
    };
    // 调用函数即可
    dfs(0);
    return found;
}