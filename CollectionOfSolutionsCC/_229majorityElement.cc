#include "Solution.h"

vector<int> Leetcode201_300::Solution::majorityElement(vector<int>& nums)
{
    // 本题是摩尔投票的进阶题目，可以考虑使用拓展形式的摩尔投票算法
    // 注意到这样一个事实：假设这个数组的大小为 n，那么这个数组中至多只会有两个出现超过 ⌊n/3⌋ 次的元素
    // 反证法：假设出现了三个这样的元素，那么这三种元素出现的次数之和为：⌊n/3⌋ * 3，不难发现这个值一定是大于 n 的。可以自己考察一下向下取整这个运算符的结果
    // 因而我们可以设两个 "候选人" 变量以及对应的 "票数"
    // 之后使用类似基础题的方法
    // 这里我们用下标记录的方法来对 candidatex 变量进行初始化
    int candidate1 = -1, candidate2 = -1;
    int cnt1 = 0, cnt2 = 0;
    int n = nums.size();
    for(int i = 0; i < n; ++i)
    {
        // 如果我们还没有记录一个可能的 "一号候选人"，那么我们记录当前这个序号代表的候选人为 "一号候选人"，并记录他得到的票数为1
        if(candidate1 == -1)
        {
            candidate1 = i;
            cnt1 = 1;
        }
        // 否则，我们已经记录了第一个可能的 "一号候选人"，那么如果当前这个序号代表的候选人也是 "一号候选人"，那么我们给他的票数加一
        else if(nums[i] == nums[candidate1])
        {
            ++cnt1;
        }
        // 否则，我们已经记录了第一个可能的 "一号候选人"，并且当前这个序号代表的候选人不是 "一号候选人"，那么我们按序检查 "二号候选人"
        else if(candidate2 == -1)
        {
            candidate2 = i;
            cnt2 = 1;
        }
        // 否则，我们还要检查 "二号候选人" 是否与当前元素相等
        else if(nums[i] == nums[candidate2])
        {
            ++cnt2;
        }
        // 到了这里，我们可以断定，这个序号和两个已经决定的 "候选人" 的序号都不同，那么我们需要 "抵消" 每一个候选人的一张票
        else 
        {
            if(--cnt1 == 0)
            {
                candidate1 = -1;
            }
            if(--cnt2 == 0)
            {
                candidate2 = -1;
            }
        }
    }
    // 全部结束后，我们检查两个候选人位置是否存在得票较多的候选人，如果存在，那么我们还需要额外进行一轮检查，判断他的得票数是不是真的超过了 ⌊n/3⌋ 张
    if(candidate1 == -1 && candidate2 == -1)
    {
        return {};
    }
    cnt1 = 0; cnt2 = 0;
    for(int i = 0; i < n; ++i)
    {
        if(candidate1 != -1 && nums[i] == nums[candidate1])
        {
            ++cnt1;
        }
        if(candidate2 != -1 && nums[i] == nums[candidate2])
        {
            ++cnt2;
        }
    }
    vector<int> res;
    if(cnt1 > n/3)
    {
        res.push_back(nums[candidate1]);
    }
    if(cnt2 > n/3)
    {
        res.push_back(nums[candidate2]);
    }
    return res;
}

// 注意，第一版的代码有问题：
// 具体说明一下
// 分类讨论的逻辑上有漏洞，对于下面的例子：
// [2,1,1,3,1,4,5,6]
// 由于我们在检查时是先检查 candidate1，如果它没被记录，就把当前元素记录到里面，这实际上是有问题的，如果此时 nums[i] 实际上是 candidate2 的元素，那么我们实际上记录成了：一号二号候选人都是 i 下标处的这个候选人，这样显然是错误的
// 进行改正
vector<int> majorityElement(vector<int>& nums)
{
    int candidate1 = -1, candidate2 = -1;
    int cnt1 = 0, cnt2 = 0;
    int n = nums.size();
    for(int i = 0; i < n; ++i)
    {
        if(candidate1 != -1 && nums[i] == nums[candidate1])
        {
            ++cnt1;
        }
        else if(candidate2 != -1 && nums[i] == nums[candidate2])
        {
            ++cnt2;
        }
        else if(candidate1 == -1)
        {
            candidate1 = i;
            ++cnt1;
        }
        else if(candidate2 == -1)
        {
            candidate2 = i;
            ++cnt2;
        }
        else
        {
            if(--cnt1 == 0)
            {
                candidate1 = -1;
            }
            if(--cnt2 == 0)
            {
                candidate2 = -1;
            }
        }
    }
    // 结束大循环后，再遍历一轮
    // 如果没必要遍历了，就直接返回空集合
    if(candidate1 == -1 && candidate2 == -1)
    {
        return {};
    }
    cnt1 = 0; cnt2 = 0;
    for(int i = 0; i < n; ++i)
    {
        if(candidate1 != -1 && nums[i] == nums[candidate1])
        {
            ++cnt1;
        }
        else if(candidate2 != -1 && nums[i] == nums[candidate2])
        {
            ++cnt2;
        }
    }
    vector<int> res;
    if(cnt1 > n/3)
    {
        res.push_back(nums[candidate1]);
    }
    if(cnt2 > n/3)
    {
        res.push_back(nums[candidate2]);
    }
    return res;
}