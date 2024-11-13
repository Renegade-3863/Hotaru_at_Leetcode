#include "Solution.h"

bool Leetcode301_400::Solution::isSubSequence(string s, string t)
{
    // 很简单的双指针问题，我们只需要用两个指针，分别指向两个字符串的头部
    // 指向 s 的指针只有在 t 中匹配到的时候才会移动，指向 t 的指针持续移动
    // 如果可以在遍历完 t 或者之前结束对 s 对遍历，那么我们就可以返回 true，否则只能返回 false
    int ptr1 = 0, ptr2 = 0;
    int m = s.size(), n = t.size();
    // 只要任何一个指针到达了结尾，我们都可以退出了
    while(ptr2 < n && ptr1 < m)
    {
        if(t[ptr2++] == s[ptr1])
        {
            ++ptr1;
        }
    }
    return ptr1 == m;
}