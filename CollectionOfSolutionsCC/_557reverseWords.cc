#include "Solution.h"

string Leetcode501_600::Soltuion::reverseWords(string s)
{
    // 很有意思的一道题
    // 我们先思考题目的要求
    // 题目的本质要求是把字符串中的每一个单词反过来写
    // 那么我们只需要使用两个指针对 s 遍历一遍就能完成要求了
    // 定义两个指针，之后把 right 挪到第一个单词的右边界处 (第一个空格处)
    int left = 0, right = 0, n = s.size();
    // 注意，我们需要清除开头的空格
    while(s[left] == ' ')
    {
        ++left;
    }
    right = left;
    while(right < n && s[right] != ' ')
    {
        ++right;
    }
    // 把 s[left..right) 之间的字符反转过来
    // 定义一个子过程 reverseStr
    function<void(int, int)> reverseStr = [&](int left, int right) -> void
    {
        // 函数反转 s[left..right) 这个子字符串
        int mid = ((right-left)>>1)+left;
        --mid;
        // [3, 4, 5, 6, 7]
        // 取出中点后，我们使用位运算对这个子部分进行交换
        for(int i = left; i <= mid; ++i)
        {
            int cnt = i-left;
            s[i] ^= s[right-cnt-1];
            s[right-cnt-1] ^= s[i];
            s[i] ^= s[right-cnt-1];
        }
        // 反转完成，返回即可
    };
    while(left < n)
    {
        reverseStr(left, right);
        // 修正 right 到下一个非空格字符上，然后把 left 也挪过来
        while(right < n && s[right] == ' ')
        {
            ++right;
        }
        left = right;
        while(right < n && s[right] != ' ')
        {
            ++right;
        }
    }
    return s;
}