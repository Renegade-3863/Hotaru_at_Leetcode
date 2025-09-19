#include <iostream>

class Solution 
{
public:
    string minWindow(string s, string t)
    {
        // 经典的滑动窗口类问题，我们可以用下面的循环不变式来考虑这道题：
        // 从 s 的每一个下标开始往右找，涵盖了 t 中所有字符的最小子串
        // 上面这个问题并不需要从 s 的每一个下标开始向右遍历
        // 我们可以利用滑动窗口的思想对解决方案进行简化
        // 定义一对窗口的左右边界指针 left 和 right
        // 以及一个变量 diff，记录当前的 [left, right] 区间与 t 代表的子串的字符为单位的差值
        // 换句话说，如果 diff 为 0，就代表窗口已经完全覆盖了 t 代表的子串了
        // 不过为了保证 diff 的可用性，我们还需要额外维护一个哈希表 memo，这个 memo 的作用类似差分，用于记录“当前窗口中每种字符与 t 中各种字符之间的差距值”
        // 我们在使用滑动窗口进行处理的时候，每当 right 向后移动一次，就尝试对 memo 以及 diff 进行更新
        // 1. 之后，如果 diff 是正数，那么说明以当前的 left 为起点，到现在的 right 为终点的子串并不能满足要求，不过这不代表我们后移 right 的话，后面不会有答案
        // 所以我们此时不能移动 left 指针
        // 同时，我们此时可以向后移动 right 指针，因为已知这个更靠左的 left 指针都没法满足题目都要求，那么在 (left, right) 区间中的其它值作为新的 left 值的话
        // 我们也没法得到可行的解，所以就没必要再进行检查了
        // 2. 之后，如果 diff 是负数，那么我们可以知道，当前以 left 为左边界的窗口已经“过分满足”了题目的要求，如果我们把 left 指针往右移动，那么就是有可能拿到合法结果的
        // 提问：为什么不左移 right 指针？
        // 因为这样可能找出重复的解，前面的 [left, right] 区间我们已经遍历过了
        // 而一旦我们找到一个 [left, right] 区间满足 diff == 0，那么我们就可以记录结果，并继续后移 right 指针尝试扩展窗口了
        // 定义一个左边界指针 left，指向窗口的左侧边界
        int left = 0, n = s.size();
        // res 用于记录全局的最短覆盖字符串的长度
        int start = n, res = n+1;
        // 预处理一下上面提到的 diff 和差分哈希表
        unordered_map<char, int> cnts;
        int diff = 0;
        for(const auto& c : t)
        {
            // 对于 t 中的每一个字符 c 进行记录
            if(cnts.find(c) == cnts.end())
            {
                // 如果是新字符，就更新索引
                ++diff;
            }
            // 统一记录字符出现次数
            ++cnts[c];
        }
        for(int right = 0; right < n; ++right)
        {
            // 对于 s[right]，如果它在 cnts 中有索引记录，那么我们就对它进行处理，否则，不用进行任何处理
            if(cnts.find(s[right]) != cnts.end())
            {
                if(--cnts[s[right]] == 0)
                {
                    --diff;
                }
            }
            // 如果经过了上面的处理之后， diff 被我们修改成了 0，那么我们就可以尝试对窗口左边界进行右缩，来找出当前右边界可以取到的最小窗口了
            while(diff == 0)
            {
                // 判断现在已知的字符串长度是否是最小的，不是的话，就进行更新
                start = res > right-left+1 ? left : start;
                res = min(res, right-left+1);
                if(cnts.find(s[left]) != cnts.end())
                {
                    if(++cnts[s[left]] == 1)
                    {
                        ++diff;
                    }
                }
                ++left;
            }
        }
        return s.substr(start, res);
    }
};