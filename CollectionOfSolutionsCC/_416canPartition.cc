#include "Solution.h"

// 第一版：暴力回溯，直接 TLE
bool Leetcode401_500::Solution::canPartition(vector<int>& nums)
{
    // 本题很多题解都直接给出 DP 递推式，搞得非常难以理解，如果是第一次做这道题的同学们，更可能直接就被讲懵了
    // 我们还是选择一个更简单的切入点：回溯算法
    // 在开始写代码之前，考虑这样的问题：
    // 我们要把 nums 分割成两个等和的子集，那么最后分成的两个集合的元素值和就是 sum(nums)/2 
    // 这一点是我们在开始检查之前就可以确认的
    // 首先检查这个数组的元素和是不是个偶数，如果连偶数都不是，那么我们压根不可能把它拆成两份，直接返回 false 即可
    int sum = accumulate(nums.begin(), nums.end(), 0);
    // 检查是否是一个偶数
    if(sum%2)
    {
        // 是个奇数，那么我们根本就不用检查，直接返回 false 即可
        return false;
    }
    // 否则，我们尝试使用回溯的方法进行暴搜
    // 存储两个数组，用于记录当前的递归状态
    // 每个数组的第一个元素用于记录当前数组中的元素总和
    vector<vector<int>> subsets(2, vector<int>(1, 0));
    // 编写一个回溯函数
    // backtrack(idx)
    // 代表当前检查 nums 中数值 idx
    int n = nums.size();
    // 这个变量用于提前终止递归回溯，当它变成 true 的时候，我们就已经成功找到了一种可行的切分方法
    bool found = false;
    function<void(int)> backtrack = [&](int idx)
    {
        // 如果我们已经检查完了整个数组，还没有返回，那么说明我们已经找到了一种可行结果，把 found 置于 true，直接返回即可
        if(idx == n)
        {
            // 注意，由于我们递归的条件是添加后子集的和不大于 sum/2，所以最后还需要额外判断一步是否真的成功分成了两组
            found = subsets[0][0] == sum/2 && subsets[1][0] == sum/2;
            return;
        }
        // 我们尝试给两个数组中的任意一个尾接当前还没尝试过的元素
        for(int i = idx; i < n; ++i)
        {
            // 首先尝试把 nums[i] 加到第一个集合中
            if(subsets[0][0] + nums[i] <= sum/2)
            {
                subsets[0][0] += nums[i];
                subsets[0].push_back(nums[i]);
                // 递归
                backtrack(i+1);
                // 如果 found == true，那么我们就可以提前返回了
                if(found)
                {
                    return;
                }
                // 回溯
                subsets[0][0] -= nums[i];
                subsets[0].pop_back();
            }
            if(subsets[1][0] + nums[i] <= sum/2)
            {
                // 再尝试把 nums[i] 加到第二个集合中
                subsets[1][0] += nums[i];
                subsets[1].push_back(nums[i]);
                // 递归
                backtrack(i+1);
                // 如果 found == true，那么我们就可以提前返回了
                if(found)
                {
                    return;
                }
                // 回溯
                subsets[1][0] -= nums[i];
                subsets[1].pop_back();
            }
        }
    };
    // 调用函数即可
    backtrack(0);
    return found;
}

// 上面的暴力 DFS 方法很容易就超时了
// 我们需要考虑更好的求解办法
// 我们换一下 DFS 子问题中，添加元素的限制条件
// 每一个子问题条件下，我们都会有一个当前 nums 中所有元素被添加的状态信息
// 一定是有一部分元素被添加到某个子集中，而其它元素没有被添加
// 我们可以记录下面的信息：
// 当前这个分配状态 state 作为起始点，我们是否能够组合剩下的元素，分出 k 个等和子集
// 剩下的解法和一般的回溯是完全一样的
// 这样只是进行了一些微不足道的剪枝，时间复杂度依然是指数级别的，本题依然会 TLE
bool canPartition(vector<int>& nums)
{
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if(sum%2)
    {
        return false;
    }
    vector<int> sums(2, 0);
    // 8 个 32 位的整型数足够表示200位二进制数
    vector<int> used(8, 0);
    bool found = false;
    // 对 nums 数组降序排列，有利于我们后续剪枝
    sort(nums.begin(), nums.end(), [&](const int& a, const int& b) {
        return a > b;
    });
    function<void(int)> dfs = [&](int idx)
    {
        // 基本情况
        // idx == n
        // 此时说明所有元素都已经被添加完毕了，我们只需要检查是不是所有元素的和都是 sum/2 即可
        if(idx == n)
        {
            found = sums[0] == sum/2 && sums[1] == sum/2;
            return;
        }
        // 其它情况下，对于当前元素，我们考虑分别尝试把它放到两个不同的集合中
        // 首先尝试放到第一个集合中
        // 如果这个元素已经用过了，那么我们不需要进一步深入递归，跳过这个元素即可
        if(used[idx/32] & (1<<(idx%32)))
        {
            return;
        }
        // 同时，因为我们按照降序进行排列，如果当前元素和前一个相同，那么我们也没必要进一步深入了，因为这个元素前面已经检查过了，没找到合法解
        if(idx > 0 && nums[idx] == nums[idx-1])
        {
            return;
        }
        // 否则，我们可以深入递归
        for(int j = 0; j < k; ++j)
        {
            if(sums[0]+nums[idx] > sum/2)
            {
                // 如果这个和已经大于了 sum/2 
                // 那么不可能有可行解，直接返回即可
                return;
            }
            // 否则，我们可以尝试当前这个元素
            sums[0] += nums[idx];
            // 记录已经使用过
            used[idx/32] = (1<<(idx%32)) | used[idx/32];
            // 递归
            dfs(idx+1);
            // 检查是否已经找到了结果
            if(found)
            {
                return;
            }
            // 否则，没找到，我们回溯
            used[idx/32] = (1<<(idx%32)) ^ used[idx/32];
            sums[0] -= nums[idx];
        }
    };
    // 调用函数即可
    dfs(0);
    return found;
}