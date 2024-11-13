#include "Solution.h"

vector<int> Leetcode301_400::Solution::largestDivisibleSubset(vector<int>& nums)
{
    // 感觉是一道不那么好想的 DP 类题目，我们先从自顶向下的角度分析
    // 既然要找出一个子集，那么这个子集一定会有一种单调递增的序列顺序
    // 我们可以用这个单调递增顺序的最后一个数值来标识一种结果
    // 定义下面的子问题：
    // dfs(i) 代表以 nums[i] 作为子集中最大值的情况下，能够拿到的最大整除子集
    // 那么考虑如何递推
    // 如果我们把整个数组排好序，那么我们很明显可以这样进行检查：
    // 因为 dfs(k) 确保了按 nums[k] 作为结尾元素的情况下，拿到一组更小的可整除元素
    // 那么我们只需要检查 i 是否能够接到它前面任何一个更小的序列结尾元素，构成一个更长的序列即可
    // 而因为 nums[k] 和它所在的序列中前面的所有元素都有题目要求的关系模式
    // 所以我们只需要检查 nums[i] 能否和 nums[k] 形成要求的关系即可
    // 对于每个小于 i 的 k 值，我们检查 nums[k] % nums[i] == 0 || nums[i] % nums[k] 是否成立即可
    // 如果成立，那么我们更新以 nums[i] 结尾的序列最长长度为 nums[k]+1，否则，就只能更新长度为 1 (只含 nums[i] 自己的集合)
    sort(nums.begin(), nums.end());
    int n = nums.size();
    vector<int> dp(n, 1);
    // 记录长度最长的结果元素下标
    int idx = 0;
    for(int i = 0; i < n; ++i)
    {
        // 最小可以是1，即包含 nums[i] 本身的长度
        dp[i] = 1;
        for(int k = 0; k < i; ++k)
        {
            if(nums[k] % nums[i] == 0 || nums[i] % nums[k] == 0)
            {
                dp[i] = max(dp[i], dp[k]+1);
                if(dp[i] > dp[idx])
                {
                    idx = i;
                }
            }
        }
    }
    // 我们需要根据 dp 数组重构出原来的答案
    // 如何重构？
    // 首先，根据最长子序列的下标，找出序列的最后一个元素
    vector<int> res;
    int maxSize = dp[idx];
    while(1)
    {
        res.push_back(nums[idx]);
        if(--maxSize == 0)
        {
            break;
        }
        // 不断回溯 idx，找出答案序列中的下一个元素
        // 解释：如果前面的 dp[idx] 不等于 maxSize，那么很显然它不可能是我们在找的最长子序列的下一个最靠后的元素
        // 而如果 dp[idx] 等于了 maxSize，但是这个元素不能和我们上一个找出来的元素满足对应的关系，那么我们就找了一个错误的序列的尾部元素，直接跳过它即可
        while(dp[idx] != maxSize || (nums[idx] % res[res.size()-1] != 0 && res[res.size()-1] % nums[idx] != 0))
        {
            --idx;
        }
    }
    reverse(res.begin(), res.end());
    return res;
}