#include "Solution.h"

vector<vector<int>> Leetcode1_100::Solution::threeSum(vector<int>& nums)
{
    // 题目要求我们通过一个无序数组找出是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k 同时还满足
    // nums[i] + nums[j] + nums[k] == 0
    // 本题我们依然可以从最暴力的方法入手
    // 我们可以每次固定一个三元组的首元 (假设下标为i)
    // 之后再固定这个三元组的第二个元素 (假设下标为j)
    // 最后选择这个三元组的第三个元素 (假设下标为k)
    // 计算过一次三数之和之后，先固定前两个元素，移动第三个元素，检查完成后移动第二个元素，再检查完第二个元素后移动第一个元素
    // 不难写出下面这种代码
    // 避雷：我设计的这个哈希函数是有很大冲突概率的，如果有会设计哈希函数的朋友可以尝试暴力+低重复概率哈希函数莽一下试试，这里我就放弃了
#if 0
    int n = nums.size();
    struct hashFunc {
        size_t operator()(const vector<int>& v) const
        {
            return hash<int>()(v[0]) + hash<int>()(v[1]) + hash<int>()(v[2]);
        }
    };
    struct hashEqual {
        bool operator()(const vector<int>& a, const vector<int>& b) const
        {
            int sum = 0;
            for(int i = 0; i < 3; ++i)
            {
                sum ^= a[i];
            }
            for(int j = 0; j < 3; ++j)
            {
                sum ^= b[j];
            }
            return sum == 0;
        }
    };
    // 加一个哈希表用于去重，注意 vector<int> 不是常规的数据类型，STL本身不提供针对它的哈希函数，需要前面自己定义仿函数对哈希方法进行替换
    unordered_map<vector<int>, bool, hashFunc, hashEqual> exist;
    vector<vector<int>> ans;
    // 最后一个可行位置为 n-3，唯一三元组为 nums[n-3], nums[n-2], nums[n-1]
    for(int first = 0; first <= n-3; ++first)
    {
        for(int second = first+1; second <= n-2; ++second)
        {
            for(int third = second+1; third <= n-1; ++third)
            {
                int tmp = nums[first]+nums[second]+nums[third];
                if(tmp == 0)
                {
                    if(exist.find(vector<int>{nums[first], nums[second], nums[third]}) == exist.end())
                    {
                        ans.emplace_back(vector<int>{nums[first], nums[second], nums[third]});
                        exist[vector<int>{nums[first], nums[second], nums[third]}] = true;
                    }
                }
            }
        }
    }
    return ans;

#endif

    // 上面尝试莽暴力方法失败了
    // 那么我们就需要思考如何优化检查效率，同时避免哈希这种低效而困难的去重方案
    // 首先，应该能注意到一个非常重要的事实：我们要找的元组在数组中不一定是连续出现的(要找的是序列，不是子数组)
    // 那么一个直觉应该是，如果数组从无序变为有序，会对我们进行检查优化有所帮助
    // 排序后数组有序，那么接下来如何进行优化？
    // 很显然第一层循环我们没法优化，保持原样不变
    // 对于每个 first，我们是否可以从 second 和 third 入手做优化？
    // 现在 second 和 third 数之间有一层隐含的大小关系：nums[second] <= nums[third]
    // 那么我们应该能够想到可以使用类似双指针的方法进行双向奔赴
    // 我们第一次检查 nums[first]+nums[first+1]+nums[n-1] (n 为 nums 总长度)
    // 注意到一个事实很重要，我们假设一个对于 first 变量的循环不变式：每次修改 first (+1)，
    // 这个 first 值以及比它小的所有 first 值作为首元的三元组已经被检查完毕了
    // 上面两行的事实对于 second 变量一样成立
    // 如果这个值是小于 0 的，那么由于 second 变量不可能往左变化，因而想把这个值向零逼近，我们只能减小 third 变量
    // 如果这个值是大于 0 的，那么由于 third 变量不可能往右变化，因而想把这个值向零逼近，我们只能增大 second 变量
    // 等于的情况很简单，直接添加结果三元组即可
    // 现在寻找可行解的算法我们已经找到了，那么如何去重呢？上面这个方法应该依然是有重复的，因为我们没法保证在某个合法解中出现过的三个元素，
    // 以另一种排列形式出现在另一个答案数组中
    // 如何避免这种情况？
    // 考虑我们现在的状态
    // 可能出现的重复是：
    // [-1, 0, 1]和[-1, 1, 0]
    // 和[1, 0, -1]
    // 和[1, -1, 0]
    // 和[0, 1, -1]
    // 和[0, -1, 1]
    // 其实可以观察出的一种可能的重复类型是完全重复：对于同一个位置 (例如first) 两次选到了相同的数，导致后面也选出了一样的数据
    // 另一种重复类型是重排重复，就是我们选出了一种出现过的三元组的完全打乱重排
    // 第一种很好解决，因为我们的数组已经是有序的了，因而可以直接判断我们每次更新的 first/second 值是否和上一个相等，如果重复了，那么就不再对这个值进行检查
    // 这样就避免了完全相同数组的重复
    // 第二种其实已经被我们的排序方案给隐式地避免了
    // 因为我们的排序策略保证了如果有和为固定值的元组，其中的元素一定是有序的，即使不是完全升序，我们在上面的跳过策略也已经避免了重复选择一样的数据
    // 故综上，我们已经实现了去重功能
    // 代码实现在分析过后就变得简单了
    
    // 答案数组
    vector<vector<int>> ans;
    int n = nums.size();
    sort(nums.begin(), nums.end());
    for(int first = 0; first < n-2; ++first)
    {
        if(first > 0 && nums[first-1] == nums[first])
        {
            continue;
        }
        int second = first+1, third = n-1;
        while(second < third)
        {
            if(second > first+1 && nums[second-1] == nums[second])
            {
                ++second;
                continue;
            }
            int sum = nums[first]+nums[second]+nums[third];
            if(sum > 0)
            {
                // 比0大，此时要左移 third 指针
                --third;
            }
            else if(sum == 0)
            {
                // 找到了可行解
                ans.emplace_back(vector<int>{nums[first], nums[second], nums[third]});
                // 此时注意，我们必须移动 second 和 third 中的一个，否则会出现 [-2, 1, 1, 1, 1] 这种重复问题
                // 其实仔细思考大家会发现，second 和 third 是可以一起内移的，因为只要保证了其中一个数值不会重复选取，那么另一个也一定不会重复选取了
                // 所以我们选择二者一起内移
                ++second; --third;

            }
            else
            {
                // 比0小，要右移 second
                ++second;
            }
        }
    }
}