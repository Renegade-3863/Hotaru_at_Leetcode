#include "Solution.h"

bool Leetcode401_500::Soltuion::makesquare(vector<int>& matchsticks)
{
    // 经典的 "分成等和的四组" 问题
    // 本题的基本方法是回溯，常说的 dp 解法是之前的 "等分成等和的两组" 问题
    // 不过可以有一点预先的检查，如果 matchsticks 的元素和不是 4 的倍数，那么很明显我们就不可能把 matchsticks 的元素等分成四份了
    int sum = accumulate(matchsticks.begin(), matchsticks.end(), 0);
    if(sum % 4)
    {
        // 不是 4 的倍数，那么直接返回 false 就行，不可能拿到可行的分组
        return false;
    }
    // 否则说明有可能分成 4 份，我们可以继续进行检查
    // 回溯依然是画回溯树
    // 首先，既然要分成四等份，那么每一份肯定是 sum/4 为和
    int target = sum/4;
    // 我们按照回溯填数的想法，初始化一个有 4 个元素的数组
    // 之后按顺序分别尝试把 matchsticks 中的每个元素放到这个数组中每条 "边" 上，如果某次添加会导致 "边" 过长，那么我们就直接返回，不进一步深入检查
    // 否则，就进行添加，并深入递归
    // idx 代表当前在检查的 matchsticks 下标
    // 分别代表四条边当前的长度，用于递归回溯过程
    vector<int> edges(4, 0);
    function<bool(int)> backtrack = [&](int idx) -> bool
    {
        // 别忘了设定一个递归的终止情况：
        // 如果 idx == matchsticks.size()，那么不用深入了，直接返回 true 即可
        if(idx == matchsticks.size())
        {
            return true;
        }
        // 根据下面的推理，我们这里记录一个 "检查过" 值表
        // 所有这里检查过的元素我们都不再递归了
        unordered_set<int> checked;
        // 对于当前 matchsticks[idx] 位置的元素，它可以分别被放入到四条 "边" 中的任意一条中
        for(int i = 0; i < 4; ++i)
        {
            if(checked.find(edges[i]) != checked.end())
            {
                // 检查过了，没有返回 true，说明我们不用再尝试把 matchsticks[idx] 放到 edges[i] 中了
                continue;
            }
            // 尝试把 matchsticks[idx] 放入 edges[i] 中
            // 注意避免数值溢出
            // edges[i]+matchsticks[idx] <= target && edges[i]+matchsticks[idx] < INT_MAX
            if(matchsticks[idx] < INT_MAX - edges[i] && edges[i]+matchsticks[idx] <= target)
            {
                // 递归
                edges[i] += matchsticks[idx];
                // 可以添加，那么添加并递归即可
                if(backtrack(idx+1))
                {
                    return true;
                }
                // 别忘了回溯
                edges[i] -= matchsticks[idx];
                checked.insert(edges[i]);
            }
            // 否则，不可行，那么我们继续尝试添加到下一条 "边" 即可
            // 不过，思考这样的问题：如果 edges[i] 后面的元素等于 edges[i]，那么很明显我们不用重复尝试，结果是一样的
            // 我们记录一下检查过的 edges[i]，不要重复检查即可
        }
        // 四轮循环尝试完，没有返回 true，说明我们没找到可行解，直接返回 false 即可
        return false;
    };
    // 直接调用这个函数即可
    return backtrack(0);
}

// 上面的回溯解法会 TLE，我们需要考虑如何进行剪枝优化
// 最刺眼的其实就是每个 backtrack 中出现的 unordered_set 哈希集合，这个东西每次的搜索复杂度肯定不低，我们从它入手考虑如何进行第一步优化
// 看题解区有一个退而求其次的优化措施，很令人惊讶的是，这种不绝对的优化居然能勉强通过本题hhhh
// 我们不再每次都记录一个哈希集合，而是只检查 edges[i] 和 edges[i-1] 是否相等，如果相等，那么我们不再重复检查
// 不知道是不是本题的数据原因，这样做之后反而能够勉强通过。。。
bool makesquare(vector<int>& matchsticks)
{
    // 经典的 "分成等和的四组" 问题
    // 本题的基本方法是回溯，常说的 dp 解法是之前的 "等分成等和的两组" 问题
    // 不过可以有一点预先的检查，如果 matchsticks 的元素和不是 4 的倍数，那么很明显我们就不可能把 matchsticks 的元素等分成四份了
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if(sum % 4)
    {
        // 不是 4 的倍数，那么直接返回 false 就行，不可能拿到可行的分组
        return false;
    }
    // 否则说明有可能分成 4 份，我们可以继续进行检查
    // 回溯依然是画回溯树
    // 首先，既然要分成四等份，那么每一份肯定是 sum/4 为和
    int target = sum/4;
    // 我们按照回溯填数的想法，初始化一个有 4 个元素的数组
    // 之后按顺序分别尝试把 matchsticks 中的每个元素放到这个数组中每条 "边" 上，如果某次添加会导致 "边" 过长，那么我们就直接返回，不进一步深入检查
    // 否则，就进行添加，并深入递归
    // idx 代表当前在检查的 matchsticks 下标
    // 分别代表四条边当前的长度，用于递归回溯过程
    vector<int> edges(4, 0);
    function<bool(int)> backtrack = [&](int idx) -> bool
    {
        // 别忘了设定一个递归的终止情况：
        // 如果 idx == matchsticks.size()，那么不用深入了，直接返回 true 即可
        if(idx == nums.size())
        {
            return true;
        }
        // 根据下面的推理，我们这里记录一个 "检查过" 值表
        // 所有这里检查过的元素我们都不再递归了
        // unordered_set<int> checked;
        // 对于当前 matchsticks[idx] 位置的元素，它可以分别被放入到四条 "边" 中的任意一条中
        for(int i = 0; i < 4; ++i)
        {
            // if(checked.find(edges[i]) != checked.end())
            // {
            //     // 检查过了，没有返回 true，说明我们不用再尝试把 matchsticks[idx] 放到 edges[i] 中了
            //     continue;
            // }
            if(i > 0 && edges[i] == edges[i-1])
            {
                continue;
            }
            // 尝试把 matchsticks[idx] 放入 edges[i] 中
            // 注意避免数值溢出
            // edges[i]+matchsticks[idx] <= target && edges[i]+matchsticks[idx] < INT_MAX
            if(nums[idx] < INT_MAX - edges[i] && edges[i]+nums[idx] <= target)
            {
                // 递归
                edges[i] += nums[idx];
                // 可以添加，那么添加并递归即可
                if(backtrack(idx+1))
                {
                    return true;
                }
                // 别忘了回溯
                edges[i] -= nums[idx];
                // checked.insert(edges[i]);
            }
            // 否则，不可行，那么我们继续尝试添加到下一条 "边" 即可
            // 不过，思考这样的问题：如果 edges[i] 后面的元素等于 edges[i]，那么很明显我们不用重复尝试，结果是一样的
            // 我们记录一下检查过的 edges[i]，不要重复检查即可
        }
        // 四轮循环尝试完，没有返回 true，说明我们没找到可行解，直接返回 false 即可
        return false;
    };
    // 直接调用这个函数即可
    return backtrack(0);
}

