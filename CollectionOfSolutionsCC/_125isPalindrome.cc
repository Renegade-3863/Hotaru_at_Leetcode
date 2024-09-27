#include "Solution.h"

bool Leetcode101_200::Solution::isPanlindrome(string s)
{
    // 给定一个随机字符串，可能包含任何合法的 ASCII 字符，题目要求我们判断这个字符串，在移除了所有非字母数字字符之后
    // 是不是一个回文串
    // 这可以通过双指针算法简单地进行判断
    int left = 0, right = s.size()-1;
    // 定义一个 helper function，用来检查某个下标处的字符时候是字母数字字符
    function<bool(int)> check = [&](int idx) -> bool
    {
        return isalnum(s[idx]);
    };
    // 为了保证准确性，我们固定 left 指针，并在每次移动 left 指针前尝试使用 right 位置上的字符对其进行匹配
    // 或者，可以根据双指针的特性进行这样的定义：
    // 所有在 [left, right] 范围外的下标都是已经满足了对称关系的部分
    // 我们只需要在整个 while 循环中维护这个循环不变式，直到 left >= right 为止
    while(left < right)
    {
        // 我们在移动 left 的时候，需要检查当前的 left 下标处的字符是不是需要跳过的字符
        if(!check(left))
        {
            ++left;
            continue;
        }
        // 否则，我们可以对右指针进行判断/移动，尝试对当前 left 下标处的字符进行匹配
        while(!check(right))
        {
            --right;
        }
        // 现在 right 指向了从右到左第一个还未匹配的字母数字字符
        // 注意需要把 left 和 right 处的大写字符(如果是)转换成小写
        char cmp1 = s[left];
        if(s[left] >= 'A' && s[left] <= 'Z')
        {
            // 转换成小写
            cmp1 = cmp1-'A'+'a';
        }
        char cmp2 = s[right];
        if(s[right] >= 'A' && s[right] <= 'Z')
        {
            // 转换成小写
            cmp2 = cmp2-'A'+'a';
        }
        // 尝试进行匹配
        if(cmp1 == cmp2)
        {
            // 匹配了，把两个指针同时向内移动，代表它们原来位置上的字符可以回文，这样就保证了循环不变式的成立
            ++left; --right;
        }
        // 否则，无法匹配，我们直接返回 false 即可
        else
        {
            return false;
        }
    }
    // 满足了 left >= right
    // 我们可以直接返回 true
    return true;
}