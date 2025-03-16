#include "Solution.h"

bool Leetcode601_700::Soltuion::isPossible(vector<int>& nums)
{
    // 基本可以用贪心算法来解决
    // 我们首先用一个哈希表记录每种元素存在的总个数
    // 之后按照从小到大的顺序对整个数组进行遍历
    // 对于遍历到的每一个元素 num，如果它不是 -1 (我们规定，如果一个元素被配组成功，那么就把它对应的位置标记为 -1)
    // 那么我们检查 num+1 这个值是否还有剩，如果有，那么把对应那个元素配给 num，并把那个元素对应的数组下标修改为 -1
    // 注意：因为题目要求每一组至少长度为 3，所以每一个元素我们都要写入机制，保证如果某个元组配不到 3 个元素，那么我们就要返回 false
    // 哈希表存储的数据为：[val, (start, end)]
    // 代表：[start, end] 区间中的元素的值为 val
    unordered_map<int, pair<int, int>> memo;
    // 遍历 nums
    int n = nums.size();
    for(int i = 0; i < n; ++i)
    {
        if(memo.count(nums[i]))
        {
            // 新遇到一个元素，更新 memo[nums[i]].second
            memo[nums[i]].second = i;
        }   
        else
        {
            // 第一次遇到这个元素，那么我们初始化区间数对，左右边界均为 i
            memo[nums[i]] = make_pair<int&, int&>(i, i);
        }
    }
    // 记录完成，我们重新遍历 nums，这一轮就需要利用 memo 的信息进行贪心的配对
    // 注意，为了达到最可能最优的方案，我们每一个元组都只匹配 3 个元素，不再多配，防止占用别的元组的需求
    for(auto& num : nums)
    {
        // cout << num << " ";
        if(num == -1)
        {
            // 遇到一个已经合法配对的元素，我们跳过它即可
            continue;
        }
        // 否则，num 需要配对，我们考虑 num+1 和 num+2
        if(memo.count(num+1) && memo[num+1].first <= memo[num+1].second)
        {
            // 标记 "使用了一个元素"
            nums[memo[num+1].first] = -1;
            // 修改区间
            memo[num+1].first += 1;
        }
        // 找不到 num+1，那么直接返回 false 即可
        else
        {
            return false;
        }
        // 继续考虑 num+2
        if(memo.count(num+2) && memo[num+2].first <= memo[num+2].second)
        {
            // 标记 "使用了一个元素"
            nums[memo[num+2].first] = -1;
            // 修改区间
            memo[num+2].first += 1;
        }
        // 找不到 num+2，那么直接返回 false 即可
        else
        {
            return false;
        }
    }
    // 贪心的情况下，我们可以配对所有元素，返回 true
    return true;
}

// 上面的第一版代码有错误
// 这个样例没法通过：
// [1, 2, 3, 3, 4, 4, 5, 5]
// 原因在于我们只匹配了 {1, 2, 3} {3, 4, 5}
// 而实际上多出来的 4, 5 是可以和 {1, 2, 3} 做尾接的
// 所以我们需要一种机制来处理这种情况
// 引入一个新的哈希表即可
// 哈希表 last，记录我们有没有检出过以某个元素 num 结尾的子序列
// 对于每一个新元素 num，我们优先检查它能不能和前面已有的子序列配组，能的话，就不用占用后面的元素，新造一个子序列出来了
// 因为这样可能会导致后面其它的 num 值配不到元素
bool isPossible(vector<int>& nums)
{
    // 基本可以用贪心算法来解决
    // 我们首先用一个哈希表记录每种元素存在的总个数
    // 之后按照从小到大的顺序对整个数组进行遍历
    // 对于遍历到的每一个元素 num，如果它不是 -1 (我们规定，如果一个元素被配组成功，那么就把它对应的位置标记为 -1)
    // 首先检查 num 是否能接到一个以 num-1 结束的元组上去
    // 否则，我们检查 num+1 这个值是否还有剩，如果有，那么把对应那个元素配给 num，并把那个元素对应的数组下标修改为 -1
    // 注意：因为题目要求每一组至少长度为 3，所以每一个元素我们都要写入机制，保证如果某个元组配不到 3 个元素，那么我们就要返回 false
    // 哈希表存储的数据为：[val, (start, end)]
    // 代表：[start, end] 区间中的元素的值为 val
    unordered_map<int, pair<int, int>> memo;
    // 遍历 nums
    int n = nums.size();
    for(int i = 0; i < n; ++i)
    {
        if(memo.count(nums[i]))
        {
            // 新遇到一个元素，更新 memo[nums[i]].second
            memo[nums[i]].second = i;
        }   
        else
        {
            // 第一次遇到这个元素，那么我们初始化区间数对，左右边界均为 i
            memo[nums[i]] = make_pair<int&, int&>(i, i);
        }
    }
    unordered_map<int, int> last;
    // 记录完成，我们重新遍历 nums，这一轮就需要利用 memo 的信息进行贪心的配对
    // 注意，为了达到最可能最优的方案，我们每一个元组都只匹配 3 个元素，不再多配，防止占用别的元组的需求
    for(auto& num : nums)
    {
        // cout << num << " ";
        if(num == -1)
        {
            // 遇到一个已经合法配对的元素，我们跳过它即可
            continue;
        }
        // 否则，num 需要配对
        // 我们优先考虑把 num 和 num-1 进行尾接
        if(last[num-1] > 0)
        {
            // 有能尾接的，就尾接，这样一定更优
            --last[num-1];
            ++last[num];
            continue;
        }
        // 否则，我们考虑 num+1 和 num+2
        if(memo.count(num+1) && memo[num+1].first <= memo[num+1].second)
        {
            // 标记 "使用了一个元素"
            nums[memo[num+1].first] = -1;
            // 修改区间
            memo[num+1].first += 1;
        }
        else
        {
            // 根据上面的分析，num 既没法和前面匹配，也没法和后面匹配了，我们返回 false 即可
            return false;
        }
        // 继续考虑 num+2
        if(memo.count(num+2) && memo[num+2].first <= memo[num+2].second)
        {
            // 标记 "使用了一个元素"
            nums[memo[num+2].first] = -1;
            // 修改区间
            memo[num+2].first += 1;
            ++last[num+2];
        }
        // 找不到 num+2，那么直接返回 false 即可
        else
        {
            // 根据上面的分析，num 既没法和前面匹配，也没法和后面匹配了，我们返回 false 即可
            return false;
        }
    }
    // 贪心的情况下，我们可以配对所有元素，返回 true
    return true;
}