// 最后是一个很玄学的优化，还是来自官方题解，个人认为，面试中，能有逻辑地写明白上面两种中的任何一种，都已经足够证明个人能力了
// 最后这个排序优化个人认为能想到最好，想不到也无所谓的
bool makesquare(vector<int>& matchsticks)
{
    // 经典的 "分成等和的四组" 问题
    // 本题的基本方法是回溯，常说的 dp 解法是之前的 "等分成等和的两组" 问题
    // 不过可以有一点预先的检查，如果 matchsticks 的元素和不是 4 的倍数，那么很明显我们就不可能把 matchsticks 的元素等分成四份了
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if(sum % 4)
    {
        // 不是 4 的倍数，那么直接返回 false 就行，不可能拿到可行的分组
        return false;
    }
    // 否则说明有可能分成 4 份，我们可以继续进行检查
    // 回溯依然是画回溯树
    // 首先，既然要分成四等份，那么每一份肯定是 sum/4 为和
    int target = sum/4;
    // 我们按照回溯填数的想法，初始化一个有 4 个元素的数组
    // 之后按顺序分别尝试把 matchsticks 中的每个元素放到这个数组中每条 "边" 上，如果某次添加会导致 "边" 过长，那么我们就直接返回，不进一步深入检查
    // 否则，就进行添加，并深入递归
    // idx 代表当前在检查的 matchsticks 下标
    // 分别代表四条边当前的长度，用于递归回溯过程
    vector<int> edges(4, 0);
    // 这里是唯一的优化语句，我们对 nums 数组按降序排列，这样我们在递归的过程中会优先检查那些更长的 "火柴"
    // 由于我们先检查更长的火柴，那么就会更少出现：先放了一个短火柴，之后更长的火柴被这根短火柴卡住，从而导致这种填法不合法，需要回溯重填 的情况
    // 经过最后这种优化，解决方案的速度达到了最快
    sort(nums.begin(), nums.end(), [&](const int& a, const int& b) -> bool {
        return a > b;
    });
    function<bool(int)> backtrack = [&](int idx) -> bool
    {
        // 别忘了设定一个递归的终止情况：
        // 如果 idx == matchsticks.size()，那么不用深入了，直接返回 true 即可
        if(idx == nums.size())
        {
            return true;
        }
        // 根据下面的推理，我们这里记录一个 "检查过" 值表
        // 所有这里检查过的元素我们都不再递归了
        // unordered_set<int> checked;
        // 对于当前 matchsticks[idx] 位置的元素，它可以分别被放入到四条 "边" 中的任意一条中
        for(int i = 0; i < 4; ++i)
        {
            // if(checked.find(edges[i]) != checked.end())
            // {
            //     // 检查过了，没有返回 true，说明我们不用再尝试把 matchsticks[idx] 放到 edges[i] 中了
            //     continue;
            // }
            if(i > 0 && edges[i] == edges[i-1])
            {
                continue;
            }
            // 尝试把 matchsticks[idx] 放入 edges[i] 中
            // 注意避免数值溢出
            // edges[i]+matchsticks[idx] <= target && edges[i]+matchsticks[idx] < INT_MAX
            if(nums[idx] < INT_MAX - edges[i] && edges[i]+nums[idx] <= target)
            {
                // 递归
                edges[i] += nums[idx];
                // 可以添加，那么添加并递归即可
                if(backtrack(idx+1))
                {
                    return true;
                }
                // 别忘了回溯
                edges[i] -= nums[idx];
                // checked.insert(edges[i]);
            }
            // 否则，不可行，那么我们继续尝试添加到下一条 "边" 即可
            // 不过，思考这样的问题：如果 edges[i] 后面的元素等于 edges[i]，那么很明显我们不用重复尝试，结果是一样的
            // 我们记录一下检查过的 edges[i]，不要重复检查即可
        }
        // 四轮循环尝试完，没有返回 true，说明我们没找到可行解，直接返回 false 即可
        return false;
    };
    // 直接调用这个函数即可
    return backtrack(0);
}