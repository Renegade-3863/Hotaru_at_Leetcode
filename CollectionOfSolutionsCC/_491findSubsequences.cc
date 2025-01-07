#include "Solution.h"

vector<vector<int>> Leetcode401_500::Soltuion::findSubsequences(vector<int>& nums)
{
    // 题目要求我们返回的是实际的结果集合，而不是简单计算答案个数，所以我们考虑使用回溯进行暴搜
    // 老办法，回溯就画回溯树
    // 我们依然用递归嵌套循环的方式来进行搜索
    // 本题中的元素可能包含重复，所以在检查的过程中需要想办法去重
    // 自己简单画一棵回溯树，我们不难发现，无非就是一种需要去除的重复：
    // 1. 树中同层的重复元素
    // 2. 树中同一枝中的重复 (至于第二种，这种经过考虑后，会发现实际上不应该删掉)
    // 这里简单解释一下第二种为什么不需要考虑：
    // 举例：[4, 6, 7, 7, 7]
    // 这里，如果我们第一个元素填了 7，那么之后要么是连续填两个 7，要么是只填一个 7，不会出现重复填两次 7 (一次填第二个 7，一次填第三个 7)，得出两个 [7, 7] 的情况
    // 换句话说，第一种重复已经避免了所有可能的重复
    // 明确了基本的逻辑，剩下的就只有写代码了
    int n = nums.size();
    // 定义一个 path 数组，用来记录所有过程中的子序列，也用来实际给答案数组赋值
    vector<int> path;
    // res 是答案数组
    vector<vector<int>> res;
    // idx 代表，当前考虑的元素是下标为 idx 的元素
    // 这个函数的假设是：path 数组中已经有了至少一个元素，我们可以通过 path.back() 来判断 nums[idx] 是否可以添加到 path 中
    function<void(int)> backtrack = [&](int idx) 
    {
        // 首先设定一个递归的结束条件：idx >= n (n 为 nums 的长度)
        if(idx >= n)
        {
            // 到达了递归终点，返回即可
            return;
        }
        // 我们需要做的事情很简单，就是记录同一层已经添加过的元素，可以通过一个哈希集合来实现
        unordered_set<int> memo;
        // 尝试把 idx 和后面的所有元素中的任意一个放到 path 的结尾上
        for(int i = idx; i < n; ++i)
        {
            // 注意，还需要检查是否是非递减的，否则一样不能添加
            if(memo.count(nums[i]) == 0 && path.back() <= nums[i])
            {
                // 记录当前层添加过这个元素
                memo.insert(nums[i]);
                // 同一层中没有添加过同一个元素，那么我们可以进行添加
                path.push_back(nums[i]);
                // 记录到 res 中
                res.push_back(path);
                // 递归
                backtrack(i+1);
                // 回溯
                path.pop_back();
            }
            // 否则，说明这个元素在同一层中已经添加过了，重复添加会导致得出重复的结果，我们跳过它即可
        }
    };
    // 最后就是调用 backtrack 函数
    // 注意，我们需要枚举 path 的所有开头元素，以此来满足 backtrack 函数的假设
    // 最外层也需要一个哈希集合，用来防止重复
    unordered_set<int> memo;
    for(int i = 0; i < n; ++i)
    {
        // 注意，这里也需要防止重复添加，不然会得出重复结果
        if(memo.count(nums[i]) == 0)
        {
            // 初始化 path，之后是调用 backtrack
            path.push_back(nums[i]);
            // 记录添加过
            memo.insert(nums[i]);
            backtrack(i+1);
            // 回溯
            path.pop_back();
        }
    }
    // 检查结束，返回结果即可
    return res;
}