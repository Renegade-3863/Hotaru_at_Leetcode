#include "Solution.h"

vector<vector<int>> Leetcode1_100::Solution::fourSum(vector<int> &nums, int target)
{
    // 本题只是套了一层嵌套的三数之和
    // 只需基于三数之和的解法在外面再套一层循环即可
    // 存储所有有效的无重复四元组
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    int n = nums.size();
    for (int first = 0; first < n - 3; ++first)
    {
        // 如果有重复了，代表我们之前已经检查过了当前数字作为这个对应元素的情况，需要跳过这个数字
        if (first > 0 && nums[first - 1] == nums[first])
        {
            continue;
        }
        for (int second = first + 1; second < n - 2; ++second)
        {
            // 原理同first
            if (second > first + 1 && nums[second - 1] == nums[second])
            {
                continue;
            }
            int third = second + 1, fourth = n - 1;
            // 加一个优化措施，预先检查两个边界情况，如果已经不合法了，就不用继续遍历进行检查了
            if((long long)nums[first]+nums[second]+nums[second+1]+nums[second+2] > target)
            {
                continue;
            }
            else if((long long)nums[first]+nums[second]+nums[n-2]+nums[n-1] < target)
            {
                continue;
            }
            while (third < fourth)
            {
                if (third > second + 1 && nums[third - 1] == nums[third])
                {
                    ++third;
                    continue;
                }
                // 使用 long long 类型只是为了避免 int 类型求和溢出，不知道是否有更好的防溢出的方法
                long long sum = (long long)nums[first] + nums[second] + nums[third] + nums[fourth];
                if (sum > (long long)target)
                {
                    // 四数之和大于 target，我们需要左移 fourth 指针来逼近 target
                    --fourth;
                }
                else if (sum == (long long)target)
                {
                    // 找到了一个相同的和值，我们只需要添加答案，并且把两个指针同时向内推动一步即可(具体原因可见15题：三数之和)
                    res.push_back(vector<int>{nums[first], nums[second], nums[third], nums[fourth]});
                    ++third;
                    --fourth;
                }
                else
                {
                    // 四数之和小于 target，我们需要右移动 third 指针来逼近 target
                    ++third;
                }
            }
        }
    }
    return res;
}