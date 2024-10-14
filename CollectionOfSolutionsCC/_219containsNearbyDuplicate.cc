#include "Solution.h"

bool Leetcode201_300::Solution::containsNearbyDuplicate(vector<int>& nums, int k)
{
    // 本题较为简单，我们可以考虑使用一个定长的窗口(长度为 k)来进行滑动，这个窗口内的元素只要出现了相等，那么就可以返回 true
    // 划定窗口初始的左边界
    int left = -1, n = nums.size();
    // k 如果大于 n，我们可以简单地丢弃掉大于 n 的那部分
    // 哈希集合记录窗口内出现过的元素
    unordered_set<int> exist;
    for(int right = 0; right <= k && right < n; ++right)
    { 
        if(exist.find(nums[right]) != exist.end())
        {
            return true;
        }
        // 记录当前元素的出现次数
        exist.insert(nums[right]);
    }
    // 之后我们只需要滑动这个窗口即可
    for(int right = k+1; right < n; ++right)
    {
        // 先剔除原来窗口开头的元素
        exist.erase(nums[right-k-1]);
        // 之后检查新的窗口结尾元素之前是否在窗口内出现过
        if(exist.find(nums[right]) != exist.end())
        {
            return true;
        }
        // 记录当前窗口结尾元素的出现次数
        exist.insert(nums[right]);
    }
    // 循环正常退出了，说明我们没有找到合法的解，直接返回 false 即可
    return false;
}