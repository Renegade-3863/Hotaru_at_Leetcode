#include "Solution.h"

vector<int> Leetcode601_700::Soltuion::smallestRange(vector<vector<int>>& nums)
{
    // 说实话，这道题和上一题都是很巧妙的困难题 (面试问了，没做过就寄的那种)
    // 这道题可以通过某种形式，转换成 76 题：最短覆盖子串
    // 我们这样来讲解转换过程：
    // 以题目的示例1来说：
    // 把所有元素以及它们属于的 nums 子数组下标进行匹配和按元素值顺序排列：
    // [(0, 0), (4, 1), (5, 2), (9, 1), (10, 0), (12, 1), (15, 0), (18, 2), (20, 1), (22, 2), (24, 0), (26, 0), (30, 2)]
    // 之后我们要做的事情就变成了：
    // 从这个数对组中找出最短的子数对组，它包含了 0, 1 和 2 这三个元素中每一种至少一个
    // 这样就转换成了 76 题！
    // 之后的流程就是和那道题一模一样的滑动窗口遍历方法了！
    // 这里感谢一下灵神的题解，我这里只是班门弄斧了：
    // https://leetcode.cn/problems/smallest-range-covering-elements-from-k-lists/description/
    vector<pair<int, int>> pairs;
    int n = nums.size();
    for(int i = 0; i < n; ++i)
    {
        for(int& number : nums[i])
        {
            pairs.push_back(make_pair<int&, int&>(number, i));
        }
    }
    // 之后把这个数对组按照第一个元素进行升序排列
    sort(pairs.begin(), pairs.end(), [&](const pair<int, int>& a, const pair<int, int>& b) 
    {
        return a.first < b.first;
    });
    // 之后的流程就和 76 题一样了
    // 我们用一个 diff 标记值，当 diff 为 0 的时候，我们就找到了一个合法的子数组，可以更新全局的结果区间
    vector<int> res(2, 0);
    int minLen = INT_MAX, diff = n;
    // 记录每个下标值出现的次数，初始值为全零
    vector<int> cnts(n, 0);
    int left = 0;
    for(int right = 0; right < pairs.size(); ++right)
    {
        // 先把 right 这个数对中的 second 下标值加 1
        // 如果加 1 后这种值达到了 1，那么我们对 diff 减 1 即可
        if(++cnts[pairs[right].second] == 1)
        {
            --diff;
        }
        // 之后，如果 diff 变成了 0，那么我们找到了一个可能行的结果，不过这个区间还可能不是最优的，我们需要通过尽量右移 left 来拿到以 right 为结尾的最优解
        while(diff == 0)
        {
            // 当前区间的长度更优，那么我们进行更新
            if(pairs[right].first-pairs[left].first+1 < minLen)
            {
                res[0] = pairs[left].first;
                res[1] = pairs[right].first;
                minLen = res[1]-res[0]+1;
            }
            // 进行了可能的更新后，我们需要尽量右移 left 指针
            if(--cnts[pairs[left++].second] == 0)
            {
                ++diff;
            }
        }
    }
    // 处理完成，返回 res 即可
    return res;
}