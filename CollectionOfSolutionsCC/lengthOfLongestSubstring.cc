#include "Solution.h"

int Leetcode1_100::Solution::lengthOfLongestSubstring(string s)
{
    // 经典的滑动窗口类问题
    // left 和 right 指针分别划定一个无重复字符的子串的左右边界
    int left = -1, n = s.size();
    // 用一个哈希表记录当前子串中出现过的所有字符的下标(使用懒删除策略)
    unordered_map<char, int> exist;
    int res = 0;
    // 枚举右边界
    for(int right = 0; right < n; ++right)
    {
        if(exist.find(s[right]) == exist.end())
        {
            // 记录一个之前没有出现过的字符在当前窗口内的下标
            exist[s[right]] = right;
        }
        else
        {
            // 通过不断右移left指针，知道当前窗口只包含right下标处一个s[right]字符
            while(exist[s[right]] > left)
            {
                ++left;
            }
            exist[s[right]] = right;
        }
        // 每次经过上面的判断，(left, right] 都是一个合法的，以right字符结尾的最长合法的无重复子串
        // 更新全局信息即可
        res = max(res, right-left);
    }
    return res;
}