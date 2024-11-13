#include "Solution.h"

Leetcode301_400::Solution::Solution::Solution(vector<int>& nums)
{
    // 本题不是很难，比较考验我们的设计能力
    // 我们需要对每一个值保存一组下标集合，之后对相应的下标集合进行随机取值即可
    int n = nums.size();
    for(int i = 0; i < n; ++i)
    {
        this->memo[nums[i]].push_back(i);
    }
}

int Leetcode301_400::Solution::Solution::pick(int target)
{
    // 我们根据这个 target 取出对应的数组的指针，随机取一个下标返回即可
    // 防止爆炸，检查一下 target 是否存在于 memo 中
    if(this->memo.find(target) == this->memo.end())
    {
        // 返回 -1，代表这个 target 找不到下标
        return -1;
    }
    const vector<int>& ref = this->memo[target];
    int random = rand() % ref.size();
    return ref[random];
}