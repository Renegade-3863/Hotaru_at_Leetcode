#include "Solution.h"

vector<int> Leetcode401_500::Soltuion::findDisappearedNumbers(vector<int>& nums)
{
    // 简单版的原地哈希，我们依然是 "换换换" 解决
    // 考虑题目给出的基本限制条件：
    // 数组内有 n 个整数，同时 nums[i] 在区间 [1, n] 内
    // 那么我们要做的就是：把每个元素交换到 "它们该在的位置上"
    // 由于题目说明了有元素没有出现，那么反过来说，就一定有某些值重复出现，否则不可能有 n 个元素
    // 我们在交换过程中，如果发现某个元素 "该在的" 位置上已经存在了和本身值相等的另一个元素，那么我们可以直接把当前位置上这个元素修改成 -1，以防死循环的交换
    // 最后，交换完成后，再遍历一遍整个数组，值为 -1 的那些位置上 "该在的" 元素就是我们的答案
    // 写代码即可
    int n = nums.size();
    for(int i = 0; i < n; ++i)
    {
        // while 循环进行循环交换，知道 nums[i] == -1 或者 nums[i] == i+1 或者 nums[nums[i]-1] == nums[i] 为止
        while(nums[i] != -1 && nums[i] != i+1 && nums[nums[i]-1] != nums[i])
        {
            // 不断把当前位置上的元素放到 "该在的" 位置上去
            swap(nums[i], nums[nums[i]-1]);
        }
        // 退出后，检查退出原因，分别进行处理
        // 1. nums[i] == -1，那么我们什么也不用做
        // 2. nums[i] == i+1，正常情况，也不用做什么
        // 3. nums[nums[i]-1] == nums[i]，出现了重复，我们把当前位置上这个重复的元素改成 -1，代表出现了重复，也代表可能的不存在值
        if(nums[i] != -1 && nums[i] != i+1 && nums[nums[i]-1] == nums[i])
        {
            nums[i] = -1;
        }
    }
    // 整个检查一遍，记录所有值为 -1 的元素下标，+1 后记录到 res 中即可
    vector<int> res;
    for(int i = 0; i < n; ++i)
    {
        if(nums[i] == -1)
        {
            res.push_back(i+1);
        }
    }
    return res;
}