#include "Solution.h"

string Leetcode1_100::Solution::minWindow(string s, string t)
{
    // 一般遇到这种字符串覆盖类的问题，本质上都是滑动窗口类的问题
    // 本题也可以利用类似的思路进行遍历
    // 简单分析一下要求
    // 要找的是 s 的所有子串中能够覆盖 t 中所有字符的最小子串
    // 说明题要我们找的是 "覆盖" 而不是 "包含"，如果包含的话，那么要么是子序列那种动态规划，要么是子串匹配那种 KMP
    // 本题要的是 "出现"，因而就不需要这种考虑完全匹配的算法
    // 即然要知道包含关系，那么我们就必须先拿到 t 串中包含的所有字符的信息(类型、出现次数)
    // 这可以用一个哈希表来存储
    // 记录：{字符，出现次数}
    unordered_map<char, int> rec;
    int m = s.size(), n = t.size();
    // 一个全局的"种类差距"值，后面会讲用处
    int diff = 0;
    for(int j = 0; j < n; ++j)
    {
        // 如果这个字符是新出现的，就多记录一个"种类差距"值
        if(rec.find(t[j]) == rec.end())
        {
            ++diff;
        }
        // C++ 的散列表会自动给没有添加过的表项进行初始化(为0)，所以我们这里可以直接使用递增运算符
        ++rec[t[j]];
    }
    // 循环结束后，我们就拿到了 t 中所有字符的种类以及出现次数信息，以及一个全局的 "种类差距" 信息
    // 接下来可以进行窗口的滑动操作
    // 规定一个窗口的左界
    int left = -1;
    // 全局的最小长度，m+1 代表不合法的结果(即没有这样的覆盖子串)
    int res = m+1;
    // 最短覆盖串的开始地址，m 代表不存在
    int start = m;
    // 不断滑动右界
    for(int right = 0; right < m; ++right)
    {
        // 先记录窗口计入 s[right]，之后的哈希表信息和全局 "种类差距" 值
        if(rec.find(s[right]) != rec.end())
        {
            --rec[s[right]];
            // 只有一种情况需要更新全局的 diff 值
            // 即原来是 1 差距，多了一个后，差距正好变成 0
            // 此时 diff 要减一
            // 如果本来是 0 差距，这样再做递减之后，对应字符的差距值会变成负数，不过这里仍然是合法的，因为我们后面在右移左指针的时候
            // 直到对应字符的差距值变为正数，我们才会修改 diff，所以不会影响最终结果
            // 而事实上，我们也不能在对应字符差距值为负的时候更新 diff 值，这样的话会导致这种问题：
            // 虽然一个很长的子串，它包含了 t 中所有的字符，但是这些字符出现的次数与 t 中不完全一致，而此时我们显然不会把 diff 置于0
            // 也就是不会进入下面的 while 循环更新最小长度，我们就丢失了这种结果
            // (细心的话会发现一旦出现这种情况，后面所有的子串就都没法计算最小长度了，因为无论怎样，left指针都不会再移动了)
            // 所以这里重申一下所谓全局 "种类差距" 值的含义：
            // 当前窗口中拥有的 t 中字符种类数与 t 中实际字符种类数的差距
            if(rec[s[right]] == 0)
            {
                --diff;
            }
        }
        // 如果当前窗口和 t 的全局 "种类差距" 值为0，则可以开始向右不断增加左边界的值，直到当前窗口不再合法
        while(diff == 0)
        {
            // 注意到，只有这个循环体内的窗口，才满足我们题目的要求，因而，我们只需要在这个循环体内不断更新全局的窗口最小值即可
            // 先更新，后收缩 left 指针
            // 更新答案串的起始下标
            start = res > right-left ? left+1 : start;
            res = min(res, right-left);
            // 其实我们会发现，这里只要 left 更新到了一个之前在 rec 表中出现过的字符，其实 while 循环就已经可以结束了
            if(rec.find(s[++left]) != rec.end())
            {
                ++rec[s[left]];
                // 和上面 right 更新时候的逻辑是一致的
                if(rec[s[left]] == 1)
                {
                    ++diff;
                }
            }
        }
    }
    // 返回最终结果即可
    return start != m ? s.substr(start, res) : "";
}