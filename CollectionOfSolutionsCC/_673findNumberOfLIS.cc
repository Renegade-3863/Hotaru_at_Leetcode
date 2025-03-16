#include "Solution.h"

// 个人认为，面试的时候可以把下面这种方法大致写出来并跑通，就已经很不错了
// 这道题真的难度比较大，尤其是 O(nlogn) 的树状数组解法
int Leetcode601_700::Soltuion::findNumberOfLIS(vector<int>& nums)
{
    // 个人认为这道题是 300 题的拓展版本
    // 题目要求我们找出的是最长的递增子序列的个数
    // O(nlogn) 复杂度的解法等我大致研究一下树状数组的基本原理再说吧。。
    // 首先考虑简单一些的 DP 方法
    // 我们可以先找出 "最长的递增子序列的长度"
    // 这就是 300 题
    // 之后，我们考虑再用一层 DP，找出整个数组中，长度为 maxLen 的递增子序列的个数 res，这个 res 就是结果
    // 先处理一下第一部分
    // 定义一个 memo 数组，这个数组内记录的是动态的：
    // 长度为 j 的子序列，最小的结尾元素
    // 之后我们在遍历到 nums[i] 的时候，我们可以尝试把这个元素插入到前面，尝试更新出一个更优的 memo 数组
    // 假设此时 memo 数组中有 k 个元素，分别代表长度为 1 - k-1 的递增子序列的最小结尾元素
    // 那么对于 nums[i]，我们实际上只需要找这 k 个有序元素中第一个大不小于它的值的下标
    // 因为对于那些值本身就小于它的元素，从定义上来说，nums[i] 没法代替它们，或者也没必要代替它们
    // 而对于那些值不小于它的元素，我们只能修改第一个不小于它的元素
    // 因为如果用 nums[i] 同时替代第一个不小于它的元素，以及后续的不小于它的元素，那么相当于我们用了同一个元素两次
    // 而却生成了两个不同长度的子序列
    // 这显然是错误的，跟数组本身的定义相悖
    vector<int> memo;
    for(const auto& num : nums)
    {
        // 检查 memo 中第一个不小于 num 的元素下标
        int pos = memo.size();
        int left = 0, right = memo.size()-1;
        while(left <= right)
        {
            int mid = ((right-left)>>1)+left;
            // 判断 memo[mid] 和 num 的大小关系
            if(memo[mid] >= num)
            {
                // 作为备选答案，记录给 pos，并往左缩小区间
                pos = mid;
                right = mid-1;
            }
            else
            {
                // mid 不可能作为备选答案，往右缩小区间
                left = mid+1;
            }
        }
        // 如果 pos == memo.size()，那么 memo 只能接到 memo 尾部，构成一个更长的递增子序列
        // 否则，可以把 memo[pos] 修改成 num
        if(pos == memo.size())
        {
            memo.push_back(num);
        }        
        else
        {
            memo[pos] = num;
        }
    }
    // 最后，memo 的总长度就是最长的递增子序列的长度
    int maxLen = memo.size();
    // 第二步，我们使用一轮 O(n^2) 的 DP 算法进行处理
    // 尝试定义递归子问题：
    // dfs(i, k) 代表以 nums[i] 结尾，并且长度为 k 的递增子序列的总个数
    // 之后考虑如何进行递推
    // dfs(i, k) = sum of all j from 0 to i-1 : dfs(j, k-1)
    // 也就是说，以 nums[i] 结尾，并且长度为 k 的递增子序列的总个数
    // 等于前面所有长度为 k-1 的子序列的个数和
    // 注意检查 nums[j] < nums[i] 是否成立，只有这个条件成立的情况下我们才能进行累加
    function<int(int, int)> dfs = [&](int i, int k) -> int
    {
        // 基本情况1：如果 k == 1，那么返回 1 即可
        if(k == 1)
        {
            return 1;
        }
        // 基本情况2：如果 i < k-1，那么不可能有可行的结果，因为前面的元素全算上，也不够 k 个元素，此时返回 0
        if(i < k-1)
        {
            return 0;
        }
        // 剩下的是一般情况
        int res = 0;
        for(int j = 0; j < i; ++j)
        {
            if(nums[j] < nums[i])
            {
                // 可以尾接，那么累加结果
                res += dfs(j, k-1);
            }
        }
        return res;
    };
    int ans = 0, n = nums.size();
    for(int i = 0; i < n; ++i)
    {
        ans += dfs(i, maxLen);
    }
    return ans;
}


// 第二版：尝试对上面的第二步 dfs 进行记忆化优化
int findNumberOfLIS(vector<int>& nums)
{
    // 前面和 300 题一样的部分不用改，原样拿过来就行
    vector<int> memo;
    for(const auto& num : nums)
    {
        // 检查 memo 中第一个不小于 num 的元素下标
        int pos = memo.size();
        int left = 0, right = memo.size()-1;
        while(left <= right)
        {
            int mid = ((right-left)>>1)+left;
            // 判断 memo[mid] 和 num 的大小关系
            if(memo[mid] >= num)
            {
                // 作为备选答案，记录给 pos，并往左缩小区间
                pos = mid;
                right = mid-1;
            }
            else
            {
                // mid 不可能作为备选答案，往右缩小区间
                left = mid+1;
            }
        }
        // 如果 pos == memo.size()，那么 memo 只能接到 memo 尾部，构成一个更长的递增子序列
        // 否则，可以把 memo[pos] 修改成 num
        if(pos == memo.size())
        {
            memo.push_back(num);
        }        
        else
        {
            memo[pos] = num;
        }
    }
    // 最后，memo 的总长度就是最长的递增子序列的长度
    int maxLen = memo.size();
    // 第二部分，加上个记忆化数组进行加速即可
    int n = nums.size();
    vector<vector<int>> memoization(n, vector<int>(maxLen+1, -1));
    function<int(int, int)> dfs = [&](int i, int k) -> int
    {
        // 基本情况1：如果 k == 1，那么返回 1 即可
        if(k == 1)
        {
            return 1;
        }
        // 基本情况2：如果 i < k-1，那么不可能有可行的结果，因为前面的元素全算上，也不够 k 个元素，此时返回 0
        if(i < k-1)
        {
            return 0;
        }
        if(memoization[i][k] != -1)
        {
            return memoization[i][k];
        }
        // 剩下的是一般情况
        int res = 0;
        for(int j = 0; j < i; ++j)
        {
            if(nums[j] < nums[i])
            {
                // 可以尾接，那么累加结果
                res += dfs(j, k-1);
            }
        }
        memoization[i][k] = res;
        return res;
    };
    int ans = 0;
    for(int i = 0; i < n; ++i)
    {
        ans += dfs(i, maxLen);
    }
    return ans;
}

// 第三版来尝试一下更高级的树状数组解法
// 